#include "utxo.h"

UnspentTxOut::  UnspentTxOut(string txOutId, string address, size_t txOutIndex, size_t amount):
                txOutId_{txOutId}, address_{address}, txOutIndex_{txOutIndex}, amount_{amount}{}
