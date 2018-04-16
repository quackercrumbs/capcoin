
# Testing
This folder will contain test drivers for all classes, methods, etc. This project requires the googletest library inorder to run the tests.
 
## Setup
This compiles all of capcoins sources and clones the googletest library.
```
./setup.sh
```

### To compile and run:
```
make all            # compiles all unittest
make <unit test>    # compiles specific unit test
```

```
./bin/<unit test>   # runs a specific unit tests
```

### To clean:
```
make clean 
```
**Warning**: this will remove all compiled code for google tests.

## Creating New Tests
To create a new unit test you must have a unit test file:
```
<name>_unittest.cc
```
If there are more functions you wish to be used for testing put them into the utils folder and import them into you unit test file. Also make sure to add build rules for them in the Makefile.

Once you have your unit test file completed, go to the make file and add a target rule to build the unit test. When compiling link your unit test file to gtest_main.a. This file is where your unittest will be executed. See the makefile for an example of how you should build your unittest.

Review googletest documentation to get an introduction on how to create unittest.

[Google Test Introduction](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)



## Samples
View the sample files in the test directory to get an idea of how to create tests. That sample was copied from the googletest sample.

To view more google test samples go to the googletest/googletest/samples directory.


## Problems

The following test have not been implemented:

 - transaction_unittest
 - block_unittest
 - merkle_unittest
