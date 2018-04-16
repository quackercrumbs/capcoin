
# Capcoin


Current implementations of cryptocurrencies have various challenges to overcome, mainly characterized by their poor environmental sustainability and lack of consumer friendliness.

The main source of negative environmental impact any blockchain based network faces stems from the Proof-of-Work consensus algorithm used to secure the blockchain ledger. We propose the use a hybrid validation method predicated upon both Proof-of-Stake and Proof-of-Work. By sidestepping the computationally heavy resources required by an ordinary Proof-of-Work algorithm, in favor for a hybrid option, we aim to build a more sustainable and efficient cryptocurrency.

## Outcomes
There are two major components to this project, a linux-based full network node application and web-based thin client also known as a wallet. The expectations for each components is listed below.

### Network Node:
 - Listens, collects, and verifies open transactions
 - Creates blocks
 -  Add blocks to blockchain using consensus algorithm
 - Connect to other node (establish P2P connection with other nodes)
 - Should be able to query neighboring nodes for their blockchain
 - Should be able to broadcast the block the node just added to their blockchain
 - Store unverified transactions to a temporary pool

### Wallet:

 - Users should be able to send/receive coins with other users on Capcoin Wallet application
 - The user should be able to create an account
 - User identification (key pair creation/upload)
 - Send unverified transactions to CapCoin Blockchain network
 - Enforces transactions anonymity  
 - UI to view current state of blockchain

## To Run
```
make all //compiles all source code
./bin/capcoin.o //run driver for capcoin
./bin/capcoin.o server //run driver for capcoin as server
```
