#include "blockchain.h"
#include "p2p_manager.h"


int main(int argc, char* argv[]) {

    if ( argc < 2 ) {
        std::cout << "USAGE: ./bin/net_test<running port>" << std::endl;
        return 0;
    }
    unsigned short p = atoi(argv[1]);
         

    std::cout << "====================================" << std::endl;
    std::cout << "Listening from port " << p << std::endl;
    std::cout << "====================================" << std::endl;
   
    Blockchain bc;
    P2P_Manager net(&bc,p);
    net.init();
   
    //If the node is hosting (aka the inital node)  THIS IS REQUIRED
    if (argc == 3) {
        if(strcmp(argv[2],"initial") == 0) {
            std::cout << "Initial Node" << std::endl;
            net.run();
        }
    }
    std::string ans = "";
        while(true) {
            std::getline(std::cin, ans);
            if(ans == "!q") {
               std::cout << "Leaving..." << std::endl;
               break;
            } 
            else if(ans == "!connect") {
                std::cout << "Enter node ip: " << std::endl;
                std::string new_address; 
                std::getline(std::cin, new_address);
                
                std::cout << "Enter node port: " << std::endl;
                std::getline(std::cin, ans);
                unsigned short new_port = atoi(ans.c_str());

                net.AddPeer(new_address, new_port);
            }
            else if(ans == "!help") {
                std::cout << "!connect, form to connect to node" << std::endl;
                std::cout << "!q, exit node" << std::endl;
                std::cout << "!help, help menu" << std::endl;
            }
            else {
                net.send_to_all(ans);
            }
    }
    net.Close();
}
