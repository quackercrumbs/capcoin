#include "fullNode.h"
#include <iostream>

FullNode::FullNode(Blockchain * bc, NetworkManager * nw, Wallet * wa, TransactionPool * transactionpool, bool* killMiner):wallet(wa){
  blockchain = bc;
  network = nw;
  wallet = wa;
  txpool = transactionpool;
  killMiner_ = killMiner;
}

bool FullNode::updateChain(){

  // Request the blockchain from one peer
  // Request BC starting from current BC index  
  network->RequestAndUpdateBlockchain();

  /*
  std::cout << "[fullnode-network]: \"Broadcasting\" request to server for blockchain" << std::endl;
  std::string request = "\"REQUEST\":";
  //Assuming that our chain height matches that of the server
  //send request with starting at the next index (which is the height)
  request += std::to_string(blockchain->GetHeight());
  std::cout << "[fullnode-network]: Sending " << request << std::endl;
  network->broadcastMessage(request);
>>>>>>> master
  */
  return false;
  /*
    //listen for responses, perhaps for a reply that states the size of the current chain
    //for(i = 0; i < current chain size; i++)
      //wait for a message, attempt to parse it into the chain.
      //if constant failures, that means that at some stage, a block was lost, break and try again

  }*/
}

bool FullNode::requestHeight() {
    network->RequestBlockchainHeight();
    return true;
}

bool FullNode::updateTransactionPool() {
    network->RequestAndUpdateTransactionPool();
    return false;
}

void FullNode::run(){
  while(1){
    std::cout << std::endl;
    displayMenu();
    std::cout << "please make a selection" << std::endl;
    std::string selection;
    std::cin >> selection;

    if(selection == "O" || selection == "o" ){

      // this screen will display the current balance, and any recent transactions by this node
      std::cout << "***************************************************************************" << std::endl;
      std::cout << "*                                                                         *" << std::endl;
      std::cout << "*    Balance:                                               ";
      std::cout<<std::fixed << std::setprecision(7) << std::setw(14) << wallet->Balance() << "*" << std::endl;
      std::cout << "*                                                                         *" << std::endl;
      std::cout << "*    Address:                                                             *" << std::endl;
      std::cout << "*       "<<                     std::setw(66) << wallet->GetAddress() << "*" << std::endl;
      std::cout << "*                                                                         *" << std::endl;
      std::cout << "*    Recent Transactions:                                                 *" << std::endl;
      std::cout << "*                                                                         *" << std::endl;
      std::cout << "***************************************************************************" << std::endl << std::endl;

      // display the last incoming message, as a string.  This is for testing purposes only
      //std::cout << "last received is: " << network->getLastReceived() << std::endl;
    }
    else if(selection == "S" || selection == "s" ){

      // prompt user for information to send a transaction
      bool correct = false;

      while(!correct){

        std::cout << "***************************************************************************" << std::endl;
        std::cout << "*                                                                         *" << std::endl;
        std::cout << "*    Please Enter a CapCoin Address to Send to                            *" << std::endl;
        std::cout << "*                                                                         *" << std::endl;
        std::cout << "***************************************************************************" << std::endl;

        std::string address;
        std::cin >> address;

        std::cout << "***************************************************************************" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Pay To: " << address << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Please enter amount to send" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "***************************************************************************" << std::endl;

        double amt;

        std::cin >> amt;

        while( std::cin.fail() ){
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
              std::cout << "***************************************************************************" << std::endl;
              std::cout << "*    Input not valid. Please enter a number." << std::endl;
              std::cout << "***************************************************************************" << std::endl;
              std::cin >> amt;
          }

        std::cout << "***************************************************************************" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Pay To: " << address << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Amount: " << amt << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "*    Is This Correct? (Y/N or X to Exit)" << std::endl;
        std::cout << "*" << std::endl;
        std::cout << "***************************************************************************" << std::endl;

        std::string response;
        std::cin >> response;

        if(response == "X" || response == "x"){
          break;
        }
        else if(response == "Y" || response == "y"){
          correct = true;
          //Creating a fake transaction and send as a block
          std::cout << "isWalletActive: " << wallet->isWalletActive() << std::endl;

          //Use the wallet to create a transaction
          Transaction * NewTxn = wallet->createTransaction(address,amt);
          //Check if the transaction generated is null
          //If null, transaction was invalid
          if(NewTxn != nullptr) {
              Serialize s(*NewTxn);
              Message request = {"TRANSACTION",s.toString()};
              network->BroadcastMessage(request);
              txpool->push(*NewTxn);
              std::cout << "***************************************************************************" << std::endl;
              std::cout << "*    Transaction Sent!" << std::endl;
              std::cout << "***************************************************************************" << std::endl;
          }
        }
      }
    }
    else if(selection == "T" || selection == "t" ){
      // This could be used to display the current transaction pool
      displayTransactionPool();
    }
    else if(selection == "H" || selection == "h" ){
      // general help menu.  Might not be necessary
      std::cout << "run help" << std::endl;
    }
    else if(selection == "BC" || selection == "bc") {
      displayBlockchain();
    }
    else if(selection == "LB" || selection == "lb") {
      displayLastBlock();
    }
    else if(selection == "CC" || selection == "cc") {
        std::cout << "Enter node ip: " << std::endl;
        std::string new_address; 
        std::getline(std::cin, new_address); //TODO: fix, some reason this is required
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
        std::string ans;
        std::cout << "Enter node port: " << std::endl;
        std::getline(std::cin, ans);
        unsigned short new_port = atoi(ans.c_str());

        network->AddPeer(new_address, new_port);

    }
    else if(selection == "RBC" || selection == "rbc") {
        updateChain();        
    }
    else if(selection == "RTP" || selection == "rtp") {
        updateTransactionPool();
    }
    else if(selection == "HI") {
        requestHeight();
    }
    else if(selection == "TKM" || selection == "tkm") {
      *killMiner_ = !*killMiner_;
      std::cout << "kill Miner " << *killMiner_ << std::endl;
    }
    else{
      std::cout << "input not valid" << std::endl;
    }
  }
}

