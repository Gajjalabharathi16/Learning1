To **blink an LED after wiping USB data (step 3)**, you'll need to modify your script by:

1. **Exporting a GPIO pin** (e.g., GPIO17).
2. **Setting it as output**.
3. **Blinking the LED** a few times (e.g., on/off every 0.5s).
4. **Cleaning up** (unexporting GPIO optionally).

Below is your **updated script** with LED blinking **after step 3** (i.e., after wiping but before unmounting):

---

### ✅ **Updated USB Auto-Wipe Script with LED Blink**

```bash
#!/bin/bash

LOG_FILE="/var/log/usb_wipe.log"
LED_GPIO=17  # Change this GPIO number based on your setup

# Initialize GPIO for LED if not already initialized
if [ ! -d "/sys/class/gpio/gpio$LED_GPIO" ]; then
    echo "$LED_GPIO" > /sys/class/gpio/export
    sleep 0.5
fi
echo "out" > /sys/class/gpio/gpio$LED_GPIO/direction

echo "$(date): USB wipe background daemon started" >> "$LOG_FILE"

while true; do
    while read -r line; do
        eval "$line"  # Sets NAME, MOUNTPOINT, RM, TYPE

        if [[ "$RM" -ne 1 || "$TYPE" != "part" ]]; then
            continue
        fi

        DEVICE="/dev/$NAME"
        MOUNTPOINT="/mnt/usb_$NAME"

        if mountpoint -q "$DEVICE"; then
            echo "$(date): $DEVICE is already mounted. Skipping." >> "$LOG_FILE"
            continue
        fi

        mkdir -p "$MOUNTPOINT"
        if mount "$DEVICE" "$MOUNTPOINT" 2>>"$LOG_FILE"; then
            echo "$(date): Mounted $DEVICE at $MOUNTPOINT" >> "$LOG_FILE"
        else
            echo "$(date): Failed to mount $DEVICE manually. Skipping." >> "$LOG_FILE"
            continue
        fi

        FILE_COUNT=$(find "$MOUNTPOINT" -mindepth 1 | wc -l)
        if (( FILE_COUNT == 0 )); then
            echo "$(date): $DEVICE ($MOUNTPOINT) is empty. Nothing to wipe." >> "$LOG_FILE"
        else
            echo "$(date): Data found on $DEVICE ($MOUNTPOINT). Wiping..." >> "$LOG_FILE"
            find "$MOUNTPOINT" -mindepth 1 -exec rm -rf {} \;
            echo "$(date): Wiped contents of $DEVICE ($MOUNTPOINT)" >> "$LOG_FILE"

            # === Blink LED after wiping ===
            echo "$(date): Blinking LED on GPIO$LED_GPIO" >> "$LOG_FILE"
            for i in {1..5}; do
                echo 1 > /sys/class/gpio/gpio$LED_GPIO/value
                sleep 0.5
                echo 0 > /sys/class/gpio/gpio$LED_GPIO/value
                sleep 0.5
            done
        fi

        if umount "$DEVICE" 2>>"$LOG_FILE"; then
            echo "$(date): Unmounted $DEVICE from $MOUNTPOINT" >> "$LOG_FILE"
        else
            echo "$(date): Failed to unmount $DEVICE" >> "$LOG_FILE"
        fi

        rmdir "$MOUNTPOINT" 2>/dev/null

    done < <(lsblk -P -o NAME,MOUNTPOINT,RM,TYPE)

    sleep 5
done
```

---

### ✅ How the LED Blink Works:

* `echo 1 > /sys/class/gpio/gpio17/value` → Turns LED **ON**
* `sleep 0.5` → Waits 0.5 seconds
* `echo 0 > /sys/class/gpio/gpio17/value` → Turns LED **OFF**
* This repeats 5 times (blinks 5 times)

---

### ⚠️ Make sure:

* You have the correct GPIO number.
* GPIO is connected to an LED with resistor.
* You run the script with **root privileges** (`sudo`) because GPIO and mounting require that.

---

Would you like me to also include **auto unexporting the GPIO** or a **cleanup script** on shutdown?
