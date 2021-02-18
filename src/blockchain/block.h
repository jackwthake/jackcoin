#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <stdint.h>

/*
 * One block in the block chain,
 * Contains information for one transaction.
*/
class Block {
public:
  /*
  * Imbedded structure for one transaction.
  */
  struct Transaction {
    char sender[50], reciever[50];
    unsigned amount;
  };

  Block(void);
  Block(Transaction &data, uint64_t timestamp);

  /* hash the current block, with respect to the previous block. */
  void hash_block(uint8_t previous_hash[32]);

  /* get the hash of this block */
  const uint8_t *get_hash() const;
private:
  uint64_t timestamp;
  uint8_t hash[32], previous_hash[32];
  Transaction data;
};

#endif