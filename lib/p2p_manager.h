#ifndef P2P_MANAGE_h_
#define P2P_MANAGE_h_

#include "blockchain.h"
#include "block.h"
#include "serialize.h"

#include <boost/uuid/uuid_io.hpp>
#include <breep/network/tcp.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

class timed_message {

public:
    timed_message();

    void operator() (breep::tcp::peer_manager&, const breep::tcp::peer& source, breep::cuint8_random_iterator data, size_t data_size, bool);

private:
    const time_t m_starting_time;

};


// A function that will be passed to respond to connections and disconnections to client
void connection_disconnection(breep::tcp::peer_manager&, const breep::tcp::peer& peer);

class P2P_Manager {
public:

    //Initalize all private member variables. Must run init() explicitly.
    P2P_Manager( Blockchain* blockchain/*, TransactionPool* pool*/, unsigned short port);

    //Initalize all peer connections and listen threads
    void init();

    // Activates data and connection/disconnect listeners
    void OpenListeners();

    // Deactivates peer manager and close all listeners
    void Close();

    //Add a peer into managers connection list
    bool AddPeer(std::string address, unsigned short port);
   
    // Broadcast message
    void broadcastMessage(std::string msg);

    // Broadcast the provided block
    void broadcastBlock(Block& block);

    // Retrieve the previous message
    std::string getLastRecieved();

    // Getters and Setter Functions
    void SetPort(unsigned short port);

    void SetBlockchain(Blockchain* bc);

    void SetTransactionPool(/*TransactionPool* pool*/);

    // Peer Manager Function Wrappers
    void disconnect();

    void send_to_all(std::string msg);

    void run();    
    
private:
    
    unsigned short port_; //listening port
    breep::tcp::peer_manager* peer_manager_; //peer manager, managers connections with peers
    

    // Data sources
    Blockchain* bc_;
    //TransactionPool* txpool_;

    breep::listener_id data_listener_id_;
    breep::listener_id connection_listener_id_;
    breep::listener_id disconnection_listener_id_;



};

#include "../src/p2p_manager.cpp"
#endif
