#!/bin/bash

# Ensure script exits on error
set -e

# Check for build type argument
if [ "$1" != "Release" ] && [ "$1" != "Debug" ]; then
    echo "Usage: build.sh Release or Debug"
    exit 1
fi

BUILD_TYPE=$1

# Create build directory
BUILD_DIR="out/bin/$BUILD_TYPE"
mkdir -p "$BUILD_DIR"

cd "$BUILD_DIR"

# Set install directory
INSTALL_DIR="$(pwd)/../../../FracLib"

# Generate library
cmake -G "Ninja" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" ../../..

# Build and install the library
cmake --build .
cmake --install .