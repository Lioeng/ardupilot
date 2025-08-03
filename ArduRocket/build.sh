#!/bin/bash

# ArduRocket Build Script
# This script simplifies building ArduRocket for different boards

set -e

BOARD=${1:-"sitl"}
CLEAN=${2:-"false"}

echo "Building ArduRocket for board: $BOARD"

# Clean if requested
if [ "$CLEAN" = "true" ]; then
    echo "Cleaning build..."
    ./waf clean
fi

# Configure for the specified board
echo "Configuring for $BOARD..."
./waf configure --board $BOARD

# Build ArduRocket
echo "Building ArduRocket..."
./waf rocket

echo "Build completed successfully!"
echo "Binary location: build/$BOARD/bin/ardurocket"