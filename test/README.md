# Testing
This folder will contain test drivers for all classes, methods, etc. Currently all testing will have to be executed manually.

### To compile:
```
	make all #compiles all tests
	make transaction_test #compiles all files for transaction test
```

### To run:
Transaction test
```
	./transactionTest.o
```

### To clean:
```
	make clean
```

## Problems
When compiling source code, the output file will be saved in source directory. Ideally, we want it saved into the test directory.

