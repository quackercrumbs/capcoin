#include "blockchain.h"
#include "p2p_manager.h"


int main(int argc, char* argv[]) {

    if ( argc < 2 ) {
        std::cout << "USAGE: ./bin/net_test<running port>" << std::endl;
        return 0;
    }
    unsigned short p = atoi(argv[1]);
    

    std::cout << "====================================" << std::endl;
    std::cout << "You're listening from port " << p << std::endl;
    std::cout << "====================================" << std::endl;
   
    Blockchain bc;
    P2P_Manager net(&bc,p);
    net.Init();
   
    //If the node is running as the initial node (starting up the first network)
    if (argc == 3) {
        if(strcmp(argv[2],"initial") == 0) {
            std::cout << "Your are running as the initial node" << std::endl;
            net.Run(); 
        }
    }
    std::string ans = "";
    std::cout << "Enter !h to display options" << std::endl;
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
            if(new_address == "localhost") {
                new_address = "127.0.0.1";
            }
            else if(new_address == "gale") {
                new_address = "159.89.42.192";
            }
            else if (new_address == "orien") {
                new_address = "167.99.12.102";
            }
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
        else if(ans == "!Message") {
            Message m = {"testMessage"};
            net.BroadcastM(m);
        }
        else {
            net.BroadcastMessage(ans);
        }
    }
    net.Close();
}
