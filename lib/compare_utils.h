#include "txin.h"
#include "txout.h"
#include "utxout.h"
#include "transaction.h"
#include "block.h"

bool compareUTxOut(UnspentTxOut left, UnspentTxOut right);

bool compareTxIn(TxIn left, TxIn right);

bool compareTxOut(TxOut left, TxOut right);

bool compareTxInList(std::vector<TxIn> left, std::vector<TxIn> right);

bool compareTxOutList(std::vector<TxOut> left, std::vector<TxOut> right);

bool compareTransaction(Transaction left, Transaction right);

bool compareBlock(Block left, Block right);
