C++FLAG = -g -std=c++11

Transaction_OBJ = src/transaction.o src/txin.o src/txout.o
Block_OBJ = src/block.o src/blockchain.o
Merkle_OBJ = src/merkle.o
Capcoin_OBJ = src/capcoin.o $(Transaction_OBJ) $(Block_OBJ) $(Merkle_OBJ) src/network.o src/socket.o

#Where to store all drivers
EXEC_DIR = ./bin/

#Compiles all cpp files listed in the given OBJ variable
.cpp.o:
	g++ $(C++FLAG) -c $< -o $@


CAPCOIN=capcoin.o #Executable name
$(CAPCOIN): $(Capcoin_OBJ) #Rule to compile capcoin
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Capcoin_OBJ)


all: capcoin

#Command to compile capcoin
capcoin:
	make $(CAPCOIN)

clean:
	(rm -f *.o;)
	(rm -f bin/*.o;)
	(rm -f src/*.o;)
