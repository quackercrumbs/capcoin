#include "block.h"
#include "blockchain.h"

#include <iostream>

using namespace std;

int main() {
    cout << "Hello World!" << endl;

    Blockchain bc;
    Block genBlock = bc.GetLastBlock();
    cout << "HashMatchesDifficulty: " << bc.HashMatchesDifficulty("0012321321312321",2) << endl;
    cout << "Hello world" << endl;
    string calculatedHash = bc.CalculateHash(genBlock.GetIndex(), genBlock.GetPreviousHash(), genBlock.GetTimestamp(), genBlock.GetData(), genBlock.GetDifficulty(), genBlock.GetNonce());
    cout << calculatedHash << endl;
    cout << genBlock.GetHash() << endl;
    return 0;
}
