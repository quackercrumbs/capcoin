#include "utxout.h"

UnspentTxOut::UnspentTxOut(std::string txOutId, std::string address, size_t txOutIndex, size_t amount):
                txOutId_{txOutId}, address_{address}, txOutIndex_{txOutIndex}, amount_{amount}{}
