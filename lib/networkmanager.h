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
     * @warning: Currently this function only request block chain from one node
     *           And assumes that it is correct(the longest chain).
     *
     */
    void RequestAndUpdateBlockchain(); 

    /**
     *
     * @brief:  Queries its peer to update its transaction pool 
     * @detail: Sends a request for a transaction pool.
     *
     * @warning: Currently this function only request for a transaction pool to one peer 
     *           And assumes that it is correct (the most updated pool).
     *
     */
    void RequestAndUpdateTransactionPool(); 
    
    /**
    *
    * @brief:  Queries its peers to update its UTxOut Pool 
    * @detail: Sends a request for a UTxOutpool.
    *
    * @warning: Currently this function only request UTxOut pool from one peer
    *           And assumes that it is correct (the most updated pool).
    *
    */
    void RequestAndUpdateUTxOutPool(); 

    void RequestBlockchainHeight();

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
     *  @brief:     A helper function that parses messages with UTXOUT type
     *  @assume:    Assumes Message have type property UTXOUT 
     *  @detail:    When this node recieves a UTXOUT request, this function will
     *              update the utxoutpool with new utxouts.
     *
     */
    bool HandleUTxOutMessage(breep::tcp::netdata_wrapper<Message>& dw);
    
    /**
     *
     *  @brief:     A helper funciton that parses messages with REQUEST_BLOCKCHAIN type
     *  @assume:    Assumes Message have type property REQUEST_BLOCKCHAIN
     *  @detail:    Sends back to the socket requesting for the Blockchain, the blockchain
     *              stored in the node. The block chain is sent a block at a time.
     *              The starting index is an optional parameter that can be attached
     *              to the request. If it is present, it will be used as the starting index.
     *              This uses BLOCK requests to send blocks.
     *
     */
    bool HandleRequestBlockchainMessage(breep::tcp::netdata_wrapper<Message>& dw);

    /**
     *
     *  @brief:     A helper functio nthat parses messages with REQUEST_TRANSACTION_POOL type
     *  @assume:    Assumes Message have type property REQUEST_TRANSACTION_POOL
     *  @details:   Sends back to the socket requesting for TxPool, its current txpool.
     *              The TxPool is sent a transaction at a time. It uses TRANSACTION
     *              requests to send transactions.
     */
    bool HandleRequestTransactionPoolMessage(breep::tcp::netdata_wrapper<Message>& dw);

    /**
     *
     *  @brief:     A helper function that parses messages with REQUEST_UTXOUTPOOL type
     *  @assume:    Assumes Message have type property REQUEST_UTXOUTPOOL
     *  @details:   Sends back to the socket requesting for UTxOutPool, its current
     *              utxoutpool. The UTxOutPool is sent a utxout at a time. It uses
     *              UTXOUT requests to send UTxOut.
     */
    bool HandleRequestUTxOutPoolMessage(breep::tcp::netdata_wrapper<Message>& dw);

    bool HandleBlockchainHeightMessage(breep::tcp::netdata_wrapper<Message>& dw);

    bool HandleRequestBlockchainHeightMessage(breep::tcp::netdata_wrapper<Message>& dw);

};

#include "../src/networkmanager.cpp"
#endif
