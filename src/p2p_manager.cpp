#include "p2p_manager.h"

P2P_Manager::P2P_Manager(Blockchain* blockchain/*, TransactionPool* pool*/, unsigned short port) {

    //Initialize client config vars
    port_ = port;

    //Create peer manager object
    network_ = new breep::tcp::network(static_cast<unsigned short>(port_));

    //Initial data source locations
    bc_ = blockchain;
    //txpool_ = pool;
}

void P2P_Manager::Init() {
    
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

void P2P_Manager::OpenListeners() {
    RequestManager request_manager;
    //Adding Listeners
    
    //Data listener for strings
    network_->add_data_listener<std::string>([&request_manager](breep::tcp::netdata_wrapper<std::string>& dw) -> void {
                request_manager.str_recieved(dw);
            });
    
    //Data listener for capcoin messages
    network_->add_data_listener<Message>([&request_manager](breep::tcp::netdata_wrapper<Message>& dw) -> void {
                request_manager.message_recieved(dw);
            });

    /**
     *
     * REQUIRED: These listeners are for handling connections and disconnection
     *
     */ 
    network_->add_connection_listener([&request_manager](breep::tcp::network &net, const breep::tcp::peer& peer) -> void {
                request_manager.connection_event(net, peer);
            });
    network_->add_disconnection_listener([&request_manager](breep::tcp::network &net, const breep::tcp::peer& peer) -> void {
                request_manager.connection_event(net, peer);
            });


}

void P2P_Manager::Close() {
    Disconnect();
}

bool P2P_Manager::AddPeer(std::string address, unsigned short port) {
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

void P2P_Manager::BroadcastMessage(std::string msg) {
    //Send message information to each peer
    network_->send_object(msg);
}

void P2P_Manager::BroadcastM(Message m) {
    network_->send_object(m);
}

void P2P_Manager::BroadcastBlock(Block& block) {
    //Serialize block into JSON data
    Serialize s(block);
    std::string data = s.toString();
    BroadcastMessage(data);
}

std::string P2P_Manager::GetLastRecieved() {
    return "default";
}

void P2P_Manager::SetPort(unsigned short port) {
    port_ = port;
}

void P2P_Manager::SetBlockchain(Blockchain* blockchain) {
    bc_ = blockchain;
}

void P2P_Manager::SetTransactionPool(/*TransactionPool* pool*/) {
    //txpool_ = pool;
}

void P2P_Manager::Disconnect() {
    network_->disconnect();
}

void P2P_Manager::Run() {
    network_->awake();
}

/*
 *
 *      Request Manager
 *  
 */ 
RequestManager::RequestManager() {}

void RequestManager::connection_event(breep::tcp::network& network, const breep::tcp::peer& peer) {
    if(peer.is_connected()) {
        std::cout << "Peer connected" << std::endl;
    } else {
        std::cout << "Peer disconnected" << std::endl;
    }
}

void RequestManager::str_recieved(breep::tcp::netdata_wrapper<std::string>& dw) {
    std::cout << dw.source.id_as_string() << ":" << dw.data << std::endl;
}

void RequestManager::message_recieved(breep::tcp::netdata_wrapper<Message>& dw) {
    std::cout << "Message Recieved by Handler" << std::endl;
    std::cout << dw.data.type_ << " " << dw.data.data_ << std::endl;
}
