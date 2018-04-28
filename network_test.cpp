#include "blockchain.h"
#include "p2p_manager.h"


int main(int argc, char* argv[]) {


        
    Blockchain bc;
    unsigned short p = 15465;
    if ( argc >= 2 ) {
        p = atoi(argv[1]);
    }
    std::cout << "====================================" << std::endl;
    std::cout << "Listening from port " << p << std::endl;
    std::cout << "====================================" << std::endl;
    
    P2P_Manager net(&bc,p);
    net.init();
    if (argc == 2) {
        net.run();
    }

    //New Peer Address
    std::string new_add = "127.0.0.1";
    unsigned short new_port = 1;
    
    std::cout << argc << std::endl;
    if(argc == 3 ) {
        std::cout << "Three Params" << std::endl;
        new_port = atoi(argv[2]);
        net.AddPeer(new_add,new_port);
    }

    std::string ans = "";
    while(true) {
        std::getline(std::cin, ans);
        if(ans == "/q") {
           std::cout << "Leaving..." << std::endl;
           break;
        } else {
            net.send_to_all(ans);
        }
    }

    net.Close();
}
