#ifndef MINER_H
#define MINER_H

#include "transactionpool.h"
#include "blockchain.h"

class Miner{
public:
  //Miner takes a blockchain to add blocks onto, as well as an address to reward coins to
  Miner(Blockchain* chain, std::string address);

  void mine(bool& killMiner, TransactionPool& pool);
  
  /**
   *
   * @brief             A routine for mining blocks, designed to be used in a thread.
   * @details           First the routine will create a coinbase transaction for the miner
   *                    Then it will package transactions from the transaction pool for the
   *                    block. The packaging routine will be interrupted when a signal to
   *                    kill the miner is activated.
   *                    If there was no interruption, the packaged transactions will be handed
   *                    off to perform the mining operation on the new block. Along with the
   *                    transactions, the signal is passed down to the mining operation. The
   *                    purpose of this is to cancel the mining operation when a signal to
   *                    stop (killMiner) mining is activated.
   *
   * @param killMiner   The signal that will be modified by other processes. This signal is
   *                    used to tell kill mining operation.
   *
   * @param pool        A reference to the transaction pool, where the miner will draw
   *                    transactions from. And package the transaction into the mined block
   *
   */
  void mine_loop(bool& killMiner, TransactionPool& pool);

private:
  //A reference to the blockchain
  Blockchain* chain_;

  //The miners address, where the reward is sent to.
  std::string address_;
};

#endif
