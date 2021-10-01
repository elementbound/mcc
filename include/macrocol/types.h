/**
 * \file types.h Common type definitions for macrocol.
 */

#ifndef _H_MACROCOL_TYPES
#define _H_MACROCOL_TYPES

#include <stdbool.h>
#include <stdint.h>

//! Type representing sizes.
typedef uint64_t mcc_size_t;

/**
 * Type representing indices.
 * Must be able to hold at least the same values as {@link mcc_size_t}.
 */
typedef uint64_t mcc_index_t;

typedef uint_fast32_t mcc_hash_t;

/**
 * Comparison callback type.
 * @param pa pointer to left value
 * @param pb pointer to right value
 * @param size item size in bytes
 * 
 * @returns \<0 if *pa \< *pb
 * @returns \>0 if *pa \> *pb
 * @returns 0 if *pa == *pb
*/
typedef int (*mcc_compare_fn_t)(const void*, const void*, mcc_size_t);

/**
 * Equality callback type.
 * 
 * Very similar to {@ref mcc_compare_fn_t} so comparison implementations can be reused as equality.
 * 
 * The difference being, for equality functions the result sign is irrelevant, while for comparison functions it bears meaning.
 * 
 * @param pa pointer to left value
 * @param pb pointer to right value
 * @param size item size in bytes
 * 
 * @returns 0 if equals; non-zero if not
 */
typedef int (*mcc_equals_fn_t)(const void*, const void*, mcc_size_t);

/**
 * Hash callback type.
 * 
 * If two values are considered equal, the hash function *should* return the same values.
 * 
 * If two values are considered non-equal, the hash function *may* return different values.
 * 
 * @param pv pointer to value
 * @param size item size in bytes
 */
typedef mcc_hash_t (*mcc_hash_fn_t)(const void*, mcc_size_t);

#endif
