```
#!/bin/bash

LOG_FILE="/var/log/usb_wipe.log"

echo "$(date): USB wipe background daemon started" >> "$LOG_FILE"

while true; do
    while read -r line; do
        eval "$line"  # Sets NAME, MOUNTPOINT, RM, TYPE

        # Only removable partitions
        if [[ "$RM" -ne 1 || "$TYPE" != "part" ]]; then
            continue
        fi

        DEVICE="/dev/$NAME"
        MOUNTPOINT="/mnt/usb_$NAME"

        # Skip if already mounted
        if mountpoint -q "$DEVICE"; then
            echo "$(date): $DEVICE is already mounted. Skipping." >> "$LOG_FILE"
            continue
        fi

        # Mount using standard mount (no udisksctl)
        mkdir -p "$MOUNTPOINT"
        if mount "$DEVICE" "$MOUNTPOINT" 2>>"$LOG_FILE"; then
            echo "$(date): Mounted $DEVICE at $MOUNTPOINT" >> "$LOG_FILE"
        else
            echo "$(date): Failed to mount $DEVICE manually. Skipping." >> "$LOG_FILE"
            continue
        fi

        # Check if mount has files
        FILE_COUNT=$(find "$MOUNTPOINT" -mindepth 1 | wc -l)
        if (( FILE_COUNT == 0 )); then
            echo "$(date): $DEVICE ($MOUNTPOINT) is empty. Nothing to wipe." >> "$LOG_FILE"
        else
            echo "$(date): Data found on $DEVICE ($MOUNTPOINT). Wiping..." >> "$LOG_FILE"
            find "$MOUNTPOINT" -mindepth 1 -exec rm -rf {} \;
            echo "$(date): Wiped contents of $DEVICE ($MOUNTPOINT)" >> "$LOG_FILE"
        fi

        # Unmount
        if umount "$DEVICE" 2>>"$LOG_FILE"; then
            echo "$(date): Unmounted $DEVICE from $MOUNTPOINT" >> "$LOG_FILE"
        else
            echo "$(date): Failed to unmount $DEVICE" >> "$LOG_FILE"
        fi

        # Remove temporary mount folder
        rmdir "$MOUNTPOINT" 2>/dev/null

    done < <(lsblk -P -o NAME,MOUNTPOINT,RM,TYPE)

    sleep 5
done
```

systemd service:

![WhatsApp Image 2025-07-07 at 13 54 43_959f4f3e](https://github.com/user-attachments/assets/04b651d8-a1ce-4e79-9754-a0d29739a0f6)


