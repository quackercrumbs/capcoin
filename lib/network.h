#ifndef NETWORK_H
#define NETWORK_H

#include "socket.h"
#include "block.h"
#include "serialize.h"
#include <string>
#include <thread>

class Network{

public:
  void startClient();
  void startServer();

  void listen();
  std::thread listenThread(){
    return std::thread([=] { listen(); });
  }

  void broadcastMessage(std::string msg);

  void broadcastBlock(Block& block);

  std::string getLastReceived();

private:
  TCPClientSocket client{1025};
  int sock = 0, valread, activity, max_sd;
  struct sockaddr_in serv_addr;
  std::string ip_addr =  "167.99.12.102";
  char buffer[1025];
  fd_set readfds;
  std::string lastReceived = "";

};

#endif
