# gcovr and CMake

# GCC12 issue

```
gcovr --gcov-executable gcov-12
```

This is required for every invocation
## CMake compiler
  ``` 
add_compile_options(
  --coverage
  -fprofile-abs-path
)
```

Old style (prefer `--coverage`)
```
-fprofile-arcs -ftest-coverage 
```

## CMake linker

```
add_link_options("--coverage")
```

Old style
```
target_link_libraries(... gcov)
```

Output files at:
```
./build/tests/CMakeFiles/<exe>.dir/_/src
```

## Running

```
gcovr --filter=src/
```

Or
Create a file `gcovr.cfg`
```
filter = src/
html-details = yes  # info about each source file
output = build/coverage.html
exclude-unreachable-branches = yes
exclude-throw-branches = yes
delete-gcov-files = yes


```


**--exclude-unreachable-branches**¶
Exclude branch coverage from lines without useful source code (often, compiler-generated “dead” code). Default: False.

**--exclude-throw-branches**¶
For branch coverage, exclude branches that the compiler generates for exception handling. This often leads to more “sensible” coverage reports. Default: False.

**-d, --delete**¶
Delete gcda files after processing. Default: False. Config key: delete-gcov-files.