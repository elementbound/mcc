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

#endif
