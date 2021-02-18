/*
 * The SHA-256 implementation can be found at:
 * https://github.com/amosnier/sha-2
*/ 

#ifndef __SHA_256__
#define __SHA_256__

void calc_sha_256(uint8_t hash[32], const void *input, size_t len);

#endif