#ifndef __BLOCK_CHAIN_H__
#define __BLOCK_CHAIN_H__

#include "block.h"

/* 
 * represents the entire block chain, just a simple lll
 * the head pointer always points to the most recent block for efficiency.
*/
class BlockChain {
public:
  BlockChain(void); /* constructor */
  ~BlockChain(void); /* destructor */

  /*
   * we only ever want to add to the list
   * removing from the list could ruin the entire integrity of the block chain.
   * this is because each blocks hash is based on the previous blocks hash
  */
  void add_block(Block &to_add);
  inline const Block get_latest_block(void) const { return this->head ?  this->head.data : Block(); }
private:
  struct node {
    Block data;
    node *next;
  };

  node *head;
};

#endif