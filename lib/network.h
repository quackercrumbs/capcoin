#ifndef NETWORK_H
#define NETWORK_H

#include "socket.h"
#include <string>

class Network{
public:

  void broadcastMessage(std::string msg);
  void listen();
  void startClient();
  void startServer();

private:
  TCPClientSocket client{1025};
  int sock = 0, valread, activity, max_sd;
  struct sockaddr_in serv_addr;
  std::string ip_addr =  "167.99.12.102";
  char buffer[1025];
  fd_set readfds;


};



#endif
