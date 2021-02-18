#include "blockchain.h"
#include <cstring>

BlockChain::BlockChain(void) : head(NULL) {}
BlockChain::~BlockChain(void) {
  node *tmp;
  while(this->head) {
    tmp = this->head;
    this->head = this->head->next;

    delete tmp;
  }
}

void BlockChain::add_block(Block &to_add) {
  /* first we hash the new block, grabbing the previous hash if it exists */
  if (!this->head) {
    uint8_t previous_hash[32];
    memset(previous_hash, 0x00, sizeof(previous_hash));

    to_add.hash_block(previous_hash);
  } else {
    to_add.hash_block(this->head->data.get_hash());
  }

  /* now we add to the LLL */
  node *tmp = this->head;
  
  this->head = new node;
  this->head->data = to_add;
  this->head->next = tmp;
}