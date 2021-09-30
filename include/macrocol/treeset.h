/**
 * \file treeset.h Set implementation based on binary trees.
 * 
 * Similar to a vector, any operation that may invalidate the set pointer, will always return a valid one to use.
 * 
 * The collection is backed by a vector. Items are kept sorted as they arrive, based on the set's comparator function.
 * 
 * If no comparator function is provided, `memcmp` will be used.
 * 
 * @see vector.h
 */

#ifndef _H_MACROCOL_TREESET
#define _H_MACROCOL_TREESET

#include <macrocol/types.h>

void* _mcc_treeset_create();
void* _mcc_treeset_create_ex(mcc_compare_fn_t compare_fn);
void  _mcc_treeset_destroy(void* set);

void* _mcc_treeset_add(void* set, void* data, mcc_size_t item_size);
bool  _mcc_treeset_contains(void* set, void* data, mcc_size_t item_size, mcc_index_t* idx);
bool  _mcc_treeset_remove(void* set, void* data, mcc_size_t item_size);

mcc_index_t _mcc_treeset_lower_bound(void* set, void* data, mcc_size_t item_size);

mcc_size_t _mcc_treeset_size(void* set);

/**
 * Allocate an empty set on the heap.
 * 
 * @returns set
 */
#define mcc_treeset_create() _mcc_treeset_create()

/**
 * Allocate an empty set on the heap with custom comparator function.
 * 
 * @param comparator comparator function
 * @returns set
 * 
 * @see mcc_compare_fn_t
 */
#define mcc_treeset_create_ex(comparator) _mcc_treeset_create_ex(comparator)

/**
 * Add a new element to the set.
 * If the set already contains the element, the set is not modified.
 * 
 * @param set target set
 * @param data variable holding the element
 * @returns set
 */
#define mcc_treeset_add(set, data) _mcc_treeset_add(set, &(data), sizeof(*set))

/**
 * Check whether the element is already in the set.
 * 
 * @param set target set
 * @param data variable holding the element
 * @returns `true` if the item is found; `false` otherwise
 */
#define mcc_treeset_contains(set, data) _mcc_treeset_contains(set, &(data), sizeof(*set), NULL)

/**
 * Find element index in the set.
 * **Note** that the set is not required to keep the same order of items after changes.
 * 
 * If the item is found, the index is stored in `idx` and `true` is returned;
 * otherwise, `false` is returned, and the value pointed by `idx` is left as-is.
 * 
 * If `idx` is `NULL`, it is not used - however, it's recommended to call {@link mcc_treeset_contains}
 * in this case.
 * 
 * @param set set
 * @param data variable holding the element
 * @param idx pointer to store element index
 * @returns `true` if the item is found; `false` otherwise
 */
#define mcc_treeset_find(set, data, idx) _mcc_treeset_contains(set, &(data), sizeof(*set), idx)

/**
 * Remove element from the set.
 * If the element is not in the set, the set is not modified.
 * 
 * It is safe to call this method with the same element any number of times -
 * the result will always be a set without the given element.
 * 
 * @param set set
 * @param data variable holding the element
 * @returns `true` if the set was modified; `false` otherwise
 */
#define mcc_treeset_remove(set, data) _mcc_treeset_remove(set, &(data), sizeof(*set))

/**
 * Destroy set.
 * This will free the heap space allocated for the set.
 * 
 * @param set set
 */
#define mcc_treeset_destroy(set) _mcc_treeset_destroy(set)

/**
 * Get set size - the number of elements held.
 * 
 * @param set set
 * @returns set size
 */
#define mcc_treeset_size(set) _mcc_treeset_size(set)

#endif
