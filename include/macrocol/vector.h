/**
 * \file vector.h Vector implementation.
 * 
 * A few notes on implementation:
 * - A vector is a self-resizing array that grows as new elements are added.
 * - Capacity is increased by about a factor of two on every second grow iteration.
 * - When adding items, they are copied byte-for-byte from the source.
 * - Calls where the vector pointer may be invalidated always return a valid pointer that can be used after the call.
 */

#ifndef _H_MACROCOL_VECTOR
#define _H_MACROCOL_VECTOR

#include <macrocol/types.h>

void* _mcc_vector_create(void* userdata);
void* _mcc_vector_add(void* vector, void* data, mcc_size_t item_size);
void* _mcc_vector_insert(void* vector, mcc_index_t at, void* data, mcc_size_t item_size);
void  _mcc_vector_remove(void* vector, mcc_index_t at, mcc_size_t item_size);
void  _mcc_vector_destroy(void* vector);

mcc_size_t _mcc_vector_size(const void* vector);
mcc_size_t _mcc_vector_capacity(const void* vector);
void* _mcc_vector_resize(void* vector, mcc_size_t size, mcc_size_t item_size);
void* _mcc_vector_ensure_capacity(void* vector, mcc_size_t capacity, mcc_size_t item_size);

void* _mcc_vector_get_userdata(const void* vector);

/**
 * Allocate a vector on the heap.
 * @returns vector
 */
#define mcc_vector_create() _mcc_vector_create(NULL)

/**
 * Add an item to the end of the vector.
 * 
 * @param vector target vector
 * @param data variable holding the data
 * @returns resulting vector
 */
#define mcc_vector_add(vector, data) _mcc_vector_add(vector, &(data), sizeof(*vector))

/**
 * Insert an item to the vector at the given index.
 * After inserting, the value at the index specified will be the input data.
 * 
 * @param vector target vector
 * @param at target index
 * @param data variable holding the data
 * @returns resulting vector
 */
#define mcc_vector_insert(vector, at, data) _mcc_vector_insert(vector, at, &(data), sizeof(*vector))

/**
 * Remove an item from the vector at the given index.
 * 
 * @param vector target vector
 * @param at target index
 */
#define mcc_vector_remove(vector, at) _mcc_vector_remove(vector, at, sizeof(*vector))

/**
 * Destroy vector.
 * 
 * @param vector target vector
 */
#define mcc_vector_destroy(vector) _mcc_vector_destroy(vector)

/**
 * Get vector size - the number of items it currently holds.
 * 
 * @param vector vector
 * @returns vector size
 */
#define mcc_vector_size(vector) _mcc_vector_size(vector)

/**
 * Get vector capacity - the number of items it can hold without growing.
 * 
 * @param vector vector
 * @returns vector capacity
 */
#define mcc_vector_capacity(vector) _mcc_vector_capacity(vector)

/**
 * Resize vector.
 * This will explicitly set the vector size, and may result in growing.
 * 
 * @param vector vector
 * @param size target size
 * @returns vector
 */
#define mcc_vector_resize(vector, size) _mcc_vector_resize(vector, size, sizeof(*vector))

/**
 * Make sure that the vector has at least the specified capacity.
 * This may result in growing.
 * 
 * @param vector vector
 * @param capacity required capacity
 * @returns vector
 */
#define mcc_vector_ensure_capacity(vector, capacity) _mcc_vector_capacity(vector, sizeof(*vector))

#endif