void FullNode::displayTransactionPool() {
    std::cout << "               __________________" << std::endl;
    std::cout << "==============| Transaction Pool |===============" << std::endl;
    std::cout << "               ------------------" << std::endl;
    std::cout << *txpool << std::endl;
}

void FullNode::displayLastBlock() {
    std::cout << "               ______________" << std::endl;
    std::cout << "==============| Latest Block |================" << std::endl;
    std::cout << "               --------------" << std::endl;

    Block latest = blockchain->GetLastBlock();
    std::cout << latest << std::endl;
}

void FullNode::displayBlockchain() {
    std::cout << "                _________________" << std::endl;
    std::cout << "===============| Full Blockchain |===============" << std::endl;
    std::cout << "                -----------------" << std::endl;
    std::cout << *blockchain << std::endl;

}

void FullNode::welcome(){
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "*************************                          ************************" << std::endl;
  std::cout << "*************************    WELCOME TO CAPCOIN    ************************" << std::endl;
  std::cout << "*************************                          ************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl;
  std::cout << "***************************************************************************" << std::endl << std::endl;
}

void FullNode::displayMenu(){
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "                    MENU                       " << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "|        O - Overview      S - Send            |" << std::endl;
  std::cout << "|        T - Transactions  H - Help            |" << std::endl;
  std::cout << "|        BC - Blockchain   LB - Last Block     |" << std::endl;
  std::cout << "|        CC - Connect to a peer                |" << std::endl;
  std::cout << "|        RBC - Request BC                      |" << std::endl;
  std::cout << "|        RTP - Request Transaction Pool        |" << std::endl;
  std::cout << "|        TKM - Toggle Kill Miner Signal        |" << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
}
