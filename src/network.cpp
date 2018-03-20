#include "../lib/socket.h"
#include "../lib/network.h"
#include <iostream>

void Network::startClient(){
  TCPClientSocket client(1025);

  int sock = 0, valread, activity, max_sd;
  struct sockaddr_in serv_addr;

  string ip_addr =  "127.0.0.1";

  char buffer[1025];

  fd_set readfds;

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    cout << "\n Socket creation error \n";
    return;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(client.getLocalPort());

  if(inet_pton(AF_INET, ip_addr.c_str(), &serv_addr.sin_addr) <= 0)
  {
    cout << "\nInvalid address\n";
    return;
  }

  if(connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    cout << "\nConnection Failed \n";
    return;
  }

  while(1)
  {
    FD_ZERO(&readfds);

    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(sock, &readfds);

    // could probably remove this and just use sock
    max_sd = (sock > 0) ? sock : 0;

    activity = select(max_sd + 1, &readfds, nullptr, nullptr, nullptr);

    if((activity < 0) && (errno != EINTR))
    {
      cout << "\nSelect error\n";
    }

    if(FD_ISSET(sock, &readfds))
    {
      valread = read(sock, buffer, 1024);
      if(valread == 0)
      {
        close(sock);
        cout << "\nConnection closed by host\n";
        //exit(0);
      }
      buffer[valread] = '\0';
      cout << string(buffer) << endl;
      strcpy(buffer, "");
      fflush(stdout);
    }
    if(FD_ISSET(0, &readfds))
    {
      valread = read(0, buffer, 1024);
      buffer[valread] = '\0';
      if(send(sock, buffer, strlen(buffer), 0) != strlen(buffer))
      {
        cout << "\nSend error\n";
      }
    }
  }
}

void Network::startServer() {
  TCPServerSocket serv_socket(1025, 5);

  int sd, max_sd, valread, activity, i;

  char buffer[1025];  //data buffer of 1K
  char *message = "ECHO Daemon v1.0 \r\n";

  struct sockaddr_in address;

  fd_set readfds;

  int master_socket = serv_socket.getSockDesc();
  int * client_socket = serv_socket.getClients();

  TCPSocket* sock;

  TCPSocket* s;

  while(1)
  {

      //clear the socket set
      FD_ZERO(&readfds);

      //add master socket to set
      FD_SET(master_socket, &readfds);
      max_sd = master_socket;


      for(i=0; i < serv_socket.client_sockets.size(); i++)
      {
        s = serv_socket.client_sockets[i];

        //if valid socket descriptor then continue
        if(s == nullptr)
          continue;

        sd = s->getSockDesc();
        FD_SET(sd, &readfds);
        max_sd = sd;

      }

      //wait for an activity on one of the sockets , timeout is NULL ,
      //so wait indefinitely
      activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

      if ((activity < 0) && (errno!=EINTR))
      {
          // printf("select error");
          cout << "select error" << endl;
      }

      //If something happened on the master socket ,
      //then its an incoming connection
      if (FD_ISSET(master_socket, &readfds))
      {

          try {
            sock = serv_socket.accept();
          }
          catch(SocketException &e){
            cout << e.what() << endl;
            continue;
          }

          sd = sock->getSockDesc();

          for (i = 0; i < serv_socket.client_sockets.size(); i++)
          {
              //if position is empty
              if( serv_socket.client_sockets[i] == nullptr )
              {
                  serv_socket.client_sockets[i] = sock;
                  cout << "Adding to list of sockets as " << i << endl;
                  break;
              }
          }
          if(i == serv_socket.client_sockets.size())
            serv_socket.client_sockets.push_back(sock);
          cout << "Adding to list of sockets as " << i << endl;
          cout << "Socket descriptor is " << sd << endl;


          //send new connection greeting message
          if( send(sd, message, strlen(message), 0) != strlen(message) )
          {
              perror("send");
          }

          puts("Welcome message sent successfully");
      }


      for(i = 0; i<serv_socket.client_sockets.size(); i++)
      {
        s = serv_socket.client_sockets[i];
        if(s == nullptr){
          continue;
        }

        sd = s->getSockDesc();

          if (FD_ISSET( sd , &readfds))
          {
            //Check if it was for closing , and also read the
            //incoming message
            if ((valread = read( sd , buffer, 1024)) == 0)
            {
                // maybe add index to reduce time complexity
                serv_socket.closeConnection(sd);
                cout << "Connection " << sd << " closed" << endl;
            }

            //Echo back the message that came in
            else
            {
                //set the string terminating NULL byte on the end of the data read
                buffer[valread] = '\0';
                serv_socket.broadcastAll(sd, string(buffer));
                strcpy(buffer, "");
            }
          }
      }
  }

}
