# Build Instructions

## To build and Run using Meson

From project root:
```
$ meson builddir && cd builddir
$ ninja test
```

## To build and Run using Cmake

From project root:
```
$ .build.sh test
```

For a clean rebuild use:
```
$ .build.sh reset test
```

