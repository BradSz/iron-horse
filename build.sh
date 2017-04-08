#!/bin/sh

set -e

# root_dir="$(readlink -f "$(dirname "$0")")"
#build_dir="$root_dir/staging"
#  bin_dir="$root_dir/bin"
#
#mkdir --parents "$build_dir"
#mkdir --parents "$bin_dir"
#
#cd "$build_dir"
#cmake "$root_dir"
#cmake --build "$build_dir"


dir="$(readlink -f "$(dirname "$0")")"

cd "$dir"
mkdir -p bin build

cd build
cmake ..
make -j$(nproc --ignore=1)

