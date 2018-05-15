#include "../lib/socket.h"
#include "../lib/network.h"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <exception>

using namespace std;

Network::Network(Blockchain * bc, TransactionPool * tp, UnspentTxOutPool * up, bool * killMiner)
  : blockchain(bc), txpool_(tp), utxopool_(up), killMiner_(killMiner) {}

void Network::broadcastMessage(string msg){
  send(sock, msg.c_str(), msg.size(), 0);
}


void Network::broadcastBlock(Block& block){

  std::cout << "[network]: Broadcasting a block" << std::endl;
  Serialize serializer(block);

  string str = serializer.toString();

  while(send(sock, str.c_str(), str.size(), 0) != str.size()) {
    usleep(50000);
  }
  std::cout << "[network]: Block broadcast complete." << std::endl;
}

void Network::broadcastTransaction(Transaction& t) {
    std::cout << "[network]: Broadcasting a transaction" << std::endl;
    Serialize serializer(t);
    string str = serializer.toString();
    while(send(sock, str.c_str(), str.size(), 0) != str.size()) {
      usleep(50000);
    }
    std::cout << "[network]: Transaction broadcast complete." << std::endl;
}

void Network::sendChain(int to, size_t startIndex)
{
  vector<Block> chain = blockchain->GetChain();

  size_t i = startIndex;

  for(; i< chain.size(); i++)
  {

    Block block = chain[i];

    if(!sendBlock(to, block)){
      cout << "Block unacknowledged" << endl;
      i--;
      continue;
    }
    else {
      cout << "Block ACKNOWLEDGED" << endl;
    }

  }

  server.broadcastToOne(to, "END");
}

bool Network::sendBlock(int to, Block& block)
{

  Serialize serializer(block);
  string blockStr = serializer.toString();
  server.broadcastToOne(to, blockStr);
  usleep(50000);

  // ??? is there a better way?
  // activity = select(to + 1, &readfds, nullptr, nullptr, nullptr);
  //
  // if((activity < 0) && (errno != EINTR)){
  //   cout << "\nSelect error\n";
  // }

  // Try to read the acknowledgement
  int bytes_read = recv(to, buffer, sizeof(buffer), 0);
  buffer[bytes_read] = '\0';

  if( bytes_read > 0 ){

    string s = string(buffer);
    int idx = strtol(s.substr(3).c_str(), NULL, 10);

    if (idx == block.GetIndex())
    {
      return true;
    }
  }
  return false;
}


std::string Network::getLastReceived(){
  return lastReceived;
}

void Network::listen(){
  vector<Block> blocks;

  while(1){
    FD_ZERO(&readfds);

    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(sock, &readfds);

    // could probably remove this and just use sock
    max_sd = (sock > 0) ? sock : 0;

    activity = select(max_sd + 1, &readfds, nullptr, nullptr, nullptr);

    if((activity < 0) && (errno != EINTR)){
      cout << "\nSelect error\n";
    }

    // receive message
    if(FD_ISSET(sock, &readfds)){
      valread = read(sock, buffer, BUFF_SIZE);
      if(valread == 0){
        close(sock);
        cout << "\nConnection closed by host\n";
        //exit(0);
      }
      buffer[valread] = '\0';
      // this line below prints out any message
      //cout << string(buffer) << endl;

      string s = string(buffer);

      if(!isComplete(s))
        continue;

      if(s.substr(1, 5) == "BLOCK")
      {
        std::cout << "[network]: Got a block message" << std::endl;

        *killMiner_ = true;
        //
        Block block = JSONtoBlock(s);

        string idx = string {to_string(block.GetIndex())};

        // // If blockchain is empty or just a genesis block then we will get every block before updating the chain
        // if(blockchain == nullptr || blockchain->GetChain().size() == 1){
        //   blocks.push_back(block);
        // }
        // // Else it's just a new block
        // else{
        //   blockchain->Push(block);
        // }

        bool success = blockchain->Push(block);
        if(success) {
            std::cout << "[network]: Accepted block" << std::endl;
        }
        else {
            std::cout << "[network]: Rejected block" << std::endl;
        }
        broadcastMessage("GOT" + idx);

      }
      else if(s.substr(1,11) == "TRANSACTION") {
        std::cout << "[network]: Recieved transaction" << std::endl;
        //Deserialize transaction
        Transaction newTx = JSONtoTx(s);
        //Push transaction into pool
        bool result = txpool_->push(newTx);
      }
      else if(s.substr(1,12) == "REJECT_BLOCK") {
        //The broadcasted block was rejected by server
        std::cout << "[network]: Block was rejected!" << std::endl;

        //Display server's last block index
        //std::cout << "[network]: \"" << s.substr(15) << "\"" <<std::endl;
        size_t index = stol(s.substr(15));
        std::cout << "[network]: Server last block index: " << index <<   std::endl;

        //Drop all blocks up to server blockchain height - 1
        //Because my top block =/= server top block (so have to drop my top block)
        while(blockchain->GetHeight() >= index+1) {
            blockchain->Dump();
        }

        //send another request to server for entire chain
        std::cout << "[network]: Sending request for blockchain to the server at index: " << blockchain->GetHeight() <<  std::endl;
        std::string bcRequest = "\"REQUEST\":";
        bcRequest += std::to_string(blockchain->GetHeight());
        broadcastMessage(bcRequest);
        std::cout << "[network]: Request sent!" << std::endl;
      }
      if(s.substr(0, 3) == "END")
      {
        // end of chain recieved

      }
      lastReceived = s;
      strcpy(buffer, "");
      fflush(stdout);
    }
  }
}

