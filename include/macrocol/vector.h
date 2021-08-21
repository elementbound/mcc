#ifndef _H_MACROCOL_VECTOR
#define _H_MACROCOL_VECTOR

#include <macrocol/types.h>

void* _mcc_vector_create();
void* _mcc_vector_add(void* vector, void* data, mcc_size_t item_size);
void* _mcc_vector_insert(void* vector, mcc_index_t at, void* data, mcc_size_t item_size);
void  _mcc_vector_remove(void* vector, mcc_index_t at, mcc_size_t item_size);
void  _mcc_vector_destroy(void* vector);

mcc_size_t _mcc_vector_size(void* vector);
mcc_size_t _mcc_vector_capacity(void* vector);
void* _mcc_vector_resize(void* vector, mcc_size_t size, mcc_size_t item_size);
void* _mcc_vector_ensure_capacity(void* vector, mcc_size_t capacity, mcc_size_t item_size);

#define mcc_vector_create() _mcc_vector_create()
#define mcc_vector_add(vector, data) _mcc_vector_add(vector, &(data), sizeof(*vector))
#define mcc_vector_insert(vector, at, data) _mcc_vector_insert(vector, at, &(data), sizeof(*vector))
#define mcc_vector_remove(vector, at) _mcc_vector_remove(vector, at, sizeof(*vector))
#define mcc_vector_destroy(vector) _mcc_vector_destroy(vector)

#define mcc_vector_size(vector) _mcc_vector_size(vector)
#define mcc_vector_capacity(vector) _mcc_vector_capacity(vector)
#define mcc_vector_resize(vector, size) _mcc_vector_resize(vector, size, sizeof(*vector))
#define mcc_vector_ensure_capacity(vector, capacity) _mcc_vector_capacity(vector, sizeof(*vector))

#endif
