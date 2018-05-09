#include "networkmanager.h"

NetworkManager::NetworkManager(unsigned short port, Blockchain* bc, TransactionPool* txpool) {

    //Initialize client config vars
    port_ = port;

    //Create peer manager object
    network_ = new breep::tcp::network(static_cast<unsigned short>(port_));

    //Initialize Blockchain
    bc_ = bc;
    
    //Initialize TxPool
    txpool_ = txpool;
}

void NetworkManager::Init() {
    
    std::cout << "================ Network Initalization ================" << std::endl; 
    OpenListeners(); 

    // Initialize a list of trusted nodes to connect to
    /*
    std::string server_string = "159.89.42.192";
    size_t server_port = 1234;
    std::pair<std::string, size_t> server = {server_string,server_port};
    */

    std::string local_server_string = "127.0.0.1";
    size_t local_server_port = 5555;
    std::pair<std::string, unsigned short> local_server = {local_server_string,local_server_port};
    
    //Collection of peer configs
    std::vector<std::pair<std::string, unsigned short>> peer_details = {local_server};
    std::cout << peer_details.size() << " connection configs loaded." << std::endl;

    //Initalize all peer connections
    for (auto peer = peer_details.begin(); peer != peer_details.end(); ++peer) {
        std::string raw_address = peer->first;
        unsigned short p_port = peer->second;
        //attempt connection with peer
        bool success = AddPeer(raw_address, p_port);
        // If successfully connect to a peer, we are done and connect to the entire network
        if(success) {
            break;
        }
    }

    //Display number of successful connections from config file
    auto my_peers = network_->peers(); //Retrieves all peers connected
    std::cout << "Successfully connected to " << my_peers.size() << " peers."  << std::endl;
    std::cout << "========== Network Initalization Complete =============" << std::endl;
}

void NetworkManager::OpenListeners() {
    //Data listener for strings
    network_->add_data_listener<std::string>([this](breep::tcp::netdata_wrapper<std::string>& dw) -> void {
                str_recieved(dw);
            });
    
    //Data listener for capcoin messages
    network_->add_data_listener<Message>([this](breep::tcp::netdata_wrapper<Message>& dw) -> void {
                message_recieved(dw);
            });

    //REQUIRED: These listeners are for handling connections and disconnection
    network_->add_connection_listener([this](breep::tcp::network &net, const breep::tcp::peer& peer) -> void {
                connection_event(net, peer);
            });
    network_->add_disconnection_listener([this](breep::tcp::network &net, const breep::tcp::peer& peer) -> void {
                connection_event(net, peer);
            });


}

void NetworkManager::Close() {
    Disconnect();
}

bool NetworkManager::AddPeer(std::string address, unsigned short port) {
    //@brief: Attempt to connect to new peer
    std::cout << "===================================================" << std::endl;
    std::cout << "Attempting connection with " << address << ":" << port << std::endl;  
    //convert string address to a boost ip address type
    boost::asio::ip::address p_address = boost::asio::ip::address::from_string(address);
    //attempt a connection to provided address and port
    if(!network_->connect(p_address,port)) {
        //Failed to connect
        //TO DO: Try again one more time
        std::cout << "Connection failed!" << std::endl;
        return false;
    }
    std::cout << "Connection successful!" << std::endl;
    return true;
}

void NetworkManager::BroadcastString(std::string msg) {
    //@brief: Send string to ever peer
    network_->send_object(msg);
}

void NetworkManager::BroadcastMessage(Message m) {
    //@brief: Send a message to every peer 
    network_->send_object(m);
}

void NetworkManager::RequestAndUpdateBlockchain() {
    //Retrieve a list of peers for the node
    auto node_peers = network_->peers();
    if(node_peers.empty())
        return;
    //Get the "first peer" from the collection
    auto first_peer = node_peers.begin();
    //Send the request to said peer
    Message request = {"REQUEST_BLOCKCHAIN", std::to_string(bc_->GetHeight())};
    network_->send_object_to((*first_peer).second,request);
}

void NetworkManager::SetPort(unsigned short port) {
    port_ = port;
}

void NetworkManager::Disconnect() {
    network_->disconnect();
}

void NetworkManager::Run() {
    network_->awake();
}

/**
 *
 *  Request Handlers
 *
 */

void NetworkManager::connection_event(breep::tcp::network& network, const breep::tcp::peer& peer) {
    if(peer.is_connected()) {
        std::cout << "Peer connected" << std::endl;
    } else {
        std::cout << "Peer disconnected" << std::endl;
    }
}

void NetworkManager::str_recieved(breep::tcp::netdata_wrapper<std::string>& dw) {
    std::cout << dw.source.id_as_string() << ":" << dw.data << std::endl;
}

void NetworkManager::message_recieved(breep::tcp::netdata_wrapper<Message>& dw) {
    if(dw.data.type_ == "BLOCK") {
        HandleBlockMessage(dw); 
    }
    else if(dw.data.type_ == "TRANSACTION") {
        HandleTransactionMessage(dw);
    }
    else if(dw.data.type_ == "REQUEST_BLOCKCHAIN") {
        HandleRequestBlockchainMessage(dw);
    }
    else {
        std::cout << "Unknown type recieved" << std::endl;
        std::cout << "TYPE: " << dw.data.type_ << std::endl;
        std::cout << "DATA: " << dw.data.data_ << std::endl;
    }
}

bool NetworkManager::HandleTransactionMessage(breep::tcp::netdata_wrapper<Message>& dw) {
    Transaction* newTx = JSONtoDynamicTx(dw.data.data_);
    bool result = txpool_->AddTransaction(newTx);
    return result;
}

bool NetworkManager::HandleUTxOut(breep::tcp::netdata_wrapper<Message>& dw) {
    return true;
}



bool NetworkManager::HandleBlockMessage(breep::tcp::netdata_wrapper<Message>& dw) {
    //TODO:
    //If this block has a bigger index than ours, 
    // Perform validation on blocks integretiy
    // If pass, append to chain, else ignore
    Block newBlock = JSONtoBlock(dw.data.data_);
    bc_->Push(newBlock);
    return true;
}

bool NetworkManager::HandleRequestBlockchainMessage(breep::tcp::netdata_wrapper<Message>& dw) {
    // Retrieve block chain and send blocks back to socket
    std::vector<Block> chain = bc_->GetChain();
    
    // Retrieve starting index from message.
    // Convert string data to int, then cast to size_t
    size_t i = 0;
    //first check if starting index is provided
    //if provided, then take it. else use default 0.
    if(dw.data.data_ != "")
        i = stoi(dw.data.data_); 

    //Begin sending process
    Serialize s;
    for(; i < chain.size(); i++) {
        std::cout << "Sending block " << i << "/" << chain.size()-1 << std::endl;
        Block block = chain[i];
        s(block); //serialize block data

        Message m = {"BLOCK", s.toString()};
        network_->send_object_to(dw.source, m); //send block message to socket
    }
    std::cout << "REQUEST BLOCKCHAIN complete." << std::endl;
    return true;
}

bool NetworkManager::HandleRequestTransactionPoolMessage(breep::tcp::netdata_wrapper<Message>& dw) {
    
    return true;
}

bool NetworkManager::HandleRequestUTxOutPoolMessage(breep::tcp::netdata_wrapper<Message>& dw) {
    return true;
}
