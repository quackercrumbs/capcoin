#ifndef MINER_H
#define MINER_H

#include "transactionpool.h"
#include "blockchain.h"
#include "network.h"
#include <thread>

class Miner{
public:
  
  /**
   *
   *
   * @brief:            Takes a reference to blockchain, transactionpool, killMiner signal,
   *                    and an address to where the rewarded coins are sent to
   *
   * @param: chain      The blockchain reference where mined blocks are generated to
   * @param: txpool     A reference to the transation pool, where the miner packages
   *                    transactions from.
   * @param: killMiner  A reference to a signal that tells the miner to stop mining ops
   * @param: address    The address where the reward of a mined block are sent to.
   *
   */
  Miner(Blockchain* chain, TransactionPool* txpool, Network* nw, bool* killMiner, std::string address);

  /**
   *
   * @brief:             A routine for mining blocks, designed to be used in a thread.
   * @details:           First the routine will create a coinbase transaction for the miner
   *                    Then it will package transactions from the transaction pool for the
   *                    block. The packaging routine will be interrupted when a signal to
   *                    kill the miner is activated.
   *                    If there was no interruption, the packaged transactions will be handed
   *                    off to perform the mining operation on the new block. Along with the
   *                    transactions, the signal is passed down to the mining operation. The
   *                    purpose of this is to cancel the mining operation when a signal to
   *                    stop (killMiner) mining is activated.
   *
   */
  void mine_loop();

  /**
   *
   * @brief:            Returns a thread that activates the mining routine
   * @details:          Create a thread that calls mine_loop()
   *
   */
  std::thread mineThread();


private:
  //A reference to the blockchain
  Blockchain* chain_;

  //A reference to the transaction pool (mempool)
  TransactionPool* txpool_;

  //A reference to the network
  Network* nw_;

  //A reference to the killMiner signal
  bool* killMiner_;

  //The miners address, where the reward is sent to.
  std::string address_;
};

#endif
