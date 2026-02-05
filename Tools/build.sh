#!/bin/bash
set -e

# Default to Build directory
BUILD_DIR="Build"
TARGET="SIL"

# Parse arguments
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -t|--target) TARGET="$2"; shift ;;
        -c|--clean) rm -rf "$BUILD_DIR"; shift ;;
        *) echo "Unknown parameter passed: $1"; exit 1 ;;
    esac
    shift
done

echo "Building ARK for Target: $TARGET in Directory: $BUILD_DIR"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

if [ "$TARGET" == "ESP32" ]; then
    # Helper for ESP-IDF
    idf.py build
else
    # Standard CMake for SIL / Pico
    cmake .. -DARCH_TARGET="$TARGET"
    make -j$(nproc)
fi

echo "Build Complete! Output in $BUILD_DIR"
