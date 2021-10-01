/**
 * \file hashset.h Set implementation based on hashtables.
 * 
 * The collection is backed by a vector, divided into logical chunks called buckets. A bucket marks a section of the vector - as one vector changes size, the others are shifted accordingly.
 * 
 * Thus, set data is still stored in a contiguous chunk of data that can be iterated.
 * 
 * Hashsets need a *hash function* and an *equals function*. The latter decides whether two elements are considered equal. The former should return the same hash value for equal items, and may return different values for non-equal items.
 * 
 * Passing a hash- and equals function is optional, see defaults in @ref typehandlers.h.
 * 
 * @see vector.h
 * @see typehandlers.h
 */

#ifndef _H_MACROCOL_HASHSET
#define _H_MACROCOL_HASHSET

#include <macrocol/types.h>

void* _mcc_hashset_create();
void* _mcc_hashset_create_ex(mcc_hash_fn_t hash_func, mcc_equals_fn_t equals_func, mcc_size_t buckets);
void _mcc_hashset_destroy(void* set);

void* _mcc_hashset_add(void* set, void* data, mcc_size_t item_size);
bool _mcc_hashset_find(void* set, void* data, mcc_size_t item_size, mcc_index_t* idx, mcc_index_t* bucket_idx);
bool _mcc_hashset_remove(void* set, void* data, mcc_size_t item_size);

mcc_size_t _mcc_hashset_size(void* set);

/**
 * Allocate empty hashset with default settings.
 * 
 * @returns set
 * 
 * @see mcc_hashset_create_ex
 */
#define mcc_hashset_create() _mcc_hashset_create()

/**
 * Allocate empty hashset with custom settings.
 * 
 * `hash_func` and `equals_func` are optional, defaults are defined in @ref typehandlers.h.
 * 
 * @param hash_func hashing function ( NULL for default )
 * @param equals_func equals function ( NULL for default )
 * @param buckets bucket count
 */
#define mcc_hashset_create_ex(hash_func, equals_func, buckets) _mcc_hashset_create_ex(hash_func, equals_func, buckets)

/**
 * Destroy set.
 * This will free heap space allocated for the set.
 * 
 * @param set set
 */
#define mcc_hashset_destroy(set) _mcc_hashset_destroy(set)

/**
 * Add a new element to the set.
 * If the set already contains the element, the set is not modified.
 * 
 * @param set target set
 * @param data element variable
 * @returns set
 */
#define mcc_hashset_add(set, data) _mcc_hashset_add(set, &(data), sizeof(*set))

/**
 * Check whether the element is already in the set.
 * 
 * @param set target set
 * @param data element variable
 * @returns `true` if the item is found; `false` otherwise
 */
#define mcc_hashset_contains(set, data) _mcc_hashset_find(set, &(data), sizeof(*set), NULL, NULL)

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
#define mcc_hashset_find(set, data, idx) _mcc_hashset_find(set, &(data), sizeof(*set), &(idx), NULL)

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
#define mcc_hashset_remove(set, data) _mcc_hashset_remove(set, &(data), sizeof(*set))

/**
 * Get the number of elements in the set.
 * 
 * @param set set
 * @returns set size
 */
#define mcc_hashset_size(set) _mcc_hashset_size(set)

#endif
