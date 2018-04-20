#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
typedef void raw_type;       // Type used for raw data on this platform

#include "../lib/socket.h"

#include <iostream>

using namespace std;

void broadcast_all(int sd, int * client_socket, int max_clients, char * msg);
void close_connection(int sd, int * client_socket, int i);


// SocketException Code

SocketException::SocketException(const string &message, bool inclSysMsg)
  throw() : userMessage(message) {
  if (inclSysMsg) {
    userMessage.append(": ");
    userMessage.append(strerror(errno));
  }
}

SocketException::~SocketException() throw() {
}

const char *SocketException::what() const throw() {
  return userMessage.c_str();
}

// Function to fill in address structure given an address and port
static void fillAddr(const string &address, unsigned short port,
                     sockaddr_in &addr) {
  memset(&addr, 0, sizeof(addr));  // Zero out address structure
  addr.sin_family = AF_INET;       // Internet address

  hostent *host;  // Resolve name
  if ((host = gethostbyname(address.c_str())) == NULL) {
    // strerror() will not work for gethostbyname() and hstrerror()
    // is supposedly obsolete
    throw SocketException("Failed to resolve name (gethostbyname())");
  }
  addr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

  addr.sin_port = htons(port);     // Assign port in network byte order
}

// Socket Code

Socket::Socket() throw(SocketException) {
  if ((sockDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    throw SocketException("Socket creation failed (socket())", true);
  }

  int opt = 1;
  setsockopt(sockDesc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  // Mainly for testing
  setsockopt(sockDesc, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
}

Socket::Socket(int type, int protocol) throw(SocketException) {

  // Make a new socket
  // if ((sockDesc = socket(PF_INET, type, protocol)) < 0) {
  //   throw SocketException("Socket creation failed (socket())", true);
  // }
  if ((sockDesc = socket(AF_INET, type, protocol)) < 0) {
    throw SocketException("Socket creation failed (socket())", true);
  }

  int opt = 1;
  setsockopt(sockDesc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  // Mainly for testing
  setsockopt(sockDesc, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
}

Socket::Socket(int sockDesc) {
  this->sockDesc = sockDesc;
}

Socket::~Socket() {
  ::close(sockDesc);
  sockDesc = -1;
}

int Socket::getSockDesc() {
  return sockDesc;
}

string Socket::getLocalAddress() throw(SocketException) {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getsockname(sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of local address failed (getsockname())", true);
  }
  return inet_ntoa(addr.sin_addr);
}

unsigned short Socket::getLocalPort() throw(SocketException) {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getsockname(sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of local port failed (getsockname())", true);
  }
  return ntohs(addr.sin_port);
}

void Socket::setLocalPort(unsigned short localPort) throw(SocketException) {
  // Bind the socket to its port
  sockaddr_in localAddr;
  memset(&localAddr, 0, sizeof(localAddr));
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(localPort);

  if (::bind(sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
    throw SocketException("Set of local port failed (bind())", true);
  }
}

void Socket::setLocalAddressAndPort(const string &localAddress,
    unsigned short localPort) throw(SocketException) {
  // Get the address of the requested host
  sockaddr_in localAddr;
  fillAddr(localAddress, localPort, localAddr);

  if (::bind(sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
    throw SocketException("Set of local address and port failed (bind())", true);
  }
}

unsigned short Socket::resolveService(const string &service,
                                      const string &protocol) {
  struct servent *serv;        /* Structure containing service information */

  if ((serv = getservbyname(service.c_str(), protocol.c_str())) == NULL)
    return atoi(service.c_str());  /* Service is port number */
  else
    return ntohs(serv->s_port);    /* Found port (network byte order) by name */
}

// CommSocket Code
CommSocket::CommSocket(){

}


CommSocket::CommSocket(int type, int protocol)
    throw(SocketException) : Socket(type, protocol) {
}

CommSocket::CommSocket(int newConnSD) : Socket(newConnSD) {
}

void CommSocket::connect(const string &foreignAddress,
    unsigned short foreignPort) throw(SocketException) {
  // Get the address of the requested host
  sockaddr_in destAddr;
  fillAddr(foreignAddress, foreignPort, destAddr);

  // Try to connect to the given port
  if (::connect(sockDesc, (sockaddr *) &destAddr, sizeof(destAddr)) < 0) {
    throw SocketException("Connect failed (connect())", true);
  }
}

void CommSocket::send(const void *buffer, int bufferLen)
    throw(SocketException) {
  if (::send(sockDesc, (raw_type *) buffer, bufferLen, 0) < 0) {
    throw SocketException("Send failed (send())", true);
  }
}

int CommSocket::recv(void *buffer, int bufferLen)
    throw(SocketException) {
  int rtn;
  if ((rtn = ::recv(sockDesc, (raw_type *) buffer, bufferLen, 0)) < 0) {
    throw SocketException("Received failed (recv())", true);
  }

  return rtn;
}

string CommSocket::getForeignAddress()
    throw(SocketException) {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getpeername(sockDesc, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of foreign address failed (getpeername())", true);
  }
  return inet_ntoa(addr.sin_addr);
}

unsigned short CommSocket::getForeignPort() throw(SocketException) {
  sockaddr_in addr;
  unsigned int addr_len = sizeof(addr);

  if (getpeername(sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
    throw SocketException("Fetch of foreign port failed (getpeername())", true);
  }
  return ntohs(addr.sin_port);
}

// TCPSocket Code

TCPSocket::TCPSocket()
    throw(SocketException) : CommSocket(SOCK_STREAM,
    IPPROTO_TCP) {
}

TCPSocket::TCPSocket(const string &foreignAddress, unsigned short foreignPort)
    throw(SocketException) : CommSocket(SOCK_STREAM, IPPROTO_TCP) {
  connect(foreignAddress, foreignPort);
}

TCPSocket::TCPSocket(int newConnSD) throw(SocketException) : CommSocket(newConnSD) {
}

// TCPClientSocket Code
TCPClientSocket::TCPClientSocket(const string &localAddress, unsigned short localPort)
  throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP) {
    setLocalAddressAndPort(localAddress, localPort);
}

TCPClientSocket::TCPClientSocket(unsigned short localPort)
  throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP) {
    setLocalPort(localPort);
}

// TCPServerSocket Code

TCPServerSocket::TCPServerSocket(unsigned short localPort, int queueLen)
    throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP) {
  setLocalPort(localPort);
  setListen(queueLen);

  this->max_clients = 30;

  // this->clients = (int*) malloc(this->max_clients * sizeof(int));
  // memset(clients, 0, max_clients);
}

TCPServerSocket::TCPServerSocket(const string &localAddress,
    unsigned short localPort, int queueLen)
    throw(SocketException) : Socket(SOCK_STREAM, IPPROTO_TCP) {
  setLocalAddressAndPort(localAddress, localPort);
  setListen(queueLen);

  this->max_clients = 30;

  // this->clients = (int*) malloc(this->max_clients * sizeof(int));
  // memset(clients, 0, max_clients);
}

TCPServerSocket::~TCPServerSocket() {
  free(this->clients);
}

TCPSocket *TCPServerSocket::accept() throw(SocketException) {
  int newConnSD;
  if ((newConnSD = ::accept(sockDesc, NULL, 0)) < 0) {
    throw SocketException("Accept failed (accept())", true);
  }

  return new TCPSocket(newConnSD);
}

int * TCPServerSocket::getClients() {
  return this->clients;
}

unsigned int TCPServerSocket::maxClients() {
  return this->max_clients;
}

void TCPServerSocket::setListen(int queueLen) throw(SocketException) {
  if (listen(sockDesc, queueLen) < 0) {
    throw SocketException("Set listening socket failed (listen())", true);
  }
}

void TCPServerSocket::closeConnection(int sd)
{
  TCPSocket* sock = nullptr;

  // find client by socket descriptor
  for(int i=0; i < client_sockets.size(); i++)
  {
    TCPSocket *s = client_sockets[i];
    if(s == nullptr)
      continue;

    if(s->getSockDesc() == sd)
    {
      sock = s;
      delete this->client_sockets[i];
      this->client_sockets[i] = nullptr;
      break;
    }
  }

  // if client isn't there, give up
  if(sock == nullptr)
    return;

  struct sockaddr_in address;
  int addrlen = sizeof(address);
  //Somebody disconnected , get their details and print
  getpeername(sd , (struct sockaddr*)&address , \
      (socklen_t*)&addrlen);
  cout << "Host disconnected , ip "<< inet_ntoa(address.sin_addr) << " , port " <<  ntohs(address.sin_port) << endl;

  //Close the socket
  close( sd );
}

// sends to all but the sd
void TCPServerSocket::broadcastAll(int sd, const string &msg)
{

  for(auto s: client_sockets)
  {
    if(s == nullptr)
      continue;

    if(s->getSockDesc() == sd)
      continue;

    cout << "Sending to " << s->getSockDesc() << endl;

    if(send(s->getSockDesc(), msg.c_str(), msg.length(), 0) != msg.length())
    {
      cout << "\n*send error*\n" << endl;
    }

  }
}

// sends to only the sd
void TCPServerSocket::broadcastToSD(int sd, const string &msg)
{

  for(auto s: client_sockets)
  {
    if(s == nullptr)
      continue;

    if(s->getSockDesc() != sd)
      continue;

    cout << "Sending to " << s->getSockDesc() << endl;

    if(send(s->getSockDesc(), msg.c_str(), msg.length(), 0) != msg.length())
    {
      cout << "\n*send error*\n" << endl;
    }
  }
}
