#!/bin/bash
set -e

# Require build flag
if [[ "$1" != "Release" && "$1" != "Debug" ]]; then
    echo "Usage: build.sh Release or Debug"
    exit 1
fi

BUILD_TYPE="$1"

if [[ -f "out/$BUILD_TYPE/ExampleProject.exe" ]]; then
    ./out/"$BUILD_TYPE"/ExampleProject.exe &
else
    echo "Could not find executable, run ./build.sh BUILD_TYPE in ./example directory."
fi
