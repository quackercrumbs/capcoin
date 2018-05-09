#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "transactionpool.h"
#include "transaction.h"
#include "blockchain.h"
#include "block.h"
#include "serialize.h"
#include "message.h"

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

//Serialization and Deserialization overrides defined in message header
BREEP_DECLARE_TYPE(Message);

/**
 *
 *  @brief: This class provides an interface to connect, send and recieve messages
 *      on the capcoin network.
 *
 */

class NetworkManager {

private:
    unsigned short port_; //listening port
    breep::tcp::network* network_; //peer manager, managers connections with peers

    Blockchain* bc_;
    TransactionPool* txpool_;

public:

    /**
     *
     * Initalize all private member variables. Must run init() explicitly.
     *
     */ 
    NetworkManager(unsigned short port, Blockchain* bc, TransactionPool* txpool);

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
    void BroadcastString(std::string msg);

    /*
     *
     * Broadcast Message
     *
     */ 
    void BroadcastMessage(Message m);
    
    /**
     *
     * @brief:  Searches for longest bc and updates bc with it.
     * @detail: Sends a request for blockchain to the network.
     *          The longest chain with the most votes gets selected.
     *          This chain will replace/update nodes current chain
     *
     * @warning: This function only request block chain from one node
     *           And assumes that it is correct(the longest chain).
     *
     */
    void RequestAndUpdateBlockchain(); 

    /**
     *
     * This update private member variable port_
     * Note: It does not restart the connection onto this port
     *
     */
    void SetPort(unsigned short port);

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

    
    /**
    * Called when there is a connection or disconnection to the network
    */ 
    void connection_event(breep::tcp::network& network, const breep::tcp::peer& peer);

    /**
    * General string data listener
    */ 
    void str_recieved(breep::tcp::netdata_wrapper<std::string>& dw);

    /**
    *
    *
    *   @brief: A handler that parses incoming Messages
    *   @example: This handler will handle different types of message headers.
    *       For example, if the header for an incoming message is TRANSACTION.
    *       The handler will perform verify the incoming TRANSACTION information.
    *       From there on, it will post this request into the TxPool. 
    *   
        @info: Handles BLOCK, TRANSACTION, REQUEST_BLOCKCHAIN ....
    *   
    *
    */
    void message_recieved(breep::tcp::netdata_wrapper<Message>& dw);
    
    /**
     *
     *  @brief:     A helper function that parses messages with BLOCK type
     *  @assume:    Assumes Message has type BLOCK 
     *  @detail:    When this node recieves a new block, this function will update the
     *              transaction pool, UTxOutPool and blockchain.
     *
     */
    bool HandleBlockMessage(breep::tcp::netdata_wrapper<Message>& dw);
    
    /**
     *
     *  @brief:     A helper function that parses messages with TRANSACTION type
     *  @assume:    Assumes Message have type property TRANSACTION
     *  @detail:    When this node recieves a transaction request, this function will
     *              update the transaction pool with a new unverified transaction.
     *
     */
    bool HandleTransactionMessage(breep::tcp::netdata_wrapper<Message>& dw);
    
    /**
     *
     *  @brief:     A helper funciton that parses messages with REQUEST_BLOCKCHAIN type
     *  @assume:    Assumes Message have type property REQUEST_BLOCKCHAIN
     *  @detail:    Sends back to the socket requesting for the Blockchain, the blockchain
     *              stored in the node. The block chain is sent block per block.
     *              The starting index is an optional parameter that can be attached
     *              to the request. If it is present, it will be used as the starting index.
     *
     */
    bool HandleRequestBlockchainMessage(breep::tcp::netdata_wrapper<Message>& dw);
};

#include "../src/networkmanager.cpp"
#endif
