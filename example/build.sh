#!/bin/bash
set -e

# Require build flag
if [[ "$1" != "Release" && "$1" != "Debug" ]]; then
    echo "Usage: build.sh Release or Debug"
    exit 1
fi

BUILD_TYPE="$1"
BUILD_DIR="bin/$BUILD_TYPE"
FracLib="$(cd "$(dirname "${BASH_SOURCE[0]}")/../out/FracLib" && pwd)"

# Ensure the library installation directory exists
if [[ ! -d "$FracLib" ]]; then
    echo "Error: Required library directory $FracLib does not exist."
    exit 1
fi

# Create the build directory if it doesn't exist
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake -S ../.. -B . -G "Ninja" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DCMAKE_PREFIX_PATH="$FracLib"
cmake --build .
