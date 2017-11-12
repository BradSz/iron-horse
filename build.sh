#!/bin/sh

set -e

dir="$(readlink -f "$(dirname "$0")")"

cd "$dir"
mkdir -p bin build

# Build Makefile(s)
cd "$dir/build"
cmake "$dir"

# Execute Makefile(s)
cd "$dir"
make -j$(nproc --ignore=1)

