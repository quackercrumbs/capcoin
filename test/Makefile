C++FLAG = -g -std=c++11

Transaction_OBJ = transaction_test.o ../src/transaction.o

EXEC_DIR = .

#Compiles all cpp files listed in the given OBJ variable
#TO FIX: compile all src code into this directory
#Currently, compiled src code saved into src directory
.cpp.o:
	g++ $(C++FLAG) -c $< -o $@


TRANSACTION_TEST=transactionTest.o #Executable name to test transaction
$(TRANSACTION_TEST): $(Transaction_OBJ) #Rule to compile transaction test driver
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Transaction_OBJ)


all: transaction_test

#Command to compile transaction test files
transaction_test:
	make $(TRANSACTION_TEST)

clean:
	(rm -f *.o;)
