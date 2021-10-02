/**
 * \file hashmap.h Map implementation based on hashtables.
 * 
 * The collection is backed by two variables - the keys being a hashset, and the values being stored in a vector.
 * The values are ordered the same way as the keys, so using the same index for both yields a key-value association.
 * 
 * To store and find keys, the hashmap needs a *hash* and an *equality* function.
 * These are optional, defaults are provided in @ref typehandlers.h.
 * 
 * @see hashset.h
 * @see vector.h
 */

#ifndef _H_MACROCOL_HASHMAP
#define _H_MACROCOL_HASHMAP

#include <macrocol/types.h>

void _mcc_hashmap_create(void** keys, void** values);
void _mcc_hashmap_create_ex(void** keys, void** values, mcc_hash_fn_t hash_func, mcc_equals_fn_t equals_func, mcc_size_t buckets);
void _mcc_hashmap_destroy(void** keys, void** values);

void _mcc_hashmap_set(void** keys, void** values, void* key, void* value, mcc_size_t key_size, mcc_size_t value_size);
bool _mcc_hashmap_has(void** keys, void** values, void* key, mcc_size_t key_size);
void* _mcc_hashmap_get(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size);
bool _mcc_hashmap_remove(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size);

mcc_size_t _mcc_hashmap_size(void** keys, void** values);

/**
 * Allocate an empty map on the heap with default settings.
 * The backing hashset and vector are stored in the parameter variables.
 * 
 * For extended configuration, use @ref mcc_hashmap_create_ex.
 * 
 * @param keys keys variable
 * @param values values variable
 */
#define mcc_hashmap_create(keys, values) _mcc_hashmap_create((void**)(&(keys)), (void**)(&(values)))

/**
 * Allocate an empty map on the heap with custom settings.
 * The backing hashset and vector are stored in the parameter variables.
 * 
 * @param keys keys variable
 * @param values values variable
 * @param hash_func hashing function
 * @param equals_func equals function
 * @param buckets number of buckets to use
 */
#define mcc_hashmap_create_ex(keys, values, hash_func, equals_func, buckets) _mcc_hashmap_create_ex((void**)(&keys), (void**)(&values), hash_func, equals_func, buckets)

/**
 * Destroy hashmap.
 * This will free all space allocated for the map. The param variables will be set to `NULL`.
 * 
 * @param keys keys variable
 * @param values values variable
 */
#define mcc_hashmap_destroy(keys, values) _mcc_hashmap_destroy((void**)(&(keys)), (void**)(&(values)))

/**
 * Set association in hashmap.
 * If the key is not yet known to the hashmap, a new entry will be created.
 * If the key is already known, the entry's value will be updated.
 * 
 * @param keys keys variable
 * @param values values variable
 * @param key entry's key variable
 * @param value entry's value variable
 */
#define mcc_hashmap_set(keys, values, key, value) _mcc_hashmap_set((void**)(&(keys)), (void**)(&(values)), &(key), &(value), sizeof(*(keys)), sizeof(*(values)))

/**
 * Check whether the key is known to the hashmap.
 * 
 * @param keys keys variable
 * @param values values variable
 * @param key entry's key variable
 * @returns `true` if the hashmap contains an entry with the key
 * @returns `false` otherwise
 */
#define mcc_hashmap_has(keys, values, key) _mcc_hashmap_has((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*(keys)))

/**
 * Find value based on key.
 * 
 * @param keys keys variable
 * @param values values variable
 * @param key entry's key variable
 * @returns pointer to value if key found
 * @returns `NULL` if key not found
 */
#define mcc_hashmap_get(keys, values, key) _mcc_hashmap_get((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*(keys)), sizeof(*(values)))

/**
 * Remove entry based on key.
 * If the hashmap contains an entry for the key, it will be removed. Otherwise, nothing is done.
 * 
 * Thus, this operation is idempotent - the result will always be a hashmap without the specified key.
 * 
 * @param keys keys variable
 * @param values values variable
 * @param key entry's key variable
 * @returns `true` if the hashmap was modified
 * @returns `false` otherwise
 */
#define mcc_hashmap_remove(keys, values, key) _mcc_hashmap_remove((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*(keys)), sizeof(*(values)))

/**
 * Get the number of entries in the hashmap.
 * 
 * @param keys keys variable
 * @param values values variable
 * @returns hashmap size
 */
#define mcc_hashmap_size(keys, values) _mcc_hashmap_size((void**)(&(keys)), (void**)(&(values)))

#endif
