#ifndef __BLOCK_CHAIN_H__
#define __BLOCK_CHAIN_H__

#include "block.h"

class BlockChain {
public:
  BlockChain(void);
  ~BlockChain(void);

  void add_block(Block &to_add);
private:
  struct node {
    Block data;
    node *next;
  };

  node *head;
};

#endif