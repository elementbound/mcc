#include <macrocol/hashmap.h>
#include <macrocol/hashset.h>
#include <macrocol/vector.h>
#include <macrocol/typehandlers.h>
#include <stddef.h>
#include <string.h>

#ifndef MCC_HASHMAP_DEFAULT_BUCKETS
    #define MCC_HASHMAP_DEFAULT_BUCKETS 32
#endif

void _mcc_hashmap_create(void** keys, void** values) {
    _mcc_hashmap_create_ex(keys, values, NULL, NULL, MCC_HASHMAP_DEFAULT_BUCKETS);
}

void _mcc_hashmap_create_ex(void** keys, void** values, mcc_hash_fn_t hash_func, mcc_equals_fn_t equals_func, mcc_size_t buckets) {    
    *keys = _mcc_hashset_create_ex(hash_func, equals_func, buckets);
    *values = _mcc_vector_create(NULL);
}

void _mcc_hashmap_destroy(void** keys, void** values) {
    _mcc_hashset_destroy(*keys);
    _mcc_vector_destroy(*values);
    
    *keys = NULL;
    *values = NULL;
}

void _mcc_hashmap_set(void** keys, void** values, void* key, void* value, mcc_size_t key_size, mcc_size_t value_size) {
    mcc_index_t idx;

    if (_mcc_hashset_find(*keys, key, key_size, &idx, NULL)) {
        memcpy(((uint8_t*)*values) + idx * value_size, value, value_size);
    } else {
        *keys = _mcc_hashset_add(*keys, key, key_size);
        *values = _mcc_vector_insert(*values, idx, value, value_size);
    }
}

bool _mcc_hashmap_has(void** keys, void** values, void* key, mcc_size_t key_size) {
    return _mcc_hashset_find(*keys, key, key_size, NULL, NULL);
}

void* _mcc_hashmap_get(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size) {
    mcc_index_t idx;
    
    if (_mcc_hashset_find(*keys, key, key_size, &idx, NULL))
        return ((uint8_t*)(*values)) + idx * value_size;
    else
        return NULL;
}

bool _mcc_hashmap_remove(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size) {
    mcc_index_t idx;
    
    if (_mcc_hashset_find(*keys, key, key_size, &idx, NULL)) {
        _mcc_hashset_remove(*keys, key, key_size);
        _mcc_vector_remove(*values, idx, value_size);
        return true;
    }
    else
        return false;
}

mcc_size_t _mcc_hashmap_size(void** keys, void** values) {
    return _mcc_vector_size(*keys);
}
