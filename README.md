# TDDC++301 TDD for Embedded C++ Exercises

**Contents**
- [TDDC++301 TDD for Embedded C++ Exercises](#tddc301-tdd-for-embedded-c-exercises)
- [Solutions](#solutions)
- [Templates](#templates)
- [Build the application](#build-the-application)
  - [Generate build configuration](#generate-build-configuration)
- [Build a project](#build-a-project)
- [Run tests](#run-tests)

The primary build environment for Feabhas projects is Ubuntu Linux using
the Linux GNU Toolchain (for host based courses), or the Arm GNU Toolchain 
(for embedded courses), and the [CMake](https://cmake.org/) build system. 


# Solutions

Solutions are provided for all exercises. 

# Templates

Sample starter projects for different exercises. Either copy the project
to a new workspace or work within the project itself.

# Build the application

Using CMake is a two step process: 
   1. generate build configuration files
   2. run the build 

## Generate build configuration

From a project root:

```
$ cmake -S . -B build
```

You need to regenerate the build configuration if you add
new source or header files, or add a `#include` for your own
header files to an existing file.

# Build a project

From project root:
```
$ cmake --build build
```

Remember to regenerate the build configuration if you add
new source or header files.

# Run tests

From project root:
```
$ cmake --build build -- test
```

