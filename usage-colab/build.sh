#!/bin/bash

DEVICE_FLAG=""
if [[ "$1" == "--device" || "$1" == "device" ]]; then
    DEVICE_FLAG="-DCOMPILE_FOR_DEVICE"
    echo "Building WITH device support..."
else
    echo "Building WITHOUT device support (run with '--device' to enable)..."
fi

g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion \
    -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused \
    -Woverloaded-virtual -Wnull-dereference -Wdouble-promotion -Wformat=2 \
    -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches \
    -Wlogical-op -Wuseless-cast -Weffc++ -O2 -fsanitize=address,undefined \
    -fstack-protector-strong $DEVICE_FLAG main.cpp -o skipy.out