#!/usr/bin/sh

# SurgeOS create_image.sh
# Create a bootable image for SurgeOS

set -eu

# Input args
SURGEOS_IMAGE_PATH="$1"
SURGEOS_IMAGE_SIZE="$2"
SURGEOS_KERNEL_PATH="$3"
SURGEOS_GRUB_CONFIG="$4"

# Constants
SURGEOS_TEMP_DIR=$(mktemp -d)
SURGEOS_BOOT_PART_NO=1

echo "=== SurgeOS image generation: $SURGEOS_IMAGE_PATH ==="
echo "Size:          $SURGEOS_IMAGE_SIZE"
echo "Kernel path:   $SURGEOS_KERNEL_PATH"
echo "Grub menu.lst: $SURGEOS_GRUB_CONFIG"
echo "Temp dir:      $SURGEOS_TEMP_DIR"
echo "Partition num: $SURGEOS_BOOT_PART_NO"

echo "== Removing old image..."
rm -f $SURGEOS_IMAGE_PATH

echo "== Creating new image..."
dd if=/dev/zero of="$SURGEOS_IMAGE_PATH" bs=1M count="$SURGEOS_IMAGE_SIZE"

echo "== Creating MBR on image..."
echo -e "\o\nn\np\n$SURGEOS_BOOT_PART_NO\n\n\na\n$SURGEOS_BOOT_PART_NO\nw\n" | sudo fdisk "$SURGEOS_IMAGE_PATH"

echo "== Attaching loop device..."
sudo losetup -Pf "$SURGEOS_IMAGE_PATH"
LOOP_DEV_PATH=$(sudo losetup -j "$SURGEOS_IMAGE_PATH" | cut -d':' -f1)
if [ -z $LOOP_DEV_PATH ]; then
  echo "!! Failed to find loop device for $SURGEOS_IMAGE_PATH" >&2
  exit 1
fi
LOOP_PART_PATH=${LOOP_DEV_PATH}p${SURGEOS_BOOT_PART_NO}

echo "== Formatting partition $SURGEOS_BOOT_PART_NO..."
sudo mkfs.ext2 -F "$LOOP_PART_PATH"

echo "== Installing GRUB legacy..."
sudo mount "$LOOP_PART_PATH" "$SURGEOS_TEMP_DIR"
sudo grub-install --root-directory="$SURGEOS_TEMP_DIR" --no-floppy "$LOOP_DEV_PATH"

echo "== Copying config and kernel..."
sudo mkdir -p "$SURGEOS_TEMP_DIR/boot/grub"
sudo cp "$SURGEOS_KERNEL_PATH" "$SURGEOS_TEMP_DIR/boot/surgeos.elf"
sudo cp "$SURGEOS_GRUB_CONFIG" "$SURGEOS_TEMP_DIR/boot/grub/menu.lst"

echo "== Cleaning up..."
sudo umount "$SURGEOS_TEMP_DIR"
sudo rm -r "$SURGEOS_TEMP_DIR"
sudo losetup -d "$LOOP_DEV_PATH"

echo "=== Done. Created image at $SURGEOS_IMAGE_PATH ==="


