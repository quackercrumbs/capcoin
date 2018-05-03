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

    //This is the configs for GALE (Server)
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
        if(success) { }
    }

    //Display number of successful connections from config file
    auto my_peers = network_->peers(); //Retrieves all peers connected
    std::cout << "Successfully connected to " << my_peers.size() << "/" << peer_details.size() << std::endl;
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

    /**
     *
     * REQUIRED: These listeners are for handling connections and disconnection
     *
     */ 
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
    //Attempt to connect to new peer
    std::cout << "Attempting connection with " << address << ":" << port << std::endl;  
    boost::asio::ip::address p_address = boost::asio::ip::address::from_string(address);
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
    //Send message information to each peer
    network_->send_object(msg);
}

void NetworkManager::BroadcastMessage(Message m) {
    network_->send_object(m);
}

std::string NetworkManager::GetLastRecieved() {
    return "default";
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
        std::cout << "Recieved a block!" << std::endl;
        //std::cout << "DATA: " << dw.data.data_ << std::endl;
        
        //TODO:
        //If this block has a bigger index than ours, 
        // Perform validation on blocks integretiy
        // If pass, append to chain, else ignore
        Block newBlock = JSONtoBlock(dw.data.data_);
        bc_->Push(newBlock);
    }
    else if(dw.data.type_ == "TRANSACTION") {
        std::cout << "Recieved a transaction" << std::endl;
        //std::cout << "DATA: " << dw.data.data_ << std::endl;
        Transaction* newTx = JSONtoDynamicTx(dw.data.data_);
        bool result = txpool_->AddTransaction(newTx);
    }
    else if(dw.data.type_ == "REQUEST_BLOCKCHAIN") {
        // This will return the entire blockchain, but skips the genesis block
        std::cout << "Recieved a request for the blockchain" << std::endl;
        //Retrieve block chain and send everyblock back to socket
        std::vector<Block> chain = bc_->GetChain();
        int i = 1; //Skipping the genesis block (TODO: Fix this)
        Serialize s;
        for(; i < chain.size(); i++) {
            std::cout << "Sending block " << i << "/" << chain.size()-1 << std::endl;
            Block block = chain[i];
            s(block);
            Message m = {"BLOCK", s.toString()};
            network_->send_object_to(dw.source, m);
        }
    }
    else {
        std::cout << "Unknown type recieved" << std::endl;
        std::cout << "TYPE: " << dw.data.type_ << std::endl;
        std::cout << "DATA: " << dw.data.data_ << std::endl;
    }
}
