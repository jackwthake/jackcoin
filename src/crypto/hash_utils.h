#ifndef __HASH_UTILS_H__
#define __HASH_UTILS_H__

#include <stdint.h>

extern uint64_t to_uint64(const void *arr);
extern void hash_to_string(char string[65], const uint8_t hash[32]);
extern unsigned str_to_int(char *str);

#endif