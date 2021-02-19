#include "block.h"

#include <cstring>

extern "C" {
  #include "../crypto/sha-256.h"
}


/*
 * copy one transaction into another
*/
static void copy_transaction(Block::Transaction &dest, const Block::Transaction &src) {
  strcpy(dest.sender, src.sender);
  strcpy(dest.reciever, src.reciever);

  dest.amount = src.amount;
}


/*
 * default constructor
 * not going to be used implicitly by me, 
 * but for initialising the LLL in the blockchain itself
*/
Block::Block(void) {
  this->timestamp = 0;

  memset(&this->data, 0x00, sizeof this->data);
  memset(this->hash, 0x00, sizeof this->hash);
  memset(this->previous_hash, 0x00, sizeof this->previous_hash);
}


/*
 * create a populated block
*/
Block::Block(Transaction &data, uint64_t timestamp) {
  copy_transaction(this->data, data);
  this->timestamp = timestamp;

  memset(this->hash, 0x00, sizeof this->hash);
  memset(this->previous_hash, 0x00, sizeof this->previous_hash);
}


/*
 *  hash the current block, with respect to the previous block. 
 *  just hash entire contents of the class, this will hold integrity in the
 *  chain becuase we're including the previous block's hash in the class's 
 *  data
*/
void Block::hash_block(const uint8_t previous_hash[32]) {
  memcpy(this->previous_hash, previous_hash, sizeof(uint8_t[32]));
  calc_sha_256(this->hash, this, sizeof this); /* just hash the entire class :O nice and simple */
}


/*
 * Copy one block to another
*/
void Block::operator=(const Block &src) {
  memcpy(this->hash, src.hash, sizeof(uint8_t[32]));
  memcpy(this->previous_hash, src.previous_hash, sizeof(uint8_t[32]));

  copy_transaction(this->data, src.data);
  this->timestamp = src.timestamp;
}