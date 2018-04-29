#ifndef P2P_MANAGE_h_
#define P2P_MANAGE_h_

#include "blockchain.h"
#include "block.h"
#include "serialize.h"

#include <boost/uuid/uuid_io.hpp>
#include <breep/network/tcp.hpp>
#include <breep/util/serialization.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <vector> 
#include <chrono>

/**
 *
 * Tells BREEP about data types 
 *
 */
BREEP_DECLARE_TYPE(std::string);
/*
BREEP_DECLARE_TYPE(Block);
BREEP_DECLARE_TYPE(Transaction);
*/


/**
 *
 *  RequestManager is contains functions that will attach to network listeners
 *      The idea is to have a seperate listener for each data type.
 *
 */
class RequestManager {
public:
    RequestManager();
    
    /**
     * Called when there is a connection or disconnection to the network
     */ 
    void connection_event(breep::tcp::network& network, const breep::tcp::peer& peer);

    /**
     * General string data listener
     */ 
    void message_recieved(breep::tcp::netdata_wrapper<std::string>& dw);

};

class P2P_Manager {
public:

    /**
     *
     * Initalize all private member variables. Must run init() explicitly.
     *
     */ 
    P2P_Manager( Blockchain* blockchain/*, TransactionPool* pool*/, unsigned short port);

    /**
     * 
     * Initalize all peer connections and listen threads
     *
     */
    void Init();
    
    /**
     *
     * Activates data and connection/disconnect listeners
     *
     */
    void OpenListeners();

    /**
     *
     * Deactivates peer manager
     *
     */
    void Close();

    /**
     *
     * Add a peer into managers connection list
     *
     */
    bool AddPeer(std::string address, unsigned short port);
   
    /**
     *
     * Broadcast message
     *
     */
    void BroadcastMessage(std::string msg);

    /**
     *
     * Broadcast the provided block
     *
     */
    void BroadcastBlock(Block& block);

    /**
     *
     * Retrieve the previous message
     *
     */
    std::string GetLastRecieved();

    /**
     *
     * This update private member variable port_
     * Note: It does not restart the connection onto this port
     *
     */
    void SetPort(unsigned short port);

    /**
     *
     * Updates the networks ptr to blockchain in main memory.
     *
     */    
    void SetBlockchain(Blockchain* bc);

    /**
     *
     * Upddates the networks ptr to transaction pool in main memory.
     *
     */
     void SetTransactionPool(/*TransactionPool* pool*/);


    /**
     *
     * Close clients connection from network 
     *
     */
    void Disconnect();

    /**
     *
     * Start background process for network
     * Note: Once this is a activated, node cannot connect to another network
     * This should only be used for the initial (first) node, aka the booststrap node
     *
     */
    void Run();    
    
private:
    
    unsigned short port_; //listening port
    breep::tcp::network* network_; //peer manager, managers connections with peers

    // Data sources
    Blockchain* bc_;
    //TransactionPool* txpool_;

};

#include "../src/p2p_manager.cpp"
#endif
