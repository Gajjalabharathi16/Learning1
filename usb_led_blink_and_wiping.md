```
#!/bin/bash
set -euo pipefail

LOG_FILE="/var/log/usb_wipe.log"

# GPIO chip and pins
CHIP=gpiochip0
BLUE=17
GREEN=27
RED=22

# Blink delay for status LEDs (seconds)
BLINK_DELAY=0.3

log() {
    echo "$(date '+%Y-%m-%d %H:%M:%S'): $*" >> "$LOG_FILE"
}

blink_led() {
    local pin=$1
    local times=$2
    log "Blinking LED on GPIO $pin, $times times"
    for ((i=0; i<times; i++)); do
        gpioset "$CHIP" "$pin"=1
        sleep "$BLINK_DELAY"
        gpioset "$CHIP" "$pin"=0
        sleep "$BLINK_DELAY"
    done
}

blink_led_duration() {
    local pin=$1
    local duration=$2
    log "Blinking LED on GPIO $pin for $duration seconds"
    local end_time=$((SECONDS + duration))
    while (( SECONDS < end_time )); do
        gpioset "$CHIP" "$pin"=1
        sleep "$BLINK_DELAY"
        gpioset "$CHIP" "$pin"=0
        sleep "$BLINK_DELAY"
    done
}

blink_led_continuous_start() {
    local pin=$1
    log "Starting continuous blink on GPIO $pin"
    while true; do
        gpioset "$CHIP" "$pin"=1
        sleep "$BLINK_DELAY"
        gpioset "$CHIP" "$pin"=0
        sleep "$BLINK_DELAY"
    done
}

blink_led_continuous_stop() {
    local pid=$1
    log "Stopping continuous blink process $pid"
    kill "$pid" 2>/dev/null || true
    wait "$pid" 2>/dev/null || true
    # Turn off all LEDs to be safe
    gpioset "$CHIP" "$BLUE"=0 "$GREEN"=0 "$RED"=0 || true
}

log "USB wipe background daemon started"

while true; do
    while read -r line; do
        eval "$line"  # Sets NAME, MOUNTPOINT, RM, TYPE

        # Only removable partitions
        if [[ "$RM" -ne 1 || "$TYPE" != "part" ]]; then
            continue
        fi

        DEVICE="/dev/$NAME"
        MOUNTPOINT="/mnt/usb_$NAME"

        if mountpoint -q "$DEVICE"; then
            log "$DEVICE already mounted, skipping."
            continue
        fi

        mkdir -p "$MOUNTPOINT"
        if mount "$DEVICE" "$MOUNTPOINT" 2>>"$LOG_FILE"; then
            log "Mounted $DEVICE at $MOUNTPOINT"
        else
            log "Failed to mount $DEVICE"
            continue
        fi

        FILE_COUNT=$(find "$MOUNTPOINT" -mindepth 1 | wc -l)
        if (( FILE_COUNT == 0 )); then
            log "$DEVICE ($MOUNTPOINT) is empty, nothing to wipe."
        else
            log "Data found on $DEVICE ($MOUNTPOINT), wiping..."

            # Start blue LED blinking in background
            blink_led_continuous_start "$BLUE" &
            BLINK_PID=$!

            # Wipe attempt
            if find "$MOUNTPOINT" -mindepth 1 -exec rm -rf {} +; then
                log "Wipe succeeded on $DEVICE ($MOUNTPOINT)"
                # Stop blue blinking
                blink_led_continuous_stop "$BLINK_PID"

                # Blink green LED for 10 seconds
                blink_led_duration "$GREEN" 3
            else
                log "Wipe failed on $DEVICE ($MOUNTPOINT)"
                blink_led_continuous_stop "$BLINK_PID"

                # Blink red LED for 5 seconds
                blink_led_duration "$RED" 5
            fi
        fi

        if umount "$DEVICE" 2>>"$LOG_FILE"; then
            log "Unmounted $DEVICE"
        else
            log "Failed to unmount $DEVICE"
        fi

        rmdir "$MOUNTPOINT" 2>/dev/null || true

    done < <(lsblk -P -o NAME,MOUNTPOINT,RM,TYPE)

    sleep 5
done
```
