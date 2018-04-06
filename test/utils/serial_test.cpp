#include <iostream>
#include <string>
#include "transaction.h"
#include "txin.h"
#include "txout.h"
#include "serialize.h"
#include <iostream>

int main(){
  TxIn in1("a", "asdasdasd", 1);
  TxOut out1("b", 50);

  TxIn in2("c", "asdfasdfasdf", 2);
  TxOut out2("d", 100);

  TxIn in3("e", "asdfadf", 3);
  TxOut out3("f", 150);

  std::vector<TxIn> ins{in1, in2, in3};
  std::vector<TxOut> outs{out1, out2, out3};
  Transaction first(ins, outs);

  Serialize toJSON(first);
  std::cout << toJSON.toString() << std::endl;

}
