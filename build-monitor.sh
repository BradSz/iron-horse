#!/bin/sh

dir="$(readlink -f "$(dirname "$0")")"
cd "$dir"

inotifywait -mr src/ test/ |
  while read path action file; do
    reset
    date -Iseconds
    make all test
  done
