#include <iostream>
#include <string>
#include "transaction.h"
#include "txin.h"
#include "txout.h"
#include "serialize.h"
#include <iostream>

int main(){
  Serialize txToJSON;
  UnspentTxOut unspent("z", "y", 2, 50);

  txToJSON(unspent);
  std::cout << txToJSON.toString() << std::endl;
  UnspentTxOut deuxspent = JSONtoUTxO(txToJSON.toString());
  txToJSON(deuxspent);
  std::cout << txToJSON.toString() << std::endl;


  TxIn in1("a", "asdasdasd", 1);
  TxOut out1("b", 50);

  TxIn in2("c", "asdfasdfasdf", 2);
  TxOut out2("d", 100);

  TxIn in3("e", "asdfadf", 3);
  TxOut out3("f", 150);

  std::vector<TxIn> ins{in1, in2, in3};
  std::vector<TxOut> outs{out1, out2, out3};
  Transaction first(ins, outs);

  txToJSON(first);
  std::cout << txToJSON.toString() << std::endl;

  std::string txInSerial ="\"IN\":{\"ID\":\"a\",\"SIG\":\"asdasdasd\",\"INDEX\":\"1\"}";
  TxIn in4 = JSONtoTxIn(txInSerial);

  std::string txOutSerial ="\"OUT\":{\"AMOUNT\":\"50\",\"ADDRESS\":\"b\"}";
  TxOut out4 = JSONtoTxOut(txOutSerial);

  Transaction second = JSONtoTx(txToJSON.toString());
  txToJSON(second);
  std::cout << txToJSON.toString() << std::endl;

  std::vector<Transaction> GenTxns{first, second};
  Block Genesis(0, 1521001712, 0, 0, "", GenTxns);

  txToJSON(Genesis);
  std::cout << txToJSON.toString() << std::endl;
  Block gen2 = JSONtoBlock(txToJSON.toString());
  txToJSON(gen2);
  std::cout << txToJSON.toString() << std::endl;
}
