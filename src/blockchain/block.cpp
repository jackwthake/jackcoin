#include "block.h"

#include <SHA256.h>
#include <ctime>
#include <iostream>

/*******************
 * Transaction class
*******************/

/* constructors */
Transaction::Transaction() : Transaction(nullptr, nullptr, 0) {}
Transaction::Transaction(char from_addr[33], char to_addr[33], uint64_t amount) {
  /* copy over send and recieve addresses */
  if (from_addr)
    strcpy(this->from_addr, from_addr);
  else
    memset(this->from_addr, 0x00, sizeof(char[33]));
  
  if (to_addr)
    strcpy(this->to_addr, to_addr);
  else
    memset(this->to_addr, 0x00, sizeof(char[33]));
  
  this->amount = amount;
  this->timestamp = time(NULL);
}


/* 
 * sign the transaction with the senders public key, 
 * ensuring you can only send from your own wallet
*/
void Transaction::sign(char signing_key[33]) {
  // TODO: Implement me
}


/*
 * check if a transaction is valid, based on its send and
 *  recieve address, amount and internal hash.
*/
bool Transaction::is_valid(void) {
  /* 
   * we only check the recieving address, because if the sender is NULL then 
   * it's assumed the transaction is a mining reward.
  */
  if (strcmp(this->to_addr, "") == 0 || amount <= 0)
    return false;
  
  return true;
}


/* convert a transaction to a string, for hashing */
Transaction::operator std::__1::string() const {
  std::string tr;
  
  tr.append(this->from_addr, strlen(this->from_addr));
  tr.append(this->to_addr, strlen(this->to_addr));

  tr.append(std::to_string(this->timestamp));
  tr.append(std::to_string(this->amount));

  return tr;
}



/*******************
 * Transaction Class
*******************/

/* Block constructors */
Block::Block(void) : Block(0) {}
Block::Block(uint64_t nonce) {
  /* allocate hash strings */
  this->block_hash = new char[Block::hash_length];
  this->previous_hash = new char[Block::hash_length];
  this->transaction_hash = new char[Block::hash_length];

  /* zero out hash strings */
  memset(this->block_hash, 0x00, Block::hash_length);
  memset(this->previous_hash, 0x00, Block::hash_length);
  memset(this->transaction_hash, 0x00, Block::hash_length);

  this->nonce = nonce;
  this->timestamp = time(NULL);
  this->transactions.clear();
}


/* deallocates strings */
Block::~Block(void) {
  delete []this->block_hash;
  delete []this->previous_hash;
  delete []this->transaction_hash;
}


/* add a transaction to the blocks list, if the passed transaction is valid */
bool Block::add_transaction(Transaction &tr) {
  if (!tr.is_valid())
    return false;

  this->transactions.push_front(tr);
  return true;
}


/* hash the block using the previous hash to preserve integrity */
bool Block::hash_block(char previous_hash[65]) {
  if (!previous_hash)
    return false;

  SHA256 transaction_sha, block_sha;
  
  memcpy(this->previous_hash, previous_hash, sizeof(char[65]));

  /* TODO: Hash all transactions in a block properly */
  transaction_sha.update("Transactions");
  strcpy(this->transaction_hash, SHA256::toString(transaction_sha.digest()).c_str());

  block_sha.update(*this);
  strcpy(this->block_hash, SHA256::toString(block_sha.digest()).c_str());

  return true;
}


/* verify the current block, true if verified. */
bool Block::verify_block(void) {
  SHA256 sha;
  sha.update(*this);

  if (strcmp(SHA256::toString(sha.digest()).c_str(), this->block_hash) != 0)
    return false;

  return true;
}


/* convert a block to a string representation, used for hashing */
Block::operator std::__1::string() const {
  std::string blk;

  blk.append(this->previous_hash, strlen(this->previous_hash));
  blk.append(this->transaction_hash, strlen(this->transaction_hash));

  blk.append(std::to_string(this->timestamp));
  blk.append(std::to_string(this->nonce));

  return blk;
}