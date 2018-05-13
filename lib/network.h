#ifndef NETWORK_H
#define NETWORK_H

#include "socket.h"
#include "block.h"
#include "blockchain.h"
#include "transactionpool.h"
#include "serialize.h"
#include <string>
#include <thread>


class Network{

public:
  Network(Blockchain * bc, TransactionPool* txpool, UnspentTxOutPool* utxopool, bool* killMiner);
  void startClient();
  void runServer();

  void listen();
  std::thread listenThread(){
    return std::thread([=] { listen(); });
  }

// These functions are used by the client to broadcast to all nodes.
  void broadcastMessage(std::string msg);
  void broadcastBlock(Block& block);
  void broadcastTransaction(Transaction& t);
// These functions are for the server to send to one node.
  void sendChain(int to);
  bool sendBlock(int to, Block& block);

  std::string getLastReceived();

private:
  TCPClientSocket client{1025};
  TCPServerSocket server{1025, 5};
  int sock = 0, valread, activity, max_sd, sd, i;
  int master_socket = server.getSockDesc();
  struct sockaddr_in serv_addr;
  struct sockaddr_in address;
  std::string ip_addr =  "167.99.12.102";
  //std::string ip_addr =  "127.0.0.1";
  std::string strMessage = "Established Network Connection \r\n";
  const char *message = strMessage.c_str();
  TCPSocket* client_socket;
  char buffer[1025];
  fd_set readfds;
  std::string lastReceived = "";

  Blockchain * blockchain = nullptr;
  TransactionPool * txpool_ = nullptr;
  UnspentTxOutPool * utxopool_ = nullptr;

  bool* killMiner_;
};

#endif
