#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <cstdint>
#include <list>

/*
 * holds the basic information of a single transaction on the network.
*/
class Transaction {
public:
  Transaction();
  Transaction(char from_addr[33], char to_addr[33], uint64_t amount);

  void sign(char signing_key[33]);
  bool is_valid(void);

  /* for hashing */
  operator std::string() const;
private:
  char from_addr[33], to_addr[33];
  uint64_t amount, timestamp;
};


/*
 * a block of transactions, holds all information pertaining to a given block.
 * the block is responsible for hashing, and validating itself.
*/
class Block {
public:
  Block();
  Block(uint64_t nonce);
  ~Block();

  bool add_transaction(Transaction &tr);
  bool hash_block(char *previous_hash);
  bool verify_block(void);

  inline const char *get_hash(void) const { return this->block_hash; };
  inline const char *get_previous_hash(void) const { return  this->previous_hash; };
  inline const char *get_transaction_hash(void) const { return this->transaction_hash; }
  inline const std::list<Transaction> &get_transactions(void) const { return this->transactions; };

  /* for hashing */
  operator std::string() const;

  static const unsigned hash_length = 65;
private:
  char *block_hash, *previous_hash, *transaction_hash;
  uint64_t timestamp, nonce;
  std::list<Transaction> transactions;
};

#endif