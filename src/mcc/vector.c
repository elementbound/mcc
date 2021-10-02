#include <mcc/vector.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define DATA_TO_VECTOR(vector_data) ((mcc_vector_t*)((uint8_t*)(vector_data) - sizeof(mcc_vector_t)))
#define VECTOR_TO_DATA(vector) ((uint8_t*)(vector) + sizeof(mcc_vector_t))
#define INITIAL_CAPACITY 10

typedef struct {
    mcc_size_t size;
    mcc_size_t capacity;
    void* userdata;
} mcc_vector_t;

mcc_size_t _mcc_vector_calculate_capacity(mcc_size_t current, mcc_size_t required) {
    while (current < required)
        current = 1 + current * 1415 / 1000;

    return current;
}

void* _mcc_vector_create(void* userdata) {
    mcc_vector_t* vector = (mcc_vector_t*) malloc(sizeof(mcc_vector_t));

    vector->size = 0;
    vector->capacity = 0;
    vector->userdata = userdata;

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

void* _mcc_vector_insert(void* vector_data, mcc_index_t at, void* data, mcc_size_t item_size) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);
    
    if (at == vector->size) {
        return _mcc_vector_add(vector_data, data, item_size);
    } else if (at > vector->size) {
        return vector_data;
    }

    vector_data = _mcc_vector_ensure_capacity(vector_data, vector->size + 1, item_size);
    vector = DATA_TO_VECTOR(vector_data);

    memmove((uint8_t*)vector_data + (at+1) * item_size,
        (uint8_t*)vector_data + at * item_size,
        (vector->size - at) * item_size);
    
    memcpy((uint8_t*)vector_data + at * item_size, data, item_size);
    ++vector->size;

    return vector_data;
}

void _mcc_vector_remove(void* vector_data, mcc_index_t at, mcc_size_t item_size) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);

    if (at >= vector->size)
        return;

    memmove((uint8_t*)(vector_data) + at * item_size,
        (uint8_t*)(vector_data) + (at+1) * item_size,
        (vector->size - at - 1) * item_size);
    --vector->size;
}

void _mcc_vector_destroy(void* vector_data) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);
    free(vector);
}

void* _mcc_vector_get_userdata(const void* vector_data) {
    mcc_vector_t* vector = DATA_TO_VECTOR(vector_data);

    return vector->userdata;
}

mcc_size_t _mcc_vector_size(const void* vector_data) {
    return DATA_TO_VECTOR(vector_data)->size;
}

mcc_size_t _mcc_vector_capacity(const void* vector_data) {
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
    result->userdata = vector->userdata;    
    
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
