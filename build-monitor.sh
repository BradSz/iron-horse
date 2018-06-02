#!/bin/sh

dir="$(readlink -f "$(dirname "$0")")"
cd "$dir"

inotifywait -mr src/ test/ |
  while read path action file; do
    make all test
  done
