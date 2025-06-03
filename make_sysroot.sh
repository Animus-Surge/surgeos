#!/usr/bin/sh

SYSROOT_DIR="./sysroot/usr"

if [ ! -d "$SYSROOT_DIR" ]; then
  mkdir -p "$SYSROOT_DIR"
fi

# Copy directories and files to sysroot; ignore errors
cp -r ./include "$SYSROOT_DIR" > /dev/null 2>&1
cp -r ./lib "$SYSROOT_DIR" > /dev/null 2>&1
