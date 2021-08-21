#include <macrocol/vector.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define DATA_TO_VECTOR(vector_data) ((mcc_vector_t*)((vector_data) - sizeof(mcc_vector_t)))
#define VECTOR_TO_DATA(vector) ((void*)(vector) + sizeof(mcc_vector_t))
#define INITIAL_CAPACITY 10

typedef struct {
    mcc_size_t size;
    mcc_size_t capacity;
} mcc_vector_t;

mcc_size_t _mcc_vector_calculate_capacity(mcc_size_t current, mcc_size_t required) {
    while (current < required)
        current = 1 + current * 1415 / 1000;

    return current;
}

void* _mcc_vector_create() {
    mcc_vector_t* vector = (mcc_vector_t*) malloc(sizeof(mcc_vector_t));

    vector->size = 0;
    vector->capacity = 0;

    return VECTOR_TO_DATA(vector);
}

void* _mcc_vector_add(void* vector_data, void* data, mcc_size_t item_size) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);
    vector_data = _mcc_vector_ensure_capacity(vector_data, vector->size + 1, item_size);
    vector = DATA_TO_VECTOR(vector_data);
    memcpy(VECTOR_TO_DATA(vector) + vector->size * item_size, data, item_size);
    ++vector->size;

    return VECTOR_TO_DATA(vector);
}

void _mcc_vector_remove(void* vector_data, mcc_index_t at, mcc_size_t item_size) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);

    if (at >= vector->size)
        return;

    memmove(vector_data + at * item_size, vector_data + (at+1) * item_size, (vector->size - 1) * item_size);
    --vector->size;
}

void _mcc_vector_destroy(void* vector_data) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);
    free(vector);
}

mcc_size_t _mcc_vector_size(void* vector_data) {
    return DATA_TO_VECTOR(vector_data)->size;
}

mcc_size_t _mcc_vector_capacity(void* vector_data) {
    return DATA_TO_VECTOR(vector_data)->capacity;
}

void* _mcc_vector_ensure_capacity(void* vector_data, mcc_size_t capacity, mcc_size_t item_size) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);

    if (vector->capacity >= capacity)
        return vector_data;

    mcc_size_t new_capacity = _mcc_vector_calculate_capacity(vector->capacity, capacity);
    mcc_vector_t* result = (mcc_vector_t*) malloc(sizeof(mcc_vector_t) + new_capacity * item_size);
    
    result->size = vector->size;
    result->capacity = new_capacity;    
    
    if (vector->size > 0)
        memcpy(VECTOR_TO_DATA(result), vector_data, vector->size * item_size);

    _mcc_vector_destroy(vector_data);
    
    return VECTOR_TO_DATA(result);
}

void* _mcc_vector_resize(void* vector_data, mcc_size_t size, mcc_size_t item_size) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);

    if (vector->capacity < size)
        vector = _mcc_vector_ensure_capacity(vector_data, size, item_size);

    vector->size = size;
    return VECTOR_TO_DATA(vector);
}
