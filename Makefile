#Assumes machine is Linux
COMPILER = g++

# Determine which compiler to use
UNAME_S := $(shell uname -s)	# Retrieve OS name

ifeq ($(UNAME_S),Darwin) 		# For MACOS
	COMPILER+=-8
endif

C++FLAG = -g -std=c++14

Transaction_OBJ = src/transaction.o src/txin.o src/txout.o src/transactionpool.o\
				  src/utxout.o src/utxoutpool.o
Block_OBJ = src/block.o src/blockchain.o
Merkle_OBJ = src/merkle.o
Network_OBJ = src/network.o src/socket.o
FullNode_OBJ = src/fullNode.o
Serialize_OBJ = src/serialize.o
Wallet_OBJ = src/wallet.o
ECC_OBJ = src/ecc.o

#Compiles the main capcoin program and its prerequisutes
Capcoin_OBJ = src/capcoin.o $(Transaction_OBJ) $(Block_OBJ) $(Serialize_OBJ) $(Wallet_OBJ)\
			  $(ECC_OBJ)

#Where to store all drivers
EXEC_DIR = ./bin

#Tells compiler where to find headers
#Useful for importing header files (instead of listing full relative path)
INCLUDES = -I ./lib/ -I ./test/utils -I ./modules/Breep/include

#Libaries paths' flag
LIBSDIR = -L ./modules/Breep/bin

LINKS = -pthread -lboost_system

#Compiles all cpp files listed in the given OBJ variable
.cpp.o:
	$(COMPILER) $(C++FLAG) -c $< -o $@ $(INCLUDES) $(LIBSDIR) $(LINKS)


#Capcoin Main Driver
CAPCOIN=capcoin #Executable name
$(CAPCOIN): $(Capcoin_OBJ) #Rule to compile capcoin
	$(COMPILER) $(C++FLAG) -o $(EXEC_DIR)/$@ $(Capcoin_OBJ) $(LINKS)

#General Rules to compile drivers
all: Capcoin

net_test:
	make $(NET_TEST)

#Specific Rules to compile specific drivers
Capcoin:
	make $(CAPCOIN)

#Removes all executable objects from root, bin, and tests
clean:
	(rm -f *.o;)
	(rm -f bin/*;)
	(rm -f src/*.o;)
	(rm -f test/*.o;)
	(rm -f test/gtest.a test/gtest_main.a;)
