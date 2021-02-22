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
  Transaction tr("from", "to", 5);
  std::cout << tr.operator std::__1::string() << std::endl << std::endl;

  Block blk(5);
  blk.add_transaction(tr);
  std::cout << "Block string representation before hashing: " << blk.operator std::__1::string() << std::endl;
  blk.hash_block("hash");
  std::cout << "BLock string representation after hashing:  " << blk.operator std::__1::string() << std::endl;
  std::cout << std::endl << "Block Hash: " << blk.get_hash() << std::endl;
  std::cout << std::endl << "Previous Block Hash: " << blk.get_previous_hash() << std::endl;
  std::cout << std::endl << "Block transaction Hash: " << blk.get_transaction_hash() << std::endl;
  std::cout << (blk.verify_block() ? "Block Verified." : "Block not verified.") << std::endl;
  std::cout << std::endl;
}