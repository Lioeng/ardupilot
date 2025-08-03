#!/bin/bash

# ArduRocket Simulation Script
# This script runs ArduRocket in SITL (Software In The Loop) mode

set -e

echo "Starting ArduRocket simulation..."

# Build for SITL if not already built
if [ ! -f "build/sitl/bin/ardurocket" ]; then
    echo "Building ArduRocket for SITL..."
    ./ArduRocket/build.sh sitl
fi

# Run simulation
echo "Running ArduRocket simulation..."
./Tools/autotest/sim_vehicle.py -v Rocket --console --map

echo "Simulation completed!"