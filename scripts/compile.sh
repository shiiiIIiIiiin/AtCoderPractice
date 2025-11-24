#!/usr/bin/env bash
set -euo pipefail
if [ $# -ne 1 ]; then
  echo "Usage: $0 path/to/file.cpp"
  exit 1
fi
SRC="$1"
INCDIR="$(dirname "$0")/../vendor/ac-library"
g++ -std=c++17 -O2 -I "$INCDIR" -I "$PWD" -o "${SRC%.*}.exe" "$SRC"
echo "Built ${SRC%.*}.exe"
