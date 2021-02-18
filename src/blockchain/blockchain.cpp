#include "blockchain.h"
#include <cstring>

/* all we need to do in the constructor is set the head pointer to null */
BlockChain::BlockChain(void) : head(NULL) {}
BlockChain::~BlockChain(void) { /* deallocate list */
  node *tmp;
  while(this->head) {
    tmp = this->head;
    this->head = this->head->next;

    delete tmp;
  }
}


/* add a block to the chain, hash it then add it. */
void BlockChain::add_block(Block &to_add) {
  /* first we hash the new block, grabbing the previous hash if it exists */
  if (!this->head) { /* genesis block, set the previous hash to zero */
    uint8_t previous_hash[32];
    memset(previous_hash, 0x00, sizeof(previous_hash));

    to_add.hash_block(previous_hash);
  } else { /* there is a previous block, grab it's hash and then hash the block to be added */
    to_add.hash_block(this->head->data.get_hash());
  }

  /* now we add to the LLL */
  node *tmp = this->head;
  
  this->head = new node;
  this->head->data = to_add;
  this->head->next = tmp;
}