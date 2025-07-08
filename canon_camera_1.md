```bash
#!/bin/bash

# === CONFIGURATION ===
# Directory to store images
IMAGE_DIR="/home/scl/project/captured_images"
LAST_FILE_TRACKER="/home/scl/project/last_downloaded.txt"
# S3 bucket name
S3_BUCKET="canon-cam-s3"

# === SETUP ===
# Ensure directories and tracker file exist
mkdir -p "$IMAGE_DIR"
touch "$LAST_FILE_TRACKER"

# === Function to kill conflicting processes ===
kill_conflicting_processes() {
    echo "Checking for conflicting processes..."
    for process in gvfs-gphoto2-volume-monitor gvfsd-gphoto2; do
        PID=$(pgrep -f "$process")
        if [ ! -z "$PID" ]; then
            echo "Killing process $process (PID: $PID)..."
            sudo kill -9 "$PID"
        fi
    done
    echo "Resetting camera connection..."
    sudo gphoto2 --reset
}

# === Function to download new images ===
download_new_images() {
    echo "Checking for new images at $(date +"%Y-%m-%d %H:%M:%S")..."

    # Read last downloaded file number or default to 0 if empty
    LAST_DOWNLOADED=$(cat "$LAST_FILE_TRACKER")
    if [ -z "$LAST_DOWNLOADED" ]; then
        LAST_DOWNLOADED=0
    fi
    echo "Last downloaded file number: $LAST_DOWNLOADED"

    # List files on camera in target folder
    FILE_LIST=$(gphoto2 --folder="/store_00020001/DCIM/100CANON" --list-files 2>/dev/null)

    if [ -z "$FILE_LIST" ]; then
        echo "No files detected in camera storage."
        return
    fi

    # Extract file numbers and file names
    FILE_INFO=$(echo "$FILE_LIST" | awk '/#/ {print $1, $2}' | tr -d '#')

    # Find new JPEG files to download
    NEW_FILES=()
    while read -r FILE_NO FILE_NAME; do
        if [[ "$FILE_NAME" == *.JPG || "$FILE_NAME" == *.jpg ]]; then
            if [ "$FILE_NO" -gt "$LAST_DOWNLOADED" ]; then
                NEW_FILES+=("$FILE_NO")
            fi
        fi
    done <<< "$FILE_INFO"

    # If new files are found, download them
    if [ ${#NEW_FILES[@]} -gt 0 ]; then
        echo "Found ${#NEW_FILES[@]} new JPEG images. Downloading..."

        for FILE_ID in "${NEW_FILES[@]}"; do
            TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
            DEST_FILE="$IMAGE_DIR/image_${TIMESTAMP}_$FILE_ID.jpg"

            echo "Downloading file #$FILE_ID as $DEST_FILE"
            gphoto2 --folder="/store_00020001/DCIM/100CANON" --get-file="$FILE_ID" --filename "$DEST_FILE"

            # Check if download was successful and it's a valid JPEG
            if file "$DEST_FILE" | grep -qE 'JPEG image data'; then
                echo "$FILE_ID" > "$LAST_FILE_TRACKER"
                echo "File #$FILE_ID successfully saved."
            else
                echo "Error: File #$FILE_ID is not a valid JPEG. Deleting..."
                rm -f "$DEST_FILE"
            fi

            sleep 1 # Prevent overwhelming the camera
        done
    else
        echo "No new JPEG images found."
    fi
}

# === Background process to monitor directory and upload to S3 ===
monitor_and_upload() {
    echo "Monitoring $IMAGE_DIR for new images to upload to S3..."

    inotifywait -m -e close_write "$IMAGE_DIR" | while read path action file; do
        if [[ "$file" == *.jpg || "$file" == *.JPG ]]; then
            echo "New image detected: $file"
            echo "Uploading $file to S3..."
            aws s3 cp "$IMAGE_DIR/$file" "s3://$S3_BUCKET/"
            if [ $? -eq 0 ]; then
                echo "Upload complete: $file"
            else
                echo "Failed to upload: $file"
            fi
        fi
    done
}

# === Main loop ===
# Start directory monitoring in background
monitor_and_upload &

# Continuous loop to check camera for new images
while true; do
    kill_conflicting_processes
    download_new_images
    echo "Waiting for next check..."
    sleep 5
done
```
system service:

![WhatsApp Image 2025-07-08 at 12 05 10_f85988a2](https://github.com/user-attachments/assets/770b482d-6eb0-430d-b691-3dcded87b9fc)

