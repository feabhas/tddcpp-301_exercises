# Build, Run and Test

Invoke:
```
$ build.sh
```


# Alternatively
## Create Build files

From project root:
```
$ cmake -S . -B build
```

## Build project

From project root:
```
$ cmake --build build
```

## Run tests

From project root:
```
$ cmake --build build -- test
```
The GTest output can be found in the file
```
./build/Testing/Temporary/LastTest.log
```

# Viewing GTest output

## CTest
```
$ CTEST_OUTPUT_ON_FAILURE=1 cmake --build build -- test
```
## Executable
```
$ ./build/test/BufferTest
```

# Generating Coverage Statistics

Run `gcov` using `gcovr`
```
$ gcovr
```

**NOTE** : if using gcc12 then either invoke `coverage.sh` or use
```
$ gcovr --gcov-executable gcov-12
```

Then open file `./build/coverage.html`
