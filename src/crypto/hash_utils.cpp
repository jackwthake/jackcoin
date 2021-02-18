#include "hash_utils.h"

#include <stdio.h>
#include <cstring>

/* converts to uint64 for big endian systems */
#define to64b(arr) (((uint64_t)(((uint8_t *)(arr))[7]) <<  0)+\
                    ((uint64_t)(((uint8_t *)(arr))[6]) <<  8)+\
                    ((uint64_t)(((uint8_t *)(arr))[5]) << 16)+\
                    ((uint64_t)(((uint8_t *)(arr))[4]) << 24)+\
                    ((uint64_t)(((uint8_t *)(arr))[3]) << 32)+\
                    ((uint64_t)(((uint8_t *)(arr))[2]) << 40)+\
                    ((uint64_t)(((uint8_t *)(arr))[1]) << 48)+\
                    ((uint64_t)(((uint8_t *)(arr))[0]) << 56))


/* converts to uint64 for little endian systems */
#define to64l(arr) (((uint64_t)(((uint8_t *)(arr))[0]) <<  0)+\
                    ((uint64_t)(((uint8_t *)(arr))[1]) <<  8)+\
                    ((uint64_t)(((uint8_t *)(arr))[2]) << 16)+\
                    ((uint64_t)(((uint8_t *)(arr))[3]) << 24)+\
                    ((uint64_t)(((uint8_t *)(arr))[4]) << 32)+\
                    ((uint64_t)(((uint8_t *)(arr))[5]) << 40)+\
                    ((uint64_t)(((uint8_t *)(arr))[6]) << 48)+\
                    ((uint64_t)(((uint8_t *)(arr))[7]) << 56))


/* checks if system is big endian, used for converting to uint64 */
static bool is_big_endian(void) {
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}


/* converts any piece of data to a unisgned 64 bit integer */
uint64_t to_uint64(const void *arr) {
    return is_big_endian() ? to64b(arr) : to64l(arr);   
}


/* convert a hash intp a string */
void hash_to_string(char string[65], const uint8_t hash[32]) {
	size_t i;
	for (i = 0; i < 32; i++) {
		string += sprintf(string, "%02x", hash[i]);
	}
}	


/* get a numerical value for a string (add all ascii characters) */
unsigned str_to_int(char *str) {
  if (!str) return 0;

  unsigned acc = 0;
  for (int i = 0; i < strlen(str); ++i)
    acc += str[i];

  return acc;
}