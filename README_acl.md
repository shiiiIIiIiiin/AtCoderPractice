AtCoder Library (ACL) helper

This repository includes AtCoder Library as a git submodule at `vendor/ac-library`.

Quick usage

- Build a single source file (bash):
  ./scripts/compile.sh path/to/file.cpp

- Build a single source file (PowerShell):
  ./scripts/compile.ps1 path\to\file.cpp

Both scripts add `vendor/ac-library` to the include path. You can also compile manually:

g++ -std=c++17 -O2 -I vendor/ac-library -o path/to/output.exe path/to/file.cpp

Notes:
- If you clone this repository, initialize submodules with:
  git submodule update --init --recursive
- Use `#include <atcoder/all>` or specific headers like `#include <atcoder/dsu.hpp>`.
