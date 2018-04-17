#include <iostream>
#include <string>
#include "../lib/transaction.h"
#include "../lib/txin.h"
#include "../lib/txout.h"
#include "../lib/utxout.h"
#include "../lib/utxoutpool.h"

int main(){
  UnspentTxOutPool alpha;

  UnspentTxOut a("86d5bc08c2eba828a8e3588e25ad26a312ce77f6ecc02e3500ba05607f49c935",
                "7f6598ae9d008f8261f59b7aa4bc43d9a65063471ebb7bd19e81c86b6381bbb6",
                1, 50);
  UnspentTxOut b("364aba675151243a1e105cee426271f843bd1bdd7ab822291fce8b8455d7c6e4",
                "0ce2c8f048623b76f77664fd8c6f57ff99ef0219289fa6b1ba1f3e40685fd0ba",
                2, 100);
  UnspentTxOut c("ce6b20ee7f7797e102f68d15099e7d5b0e8d4c50f98a7865ea168717539ec3aa",
                "c5c14f91fc2338a72118812a6e289a98a953dfa9077caef02f6cea31977c3f95",
                3, 150);
  alpha.AddTxn(a);
  alpha.AddTxn(b);
  alpha.AddTxn(c);

  TxIn in1("86d5bc08c2eba828a8e3588e25ad26a312ce77f6ecc02e3500ba05607f49c935", "asdasdasd", 1);
  TxOut out1("cb22789c9d5c344a10e0474f134db39e25eb3bbf5a1b1a5e89b507f15ea9519c", 50);

  TxIn in2("364aba675151243a1e105cee426271f843bd1bdd7ab822291fce8b8455d7c6e4", "asdfasdfasdf", 2);
  TxOut out2("cb22789c9d5c344a10e0474f134db39e25eb3bbf5a1b1a5e89b507f15ea9519c", 100);

  TxIn in3("ce6b20ee7f7797e102f68d15099e7d5b0e8d4c50f98a7865ea168717539ec3aa", "asdfadf", 3);
  TxOut out3("cb22789c9d5c344a10e0474f134db39e25eb3bbf5a1b1a5e89b507f15ea9519c", 150);

  std::vector<TxIn> ins{in1, in2, in3};
  std::vector<TxOut> outs{out1, out2, out3};
  Transaction first(ins, outs);

  if(first.Validate(alpha))
    std::cout<< "Success" << std::endl;
  else
    std::cout<< "We're shite out of luck" << std::endl;
}
