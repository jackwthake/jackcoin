#include <iostream>
#include "blockchain/block.h"

/*
 * What we need:
 * a chain of blocks
 * each block consists of the following:
 *  - a transaction
 *  - a timestamp
 *  - the previous transaction
 *  - the current blocks hash
 * 
 * each transaction contains the following:
 *  - sender's address
 *  - reciever's address
 *  - amount
*/

int main(int argc, char **argv) {
  uint8_t hash[32];
  memset(hash, 0x00, sizeof(uint8_t[32]));

  Block::Transaction tr = {"hello", "world", 35};
  Block block(tr, 100);

  block.hash_block(hash);
  return EXIT_SUCCESS;
}