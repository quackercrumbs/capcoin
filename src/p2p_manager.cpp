#include "p2p_manager.h"

P2P_Manager::P2P_Manager(Blockchain* blockchain/*, TransactionPool* pool*/, unsigned short port) {

    //Initialize client config vars
    port_ = port;

    //Create peer manager object
    peer_manager_ = new breep::tcp::peer_manager(static_cast<unsigned short>(port_));
    
    //Initial data source locations
    bc_ = blockchain;
    //txpool_ = pool;
}

void P2P_Manager::init() {
    
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
    auto my_peers = peer_manager_->peers(); //Retrieves all peers connected
    std::cout << "Successfully connected to " << my_peers.size() << "/" << peer_details.size() << std::endl;
    std::cout << "========== Network Initalization Complete =============" << std::endl;
}

void P2P_Manager::OpenListeners() {
     //Adding Listeners
    data_listener_id_ = peer_manager_->add_data_listener(timed_message());
    connection_listener_id_ = peer_manager_->add_connection_listener(&connection_disconnection);
    disconnection_listener_id_ = peer_manager_->add_disconnection_listener(&connection_disconnection);


}

void P2P_Manager::Close() {
    disconnect();
    peer_manager_->remove_data_listener(data_listener_id_);
    peer_manager_->remove_connection_listener(connection_listener_id_);
    peer_manager_->remove_disconnection_listener(disconnection_listener_id_);
}

bool P2P_Manager::AddPeer(std::string address, unsigned short port) {
    //Attempt to connect to new peer
    std::cout << "Attempting connection with " << address << ":" << port << std::endl;  
    boost::asio::ip::address p_address = boost::asio::ip::address::from_string(address);
    if(!peer_manager_->connect(p_address,port)) {
        //Failed to connect
        //TO DO: Try again one more time
        std::cout << "Connection failed!" << std::endl;
        return false;
    }
    std::cout << "Connection successful!" << std::endl;
    return true;
}

void P2P_Manager::broadcastMessage(std::string msg) {
    //Send message information to each peer
    peer_manager_->send_to_all(msg);
}

void P2P_Manager::broadcastBlock(Block& block) {
    //Serialize block into JSON data
    Serialize s(block);
    std::string data = s.toString();
    broadcastMessage(data);
}

std::string P2P_Manager::getLastRecieved() {
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

/*
 *
 *      Wrapper functions for peer manager
 *
 *
 */
void P2P_Manager::disconnect() {
    peer_manager_->disconnect();
}

void P2P_Manager::send_to_all(std::string msg) {
    peer_manager_->send_to_all(msg);
}

void P2P_Manager::run() {
    peer_manager_->run();
}

/*
 *
 *      For Message Listener
 *
 */
timed_message::timed_message(): m_starting_time{time(0)} {}

void timed_message::operator() (breep::tcp::peer_manager&, const breep::tcp::peer& source, breep::cuint8_random_iterator data, size_t data_size, bool) {
    //Calculate time of message
    time_t now = time(0) - m_starting_time;
    //Pretty print time of message
    std::cout << '[' << std::string(ctime(&now)).substr(14,5) << "] " << source.id_as_string().substr(0, 4) << ": ";
    
    // prints what he sent.
    for (; data_size > 0 ; --data_size) {
        std::cout << static_cast<char>(*data++);
    }
    std::cout << std::endl;
}

/*
 *
 *
 *      Listener Functions
 *
 *
 */ 
void connection_disconnection(breep::tcp::peer_manager&, const breep::tcp::peer& peer) {
    if(peer.is_connected()) {
        //someone connected
        std::cout << peer.id_as_string().substr(0,4) << " connected!" << std::endl;
    } else {
        std::cout << peer.id_as_string().substr(0,4) << " disconnected!" << std::endl;
    }
}
