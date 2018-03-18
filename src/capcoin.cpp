#include "../lib/block.h"
#include "../lib/blockchain.h"

#include <iostream>

using namespace std;

int main() {
    cout << "Hello World!" << endl;

    Blockchain bc;
    Block genBlock = bc.GetLastBlock();
    cout << "HashMatchesDifficulty: " << bc.HashMatchesDifficulty("0012321321312321",2) << endl;
    

    return 0;
}
