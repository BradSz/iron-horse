#!/bin/sh

set -e

dir="$(readlink -f "$(dirname "$0")")"

cd "$dir"

# Build Makefile(s)
cmake "$dir"

# Execute Makefile(s)
make -j$(nproc --ignore=1)

