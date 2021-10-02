/**
 * \file typehandlers.h Default implementations for common operations.
 * 
 * This file contains comparison, hash and equals implementations, for generic ( byte string ) and string values.
 * 
 * When working with collections of pointer types ( e.g. `char*` ), these functions receive a pointer to them ( `char**` ), so a simple `memcmp` is not enough, as that would compare the addresses and not the actual contents.
 * 
 * The same applies to collections of types with pointers - i.e. structs with pointers inside that should be taken into account.
 */

#ifndef _H_MCC_TYPEHANDLERS
#define _H_MCC_TYPEHANDLERS

#include <mcc/types.h>

/**
 * Generic comparison implementation.
 * Compares blocks of memory byte by byte.
 * 
 * @param pa pointer to left value
 * @param pb pointer to right value
 * @param item_size item size
 * @returns \<0 if a \< b
 * @returns \>0 if a \> b
 * @returns 0 if a == b
 */
int mcc_generic_compare(const void* pa, const void* pb, mcc_size_t item_size);

/**
 * String comparison implementation.
 * 
 * @param pa pointer to left value
 * @param pb pointer to right value
 * @param item_size item size
 * @returns \<0 if a \< b
 * @returns \>0 if a \> b
 * @returns 0 if a == b
 */
int mcc_string_compare(const void* pa, const void* pb, mcc_size_t item_size);

/**
 * Generic equality implementation.
 * Checks for equality byte by byte.
 * 
 * @param pa pointer to left value
 * @param pb pointer to right value
 * @param item_size item size
 * @returns !=0 if a != b
 * @returns 0 if a == b
 */
int mcc_generic_equals(const void* pa, const void* pb, mcc_size_t item_size);

/**
 * String equality implementation.
 * 
 * @param pa pointer to left value
 * @param pb pointer to right value
 * @param item_size item size
 * @returns !=0 if a != b
 * @returns 0 if a == b
 */
int mcc_string_equals(const void* pa, const void* pb, mcc_size_t item_size);

/**
 * Generic hash implementation.
 * Calculates djb2 hash byte by byte.
 * 
 * @param pa pointer value
 * @param item_size item size
 * @returns hash
 */
mcc_hash_t mcc_generic_hash(const void* pv, mcc_size_t item_size);

/**
 * String hash implementation.
 * Calculates djb2 hash based on string value.
 * 
 * @param pa pointer value
 * @param item_size item size
 * @returns hash
 */
mcc_hash_t mcc_string_hash(const void* pv, mcc_size_t item_size);

#endif
