C++FLAG = -g -std=c++11

Transaction_OBJ = src/transaction.o src/txin.o src/txout.o
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

GTEST_MAIN_OBJS = ./test/gtest-all.o\
				  ./test/gtest_main.o
gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $(USER_DIR)/$@ $(GTEST_MAIN_OBJS)


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

#Google Test Main driver
GTEST_MAIN = $(USER_DIR)/gtest_main.a

#All test produced for this Makefile
TESTS = sample_test.o

#GTEST build targets
tests: $(TESTS)

#Building personal tests. Test should link with either gtest.a or gtest_main.a
sample.o: $(USER_DIR)/sample.cc $(USER_DIR)/sample.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $(USER_DIR)/sample.cc\
		-o $(USER_DIR)/sample.o

sample_unittest.o: $(USER_DIR)/sample_unittest.cc \
					$(USER_DIR)/sample.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -c $(USER_DIR)/sample_unittest.cc\
		-o $(USER_DIR)/sample_unittest.o

SAMPLE_TEST_OBJ= $(USER_DIR)/sample.o $(USER_DIR)/sample_unittest.o $(GTEST_MAIN)
sample_test.o: sample.o sample_unittest.o gtest_main.a 
	$(CXX) $(GTEST_CPPFLAGS) $(GTEST_CXXFLAGS) -lpthread $(SAMPLE_TEST_OBJ) -o ./bin/$@
