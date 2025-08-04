#!/bin/bash
set -uo pipefail  # Removed -e to avoid premature script exit

LOG_FILE="/var/log/usb_wipe.log"
CHIP=gpiochip0
BLUE=17
GREEN=27
RED=22
BLINK_DELAY=0.3
TRACK_FILE="/tmp/usb_wiped.log"

command -v gpioset >/dev/null || { echo "gpioset not found"; exit 1; }
command -v lsblk >/dev/null || { echo "lsblk not found"; exit 1; }

log() {
    echo "$(date '+%Y-%m-%d %H:%M:%S'): $*" >> "$LOG_FILE"
}

blink_led_continuous_start() {
    local pin=$1
    while true; do
        /usr/bin/gpioset "$CHIP" "$pin"=1
        sleep "$BLINK_DELAY"
        /usr/bin/gpioset "$CHIP" "$pin"=0
        sleep "$BLINK_DELAY"
    done
}

blink_led_for_duration() {
    local pin=$1 duration=$2
    end=$((SECONDS + duration))
    while [ $SECONDS -lt $end ]; do
        /usr/bin/gpioset "$CHIP" "$pin"=1
        sleep "$BLINK_DELAY"
        /usr/bin/gpioset "$CHIP" "$pin"=0
        sleep "$BLINK_DELAY"
    done
    /usr/bin/gpioset "$CHIP" "$RED"=0
}

blink_led_until_removed() {
    local pin=$1 devname=$2
    log "Red LED blinking until $devname is removed"
    while lsblk | grep -q "$devname"; do
        /usr/bin/gpioset "$CHIP" "$pin"=1
        sleep "$BLINK_DELAY"
        /usr/bin/gpioset "$CHIP" "$pin"=0
        sleep "$BLINK_DELAY"
    done
    /usr/bin/gpioset "$CHIP" "$RED"=0
}

blink_led_pattern_sr0() {
    local pin=$1 devname=$2
    log "$devname is ROM device. Keeping RED LED ON continuously until removed."
    /usr/bin/gpioset "$CHIP" "$pin"=1
    while lsblk | grep -q "$devname"; do
        sleep 1
    done
    /usr/bin/gpioset "$CHIP" "$pin"=0
    log "$devname removed. RED LED turned OFF."
}

blink_led_continuous_stop() {
    local pid=$1
    kill "$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true
    /usr/bin/gpioset "$CHIP" "$BLUE"=0 "$GREEN"=0 "$RED"=0 || true
}

handle_u3_device() {
    local devname=$1
    if ! command -v u3-tool >/dev/null; then
        log "u3-tool not found. Cannot remove U3 CD-ROM partition on $devname"
        return 1
    fi
    local sg_dev
    sg_dev=$(sg_map | grep "$devname" | awk '{print $1}')
    if [[ -z "$sg_dev" ]]; then
        log "Could not find SCSI generic device for $devname"
        return 1
    fi
    log "U3 device detected ($devname). SCSI generic device: $sg_dev"
    log "Attempting to uninstall U3 CD-ROM partition..."
    if u3-tool --uninstall "$sg_dev" >> "$LOG_FILE" 2>&1; then
        log "Successfully removed U3 CD-ROM emulation from $devname"
        sleep 5
    else
        log "Failed to remove U3 CD-ROM emulation from $devname"
        log "Blinking red LED until device $devname is removed..."
        while [ -e "/dev/$devname" ]; do
            gpioset $CHIP $RED=1
            sleep 1
            gpioset $CHIP $RED=0
            sleep 1
        done
        log "U3 device $devname removed. Stopping red LED blink."
        return 1
    fi
}

log "USB full disk wipe daemon started"
touch "$TRACK_FILE"

