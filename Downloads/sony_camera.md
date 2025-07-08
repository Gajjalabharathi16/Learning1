```bash
#!/bin/bash

exec > >(tee -a /tmp/camera_service_debug.log) 2>&1

echo "[ENV] Running as $(whoami) in $(pwd) at $(date)"
env

IMAGE_DIR="/home/scl/project/sony_capture"
MASS_STORAGE_DIR="$IMAGE_DIR/mass_storage"
PTP_CAPTURE_DIR="$IMAGE_DIR/ptp_capture"
MOUNT_POINT="/mnt/camera"
S3_BUCKET="sony-cam-s3"
UPLOAD_LOG="$IMAGE_DIR/uploaded_files.log"

mkdir -p "$MASS_STORAGE_DIR" "$PTP_CAPTURE_DIR" "$MOUNT_POINT"
touch "$UPLOAD_LOG"

# Absolute paths for commands
GPHOTO2="/usr/bin/gphoto2"
MOUNT="/bin/mount"
UMOUNT="/bin/umount"
AWS="/usr/bin/aws"
PGREP="/usr/bin/pgrep"
PKILL="/usr/bin/pkill"
CP="/bin/cp"
GREP="/bin/grep"
LSBLK="/bin/lsblk"
AWK="/usr/bin/awk"
SLEEP="/bin/sleep"

kill_gvfs_processes_if_any() {
    echo "🔍 Checking for conflicting gvfs processes..."
    local GVFS_PROCESSES=("gvfs-gphoto2-volume-monitor" "gvfsd-gphoto2")
    for proc in "${GVFS_PROCESSES[@]}"; do
        if $PGREP -f "$proc" > /dev/null; then
            echo "⚠  Found and killing: $proc"
            sudo $PKILL -9 -f "$proc"
        fi
    done
    echo "✅ gvfs process check complete."
}

upload_images_to_s3() {
    local DIR="$1"
    echo "🛰 Uploading new images from $DIR to S3..."

    shopt -s nullglob
    for file in "$DIR"/*.{JPG,jpg,ARW,arw}; do
        BASENAME=$(basename "$file")

        if $GREP -Fxq "$BASENAME" "$UPLOAD_LOG"; then
            echo "⏭ Already uploaded: $BASENAME"
        else
            echo "📤 Uploading $BASENAME to s3://$S3_BUCKET/"
            if $AWS s3 cp "$file" "s3://$S3_BUCKET/$BASENAME" > /dev/null 2>&1; then
                echo "$BASENAME" >> "$UPLOAD_LOG"
                echo "✅ Uploaded $BASENAME"
            else
                echo "❌ Upload failed: $BASENAME"
            fi
        fi
    done
    shopt -u nullglob
}

get_mass_storage_device() {
    $LSBLK -lnp -o NAME,TYPE,HOTPLUG,MOUNTPOINT | \
    $AWK '$2 == "part" && $3 == "1" && $4 == "" {print $1}' | head -n 1
}

is_camera_ptp_mode() {
    $GPHOTO2 --auto-detect | $GREP -i "Sony" > /dev/null
    return $?
}

is_camera_mtp_mode() {
    mtp-detect | $GREP -iq "Manufacturer.*Sony"
    return $?
}

handle_ptp_mode() {
    echo "📸 Camera detected in PTP mode."
    while is_camera_ptp_mode; do
        TIMESTAMP=$(/bin/date +"%Y%m%d_%H%M%S")
        IMAGE_FILE="$PTP_CAPTURE_DIR/image_${TIMESTAMP}.JPG"
        $GPHOTO2 --wait-event-and-download=10s --filename "$IMAGE_FILE" > /dev/null 2>&1

        if [ $? -eq 0 ] && [ -f "$IMAGE_FILE" ]; then
            echo "📥 Captured and saved: $(basename "$IMAGE_FILE")"
            upload_images_to_s3 "$PTP_CAPTURE_DIR"
        else
            echo "⏱ No image captured or download failed."
        fi

        $SLEEP 2
    done
    echo "⚠ Camera disconnected from PTP. Rechecking mode..."
}

handle_mass_storage_mode() {
    echo "💽 Camera in Mass Storage mode. Copying unique images..."
    DEVICE=$(get_mass_storage_device)
    if [ -z "$DEVICE" ]; then
        echo "❌ No USB storage found to mount."
        return
    fi

    echo "🔵 Mounting camera from $DEVICE ..."
    sudo $MOUNT "$DEVICE" "$MOUNT_POINT"

    if ! mount | $GREP "$MOUNT_POINT" > /dev/null; then
        echo "❌ Mount failed."
        return
    fi

    CAMERA_IMAGES="$MOUNT_POINT/DCIM/100MSDCF"
    if [ ! -d "$CAMERA_IMAGES" ]; then
        echo "❌ Camera folder not found at $CAMERA_IMAGES"
        sudo $UMOUNT "$MOUNT_POINT"
        return
    fi

    echo "📁 Checking for new unique images..."
    shopt -s nullglob
    for file in "$CAMERA_IMAGES"/*.{JPG,jpg,ARW,arw}; do
        BASENAME=$(basename "$file")
        DEST="$MASS_STORAGE_DIR/$BASENAME"

        if [ ! -f "$DEST" ]; then
            echo "➕ New file: $BASENAME"
            sudo $CP -v "$file" "$DEST"
        else
            echo "⏭ Already exists locally: $BASENAME"
        fi
    done
    shopt -u nullglob

    echo "📤 Unmounting camera..."
    sudo $UMOUNT "$MOUNT_POINT"
    echo "✅ Done. Unique images copied to $MASS_STORAGE_DIR"

    upload_images_to_s3 "$MASS_STORAGE_DIR"
}

# ---- Main Loop for Persistent Monitoring ----
kill_gvfs_processes_if_any

echo "🔁 Starting camera mode monitor..."
while true; do
    if is_camera_ptp_mode; then
        handle_ptp_mode
    elif is_camera_mtp_mode; then
        echo "⚠ MTP mode detected. Not supported for transfers in this script."
        $SLEEP 5
    else
        DEVICE=$(get_mass_storage_device)
        if [ -n "$DEVICE" ]; then
            handle_mass_storage_mode
        else
            echo "🔍 No camera detected. Retrying in 5 seconds..."
            $SLEEP 5
        fi
    fi
done
```
# systemd service:

![WhatsApp Image 2025-05-30 at 13 45 02_eaf6220f](https://github.com/user-attachments/assets/6b6d5c5f-7967-44ff-8cca-2f53462b2449)


