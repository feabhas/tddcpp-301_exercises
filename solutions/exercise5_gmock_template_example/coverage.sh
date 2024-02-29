#!/bin/bash

# Get GCC version
gcc_version=$(gcc -dumpversion)
# echo "You are using GCC version $gcc_version."
gcovr --gcov-executable gcov-"$gcc_version"
