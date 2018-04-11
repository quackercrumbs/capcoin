#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network{
public:

  void broadcastMessage(std::string msg);
  void listen();
  void startClient();
  void startServer();


};



#endif