void Network::startClient(){

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    cout << "\n Socket creation error \n";
    return;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(client.getLocalPort());

  if(inet_pton(AF_INET, ip_addr.c_str(), &serv_addr.sin_addr) <= 0){
    cout << "\nInvalid address\n";
    return;
  }

  if(connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
    cout << "\nConnection Failed \n";
    return;
  }

}

void Network::runServer() {

  TCPSocket* s;

  while(1)
  {

      //clear the socket set
      FD_ZERO(&readfds);

      //add master socket to set
      FD_SET(master_socket, &readfds);
      max_sd = master_socket;


      for(i=0; i < server.client_sockets.size(); i++)
      {
        s = server.client_sockets[i];

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
            client_socket = server.accept();
          }
          catch(SocketException &e){
            cout << e.what() << endl;
            continue;
          }

          sd = client_socket->getSockDesc();

          for (i = 0; i < server.client_sockets.size(); i++)
          {
              //if position is empty
              if( server.client_sockets[i] == nullptr )
              {
                  server.client_sockets[i] = client_socket;
                  break;
              }
          }
          if(i == server.client_sockets.size())
            server.client_sockets.push_back(client_socket);
          cout << "Adding to list of sockets as " << i << endl;
          cout << "Socket descriptor is " << sd << endl;


          //send new connection greeting message
          if( send(sd, message, strlen(message), 0) != strlen(message) )
          {
              perror("send");
          }

          puts("Welcome message sent successfully");
      }


      for(i = 0; i<server.client_sockets.size(); i++)
      {
        s = server.client_sockets[i];
        if(s == nullptr){
          continue;
        }

        sd = s->getSockDesc();

          if (FD_ISSET( sd , &readfds))
          {
            //Check if it was for closing , and also read the
            //incoming message
            if ((valread = read( sd , buffer, BUFF_SIZE)) == 0)
            {
                // maybe add index to reduce time complexity
                server.closeConnection(sd);
                cout << "Connection " << sd << " closed" << endl;
            }

            //Handle Incoming Messages
            else
            {
                //set the string terminating NULL byte on the end of the data read
                buffer[valread] = '\0';

                string s = string(buffer);

                // if incoming message is REQUEST send out the chain
                if(s.substr(1,7) == "REQUEST"){
                  strcpy(buffer, "");

                  // Block block = bc->GetLastBlock();
                  //
                  // Serialize serializer(block);
                  //
                  // string blockStr = serializer.toString();
                  //
                  // server.broadcastToOne(sd, blockStr);
                  std::cout << "[network]: in" << s << std::endl;
                  std::cout << "[network]: Recieved blockchain request with start index: " << s.substr(10) << std::endl;
                  //Parse starting index from request
                  size_t startIndex = stol(s.substr(10));

                  sendChain(sd,startIndex);
                  //cout << "No blocks: " << blockchain->GetChain().size() << "\n";

                  //cout << "Blockchain Sent:\n";
                  //cout << *blockchain << endl;

                }
                //if the incoming message is a new block
                else if(s.substr(1, 5) == "BLOCK"){
                  *killMiner_ = true;
                  std::cout << "[network]: Got a block" << std::endl;
                  // Parse block
                  std::cout << "[network-data]: " << s << std::endl;
                  if(!isComplete(s))
                    break;
                  Block block = JSONtoBlock(s);
                  std::cout << "[network]: The block is index " << block.GetIndex() << std::endl;
                  // Push
                  bool success = blockchain->Push(block);
                  if (success) {
                    std::cout << "[network]: Accepted block" << std::endl;
                    std::string response = "\"ACK_BLOCK\"";
                    server.broadcastToOne(sd, response);
                  }
                  else {
                    std::cout << "[network]: Rejected block" << std::endl;
                    //Tell the socket that sent this block, Server rejected
                    std::cout << "[network]: Tell socket" << sd << " block rejected" << std::endl;
                    std::string response = "\"REJECT_BLOCK\":";
                    response += std::to_string(blockchain->GetLastBlock().GetIndex());
                    std::cout << "[network]: Sending: " << response << std::endl;
                    server.broadcastToOne(sd, response);
                  }
                  //cout << "No blocks: " << blockchain->GetChain().size() << "\n";

                  //Broadcast recieved block
                  server.broadcastAll(sd, string(buffer));
                  *killMiner_ = true;

                }
                else if(s.substr(1,11) == "TRANSACTION") {
                    std::cout << "[network]: Recieved transaction" << std::endl;
                    std::cout << "[network-data]: " << s << std:: endl;
                    if(!isComplete(s))
                      break;
                    server.broadcastAll(sd, string(buffer));
                    Transaction txn = JSONtoTx(s);
                    txpool_->push(txn);
                }
            	else{
            		  // default: print to cout
                  std::cout << s << std::endl;
            	}

            		// print out all incoming messages
                //cout << string(buffer) << endl;

                strcpy(buffer, "");
            }
          }
      }
  }

}

bool isComplete(const string& s) {
  // counts left and right curly braces
  int left = 0, right = 0;
  for(auto c: s) {
    if(c == '{')
      left++;
    if(c == '}')
      right++;
  }
  return left == right;
}
