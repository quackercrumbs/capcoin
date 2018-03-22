UnspentTxOutPool:: UnspentTxOutPool(){}

TxOut* UnspentTxOutPool:: FindFromIn(const TxIn& input){
  TxOut* outptr = nullptr;
  for(UnspentTxOut out: uTxOuts_){
    if (out.txOutId_ == input.id_ && out.txOutIndex_ == input.index_)
      outptr = out;
  }
  return outptr;
}

