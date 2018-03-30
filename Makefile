C++FLAG = -g -std=c++11

Transaction_OBJ = src/transaction.o src/txin.o src/txout.o
Block_OBJ = src/block.o src/blockchain.o
Merkle_OBJ = src/merkle.o
Network_OBJ = src/network.o src/socket.o

#Create objects pack together test utils and src objects
TestPack_Transaction = test/test_transaction_utils.o\
					   $(Transaction_OBJ)

TestPack_Block = test/test_block_utils.o\
				 $(Block_OBJ)\
				 $(TestPack_Transaction)

TestPack_Merkle = test/test_merkle_utils.o\
				  $(Merkle_OBJ)\
				  $(TestPack_Block)

#Objects for all test drivers
Test_Transaction_OBJ = test/transaction_test.o\
					   $(TestPack_Transaction)

Test_Block_OBJ = test/block_test.o\
				 $(TestPack_Block)

Test_Merkle_OBJ = test/merkle_test.o\
				  $(TestPack_Merkle)\

#Compiles the main capcoin program and its prerequisutes
Capcoin_OBJ = src/capcoin.o $(Transaction_OBJ) $(Block_OBJ) $(Network_OBJ)

#Where to store all drivers
EXEC_DIR = ./bin/

#Tells compiler where to find headers
#Useful for importing header files (instead of listing full relative path)
INCLUDES = -I ./lib/

#Compiles all cpp files listed in the given OBJ variable
.cpp.o:
	g++ $(C++FLAG) -c $< -o $@ $(INCLUDES)


#Capcoin Main Driver
CAPCOIN=capcoin.o #Executable name
$(CAPCOIN): $(Capcoin_OBJ) #Rule to compile capcoin
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Capcoin_OBJ)


#Test Drivers
TEST_TRANSACTION=test_transaction.o
$(TEST_TRANSACTION): $(Test_Transaction_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Test_Transaction_OBJ)

TEST_BLOCK=test_block.o
$(TEST_BLOCK): $(Test_Block_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Test_Block_OBJ)

TEST_MERKLE=test_merkle.o
$(TEST_MERKLE): $(Test_Merkle_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Test_Merkle_OBJ)


#General Rules to compile drivers
all: capcoin

tests: test_transaction test_block

#Specific Rules to compile specific drivers
capcoin:
	make $(CAPCOIN)

test_transaction:
	make $(TEST_TRANSACTION)

test_block:
	make $(TEST_BLOCK)

test_merkle:
	make $(TEST_MERKLE)

#Removes all executable objects from root, bin, and tests
clean:
	(rm -f *.o;)
	(rm -f bin/*.o;)
	(rm -f src/*.o;)
	(rm -f test/*.o;)
