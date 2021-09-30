/**
 * \file treemap.h Map implementation based on binary trees.
 * 
 * Treemaps are backed by two treesets, one storing the keys and one storing the associated values.
 * 
 * Compared to the other collections, treemaps are stored in two separate variables for the two backing sets,
 * and methods modify these variables directly instead of returning updated pointers.
 * 
 * Incoming entries are kept sorted based on the key comparator. If a treemap was created without specifying
 * a key comparator, `memcmp` is used. It's recommended to use custom comparators on pointer types
 * ( e.g. `char*` ), or types that contain pointers.
 * 
 * @see treeset.h
 */ 

#ifndef _H_MACROCOL_TREEMAP
#define _H_MACROCOL_TREEMAP

#include <macrocol/types.h>

void  _mcc_treemap_create(void** keys, void** values, mcc_compare_fn_t key_comparator);
void  _mcc_treemap_set(void** keys, void** values, void* key, void* value, mcc_size_t key_size, mcc_size_t value_size);
bool  _mcc_treemap_has(void** keys, void** values, void* key, mcc_size_t key_size);
void* _mcc_treemap_get(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size);
bool  _mcc_treemap_remove(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size);
void  _mcc_treemap_destroy(void** keys, void** values);

mcc_size_t _mcc_treemap_size(void** keys, void** values);

/**
 * Allocate an empty treemap on the heap with default key comparator.
 * The parameter variables are updated to point to the allocated treesets.
 * 
 * @param keys map keys
 * @param values map values
 */
#define mcc_treemap_create(keys, values) _mcc_treemap_create((void**)(&(keys)), (void**)(&(values)), NULL)

/**
 * Allocate an empty treemap on the heap with custom key comparator.
 * The parameter variables are updated to point to the allocated treesets.
 * 
 * @param keys map keys
 * @param values map values
 * @param key_comparator key comparator function
 * 
 * @see mcc_compare_fn_t
 */
#define mcc_treemap_create_ex(keys, values, key_comparator) _mcc_treemap_create((void**)(&(keys)), (void**)(&(values)), key_comparator)

/**
 * Set key-value association in map.
 * If the key already exists, its value is updated. Otherwise, a new association is created.
 * 
 * @param keys map keys
 * @param values map values
 * @param key key variable
 * @param value value variable
 */
#define mcc_treemap_set(keys, values, key, value) _mcc_treemap_set((void**)(&(keys)), (void**)(&(values)), &(key), &(value), sizeof(*keys), sizeof(*values))

/**
 * Check if the map has association for given key.
 * 
 * @param keys map keys
 * @param values map values
 * @param key key variable
 * @returns `true` if found; `false` otherwise
 */
#define mcc_treemap_has(keys, values, key) _mcc_treemap_has((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*keys))

/**
 * Get value for key.
 * 
 * **Note** that the resulting pointer may get invalidated as the map changes.
 * 
 * @param keys map keys
 * @param values map values
 * @param key key variable
 * @return pointer to value; `NULL` for unknown keys
 */
#define mcc_treemap_get(keys, values, key) _mcc_treemap_get((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*keys), sizeof(*values))

/**
 * Remove association from map.
 * If the key is not in the map, the map is not modified.
 * 
 * This method may be called any number of times with the same arguments,
 * the result will be the same - a map without the specified key.
 * 
 * @param keys map keys
 * @param values map values
 * @param key key variable
 * @return `true` if the map was modified; `false` otherwise
 */
#define mcc_treemap_remove(keys, values, key) _mcc_treemap_remove((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*keys), sizeof(*values))

/**
 * Destroy treemap.
 * This will free the space allocated on the heap.
 * 
 * @param keys map keys
 * @param values map values
 */
#define mcc_treemap_destroy(keys, values) _mcc_treemap_destroy((void**)(&(keys)), (void**)(&(values)))

/**
 * Get map size - the number of associations stored in the map.
 * 
 * @param keys map keys
 * @param values map values
 * @returns map size
 */
#define mcc_treemap_size(keys, values) _mcc_treemap_size((void**)(&(keys)), (void**)(&(values)))

#endif
