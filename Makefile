C++FLAG = -g -std=c++11

Transaction_OBJ = src/transaction.o src/txin.o src/txout.o src/utxout.o src/utxoutpool.o
Block_OBJ = src/block.o src/blockchain.o
Merkle_OBJ = src/merkle.o
Network_OBJ = src/network.o src/socket.o

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

#General Rules to compile drivers
all: capcoin


#Specific Rules to compile specific drivers
capcoin:
	make $(CAPCOIN)

#Removes all executable objects from root, bin, and tests
clean:
	(rm -f *.o;)
	(rm -f bin/*.o;)
	(rm -f src/*.o;)
	(rm -f test/*.o;)
	(rm -f test/gtest.a test/gtest_main.a;)
	(rm -f bin/$(TESTS);)



####################################################
#
#				Compiling Google Test Library
#
####################################################

#Path to root of google test
GTEST_DIR = ./test/googletest/googletest

#Flags passed to preprocessor
GTEST_CPPFLAGS += -isystem $(GTEST_DIR)/include
GTEST_CXXFLAGS += -g -Wall -Wextra -pthread

#All google test headers
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

#Google test source files (dont touch pls)
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c\
		$(GTEST_DIR)/src/gtest-all.cc\
		-o $(USER_DIR)/gtest-all.o

gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c\
		$(GTEST_DIR)/src/gtest_main.cc\
		-o $(USER_DIR)/gtest_main.o

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $(USER_DIR)/$@ $(USER_DIR)/$^

GTEST_MAIN_OBJ = ./test/gtest-all.o\
				  ./test/gtest_main.o
gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $(USER_DIR)/$@ $(GTEST_MAIN_OBJ)


########################################################
#
#				Custom Util Test Files
#
########################################################

#Create objects pack together test utils and src objects
TestPack_Transaction = test/utils/test_transaction_utils.o\
					   $(Transaction_OBJ)

TestPack_Block = test/utils/test_block_utils.o\
				 $(Block_OBJ)\
				 $(TestPack_Transaction)

TestPack_Merkle = test/utils/test_merkle_utils.o\
				  $(Merkle_OBJ)\
				  $(TestPack_Block)

####################################################
#
#	Unittests
#
###################################################

#Where all test files are located
USER_DIR = ./test

#Test Utilty directory location
TEST_UTILS = $(USER_DIR)/utils

#Google Test Main driver
GTEST_MAIN = $(USER_DIR)/gtest_main.a

#All test produced for this Makefile
TESTS = sample_test.o transaction_test.o block_test.o merkle_test.o

#GTEST build targets
tests: $(TESTS)

#
#	Sample Unit Test
#

#Sample is utilty file with a function that is tested in  sample_unittest
sample.o: $(TEST_UTILS)/sample.cc $(TEST_UTILS)/sample.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $(TEST_UTILS)/sample.cc\
		-o $(TEST_UTILS)/sample.o

#This compiles sample_unittest
sample_unittest.o: $(GTEST_HEADERS) $(USER_DIR)/sample_unittest.cc \
					$(TEST_UTILS)/sample.h
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) $(INCLUDES) -c $(USER_DIR)/sample_unittest.cc\
		-o $(USER_DIR)/sample_unittest.o

#This compiles the executable to run sample unittest
#It links to the google test main, where the main function exists
SAMPLE_TEST_OBJ= $(TEST_UTILS)/sample.o $(USER_DIR)/sample_unittest.o $(GTEST_MAIN)
sample_test.o: sample.o sample_unittest.o gtest_main.a 
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -lpthread $(SAMPLE_TEST_OBJ) -o ./bin/$@


#
#	Transaction Unit Test
#
transaction_unittest.o: $(GTEST_HEADERS) $(USER_DIR)/transaction_unittest.cc
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) $(INCLUDES)\
		-c $(USER_DIR)/transaction_unittest.cc\
		-o $(USER_DIR)/transaction_unittest.o

TRANSACTION_TEST_OBJ = $(GTEST_MAIN) $(TestPack_Transaction)\
					   $(USER_DIR)/transaction_unittest.o
transaction_test.o: transaction_unittest.o gtest_main.a 
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -lpthread $(TRANSACTION_TEST_OBJ) -o ./bin/$@

#
#	Block Unit Test
#
block_unittest.o: $(GTEST_HEADERS) $(USER_DIR)/block_unittest.cc
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) $(INCLUDES)\
		-c $(USER_DIR)/block_unittest.cc\
		-o $(USER_DIR)/block_unittest.o

BLOCK_TEST_OBJ = $(GTEST_MAIN) $(TestPack_Block)\
					   $(USER_DIR)/block_unittest.o
block_test.o: block_unittest.o gtest_main.a 
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -lpthread $(BLOCK_TEST_OBJ) -o ./bin/$@

#
#	Merkle Unit Test
#
merkle_unittest.o: $(GTEST_HEADERS) $(USER_DIR)/merkle_unittest.cc
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) $(INCLUDES) \
		-c $(USER_DIR)/merkle_unittest.cc\
		-o $(USER_DIR)/merkle_unittest.o

MERKLE_TEST_OBJ = $(GTEST_MAIN) $(TestPack_Block)\
					   $(USER_DIR)/merkle_unittest.o
merkle_test.o: merkle_unittest.o gtest_main.a 
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -lpthread $(MERKLE_TEST_OBJ) -o ./bin/$@
