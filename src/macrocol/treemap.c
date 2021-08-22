#include <macrocol/treemap.h>
#include <macrocol/vector.h>

#include <string.h>

void  _mcc_treemap_create(void** keys, void** values) {
    *keys = _mcc_vector_create();
    *values = _mcc_vector_create();
}

void  _mcc_treemap_set(void** keys, void** values, void* key, void* value, mcc_size_t key_size, mcc_size_t value_size) {
    // TODO: binary search
    for (mcc_index_t i = 0; i < _mcc_vector_size(*keys); ++i) {
        if (memcmp((uint8_t*)keys + i * key_size, key, key_size) == 0) {
            memcpy((uint8_t*)values + i * value_size, value, value_size);
            return;
        }
    }

    *keys = _mcc_vector_add(*keys, key, key_size);
    *values = _mcc_vector_add(*values, value, value_size);
}

bool  _mcc_treemap_has(void** keys, void** values, void* key, mcc_size_t key_size) {
    // TODO: binary search
    for (mcc_index_t i = 0; i < _mcc_vector_size(*keys); ++i) {
        if (memcmp((uint8_t*)keys + i * key_size, key, key_size) == 0)
            return true;
    }

    return false;
}

void* _mcc_treemap_get(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size) {
    // TODO: binary search
    for (mcc_index_t i = 0; i < _mcc_vector_size(*keys); ++i) {
        if (memcmp((uint8_t*)keys + i * key_size, key, key_size) == 0) {
            return (uint8_t*)values + i * value_size;
        }
    }

    return NULL;
}

bool  _mcc_treemap_remove(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size) {
    // TODO: binary search
    for (mcc_index_t i = 0; i < _mcc_vector_size(*keys); ++i) {
        if (memcmp((uint8_t*)(*keys) + i * key_size, key, key_size) == 0) {
            _mcc_vector_remove(*keys, i, key_size);
            _mcc_vector_remove(*values, i, value_size);
            return true;
        }
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
