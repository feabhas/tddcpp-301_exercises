# Build Instructions

## To build and Run using Cmake

From project root:
```
$ cmake -S . -B build
$ cmake --build build
$ cmake --build build -- test
```

For a clean rebuild use:
```
$ cmake --build build --clean-first
```
