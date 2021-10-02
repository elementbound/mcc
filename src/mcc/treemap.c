#include <mcc/treemap.h>
#include <mcc/treeset.h>
#include <mcc/vector.h>

#include <string.h>

void  _mcc_treemap_create(void** keys, void** values, mcc_compare_fn_t key_comparator) {
    *keys = _mcc_treeset_create_ex(key_comparator);
    *values = _mcc_vector_create(NULL);
}

void  _mcc_treemap_set(void** keys, void** values, void* key, void* value, mcc_size_t key_size, mcc_size_t value_size) {
    mcc_index_t idx;
    if (_mcc_treeset_contains(*keys, key, key_size, &idx)) {
        memcpy((uint8_t*)values + idx * value_size, value, value_size);
    } else {
        idx = _mcc_treeset_lower_bound(*keys, key, key_size);
        *keys = _mcc_vector_insert(*keys, idx, key, key_size);
        *values = _mcc_vector_insert(*values, idx, value, value_size);
    }
}

bool  _mcc_treemap_has(void** keys, void** values, void* key, mcc_size_t key_size) {
    return _mcc_treeset_contains(*keys, key, key_size, NULL);
}

void* _mcc_treemap_get(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size) {
    mcc_index_t idx;
    if (_mcc_treeset_contains(*keys, key, key_size, &idx)) {
        return (uint8_t*)values + idx * value_size;
    } else
        return NULL;
}

bool  _mcc_treemap_remove(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size) {
    mcc_index_t idx;
    if (_mcc_treeset_contains(*keys, key, key_size, &idx)) {
        _mcc_vector_remove(*keys, idx, key_size);
        _mcc_vector_remove(*values, idx, value_size);
        return true;
    }

    return false;
}

void  _mcc_treemap_destroy(void** keys, void** values) {
    _mcc_vector_destroy(*keys);
    _mcc_vector_destroy(*values);

    *keys = NULL;
    *values = NULL;
}

mcc_size_t _mcc_treemap_size(void** keys, void** values) {
    return _mcc_vector_size(*keys);
}
