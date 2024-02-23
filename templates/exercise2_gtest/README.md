# Create Build files

From project root:
```
$ cmake -S . -B build
```

# Build project

From project root:
```
$ cmake --build build
```

# Run tests

From project root:
```
$ cmake --build build -- test
```


# Run tests with verbosely

From project root:
```
$ CTEST_OUTPUT_ON_FAILURE=1 cmake --build build -- test
```

or to get colour output
```
$ cd build
$ TEST_COLOR=1 ctest -V
```