while true; do
    # --- Handle U3 devices first ---
    if [[ -e /dev/sr0 ]]; then
        if blkid /dev/sr0 | grep -q 'U3'; then
            log "/dev/sr0 has U3 partition. Attempting to convert to normal USB."
            blink_led_continuous_start "$BLUE" &
            U3_BLINK_PID=$!
            handle_u3_device "sr0"
            blink_led_continuous_stop "$U3_BLINK_PID"
            sleep 5
            continue
        else
            blink_led_pattern_sr0 "$RED" "sr0" &
            continue
        fi
    fi

    # --- Continue with regular device scan ---
    while IFS= read -r line; do
        NAME=$(echo "$line" | grep -oP 'NAME="\K[^"]+')
        TYPE=$(echo "$line" | grep -oP 'TYPE="\K[^"]+')
        [[ -z "$NAME" || -z "$TYPE" ]] && continue

        DEV="/dev/$NAME"

        if [[ "$TYPE" == "rom" ]]; then
            blink_led_pattern_sr0 "$RED" "$NAME" &
            continue
        fi

        [[ "$TYPE" != "disk" || "$DEV" == "/dev/mmcblk0" ]] && continue

        SIZE_BYTES=$(lsblk -b -dn -o SIZE "$DEV" 2>/dev/null || echo 0)
        if [[ -z "$SIZE_BYTES" || "$SIZE_BYTES" -eq 0 ]]; then
            # Check if other non-zero removable disks exist; if yes, skip this dummy reader
            if lsblk -b -dn -o NAME,SIZE,TYPE | grep -v "$NAME" | grep -E "disk" | grep -qv " 0$"; then
                log "$DEV has 0B size but valid sibling disk exists. Skipping red LED blink for reader."
                continue
            fi
            log "$DEV has size 0. Possibly corrupted. Blinking RED until removed."
            blink_led_until_removed "$RED" "$NAME" &
            continue
        fi

        if blkid "$DEV" | grep -q 'U3'; then
            log "$DEV has U3 partition. Attempting to convert to normal USB."
            blink_led_continuous_start "$BLUE" &
            U3_BLINK_PID=$!
            handle_u3_device "$NAME"
            blink_led_continuous_stop "$U3_BLINK_PID"
            sleep 5
            continue
        fi

        log "$DEV will be wiped regardless of content. Starting wipe..."

        blink_led_continuous_start "$BLUE" &
        BLINK_PID=$!

        (
            trap '' ERR

            cleanup_on_error() {
                log "ERROR: Wiping $DEV failed or was interrupted."
                blink_led_continuous_stop "$BLINK_PID"
                if lsblk | grep -q "$NAME"; then
                    blink_led_until_removed "$RED" "$NAME"
                else
                    blink_led_for_duration "$RED" 5
                fi
            }

            {
                for part in $(lsblk -ln -o NAME "$DEV" | tail -n +2); do
                    umount "/dev/$part" 2>/dev/null || true
                done

                /usr/sbin/wipefs -a "$DEV" >> "$LOG_FILE" 2>&1 || { cleanup_on_error; exit 0; }
                /bin/dd if=/dev/zero of="$DEV" bs=1M count=20 status=none >> "$LOG_FILE" 2>&1 || { cleanup_on_error; exit 0; }

                /usr/sbin/parted -s "$DEV" mklabel msdos || { cleanup_on_error; exit 0; }
                /usr/sbin/parted -s "$DEV" mkpart primary fat32 1MiB 100% || { cleanup_on_error; exit 0; }

                sleep 2
                NEW_PART="${DEV}1"
                /sbin/mkfs.vfat "$NEW_PART" >> "$LOG_FILE" 2>&1 || { cleanup_on_error; exit 0; }

                log "$DEV formatted successfully."
                echo "$(date '+%Y-%m-%d %H:%M:%S'): $NAME wiped and formatted" >> "$TRACK_FILE"

                blink_led_continuous_stop "$BLINK_PID"

                blink_led_continuous_start "$GREEN" &
                GREEN_PID=$!
                while lsblk | grep -q "$NAME"; do sleep 1; done
                blink_led_continuous_stop "$GREEN_PID"
            } || {
                cleanup_on_error
            }
        )

    done < <(lsblk -P -o NAME,RM,SIZE,TYPE 2>/dev/null || true)

    sleep 3
    pkill gpioset || true
done
