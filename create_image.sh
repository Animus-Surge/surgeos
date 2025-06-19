#!/usr/bin/sh

# SurgeOS create_image.sh
# Create a bootable image for SurgeOS

set -e

mkdir -p isodir/boot/grub
cp $1/surgeos.elf isodir/boot/
cat > isodir/boot/grub/grub.cfg << EOF
set default=0
set timeout=0

menuentry "SurgeOS" {
    multiboot2 /boot/surgeos.elf
    boot
}
EOF
grub-mkrescue /usr/lib/grub/i386-pc -o surgeos.iso isodir


