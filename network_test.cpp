#include "blockchain.h"
#include "networkmanager.h"


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
    NetworkManager net(p, &bc);
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
            Message m = {"GET","testMessage"};
            net.BroadcastMessage(m);
        }
        else if(ans == "!SBlock") {
            Message m = {"BLOCK",""};
            Block genBlock = bc.GetLastBlock();
            Serialize s(genBlock);
            m.data_ = s.toString();
            net.BroadcastMessage(m);
        }
        else if(ans == "!STransaction") {
            Message m = {"Transaction",""};
            TxIn in1("a", "asdasdasd", 1);
            TxOut out1("b", 50);

            TxIn in2("c", "asdfasdfasdf", 2);
            TxOut out2("d", 100);

            TxIn in3("e", "asdfadf", 3);
            TxOut out3("f", 150);

            std::vector<TxIn> ins{in1, in2, in3};
            std::vector<TxOut> outs{out1, out2, out3};
            Transaction first(ins, outs);
            Serialize s(first);
            m.data_ = s.toString();
            net.BroadcastMessage(m);
        }
        else {
            net.BroadcastString(ans);
        }
    }
    net.Close();
}
