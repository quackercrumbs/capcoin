C++FLAG = -g -std=c++11

Transaction_OBJ = src/transaction.o src/txin.o src/txout.o
Block_OBJ = src/block.o src/blockchain.o
Merkle_OBJ = src/merkle.o
Network_OBJ = src/network.o src/socket.o

#Create objects pack together test utils and src objects
TestPack_Transaction = test/utils/test_transaction_utils.o\
					   $(Transaction_OBJ)

TestPack_Block = test/utils/test_block_utils.o\
				 $(Block_OBJ)\
				 $(TestPack_Transaction)

TestPack_Merkle = test/utils/test_merkle_utils.o\
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
INCLUDES = -I ./lib/ -I ./test/utils -I ./test/googletest/googletest/

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

xY = test/samplex.o test/samplex_unittest.o gtest-all.o

SAMPLE_X=samplexx.o
$(SAMPLE_X): $(xY) 
	g++ $(C++FLAG) -lpthread $(xY) -o $(EXEC_DIR)/$@ $(xY) 
#General Rules to compile drivers
all: capcoin

tests: test_transaction test_block 

#Specific Rules to compile specific drivers
capcoin:
	make $(CAPCOIN)

samplex:
	make $(SAMPLE_X)

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
	(rm -f gtest.a gtest_main.a;)

####################################################
#
#				Compiling Google Test Library
#
####################################################

#Path to root of google test
GTEST_DIR = ./test/googletest/googletest/

#Where all test are located
#USER_DIR = ./test/googletest/googletest/samples
USER_DIR = ./test/

#Flags passed to preprocessor
GTEST_CPPFLAGS += -isystem $(GTEST_DIR)/include
GTEST_CXXFLAGS += -g -Wall -Wextra -pthread

#All test produced for this Makefile
#TESTS = sample1_unittest
TESTS = samplex_unittest

#All google test headers
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

#GTEST build targets
testz: $(TESTS)

#Google test source files (dont touch pls)
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c\
		$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c\
		$(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


#Building personal tests. Test should link with either gtest.a or gtest_main.a

sample1.o: $(USER_DIR)/sample1.cc $(USER_DIR)/sample1.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $(USER_DIR)/sample1.cc

sample1_unittest.o: $(USER_DIR)/sample1_unittest.cc \
					$(USER_DIR)/sample1.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $(USER_DIR)/sample1_unittest.cc

sample1_unittest: sample1.o sample1_unittest.o gtest_main.a
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -lpthread $^ -o $@

samplex.o: $(USER_DIR)/samplex.cc $(USER_DIR)/samplex.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $(USER_DIR)/samplex.cc

samplex_unittest.o: $(USER_DIR)/samplex_unittest.cc \
					$(USER_DIR)/samplex.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $(USER_DIR)/samplex_unittest.cc

samplex_unittest: samplex.o samplex_unittest.o gtest_main.a
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -lpthread $^ -o $@

