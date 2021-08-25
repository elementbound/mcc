#ifndef _H_MACROCOL_TYPES
#define _H_MACROCOL_TYPES

#include <stdbool.h>
#include <stdint.h>

typedef uint64_t mcc_size_t;
typedef uint64_t mcc_index_t;

typedef int (*mcc_compare_fn_t)(const void*, const void*, mcc_size_t);

#endif
