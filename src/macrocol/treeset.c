#include <macrocol/treeset.h>
#include <macrocol/vector.h>

#include <stdlib.h>
#include <string.h>

mcc_size_t _mcc_item_size;

int _mcc_cmp(const void* a, const void* b) {
    return memcmp(a, b, _mcc_item_size);
}

void* _mcc_treeset_create() {
    return _mcc_vector_create();
}

void* _mcc_treeset_add(void* set, void* data, mcc_size_t item_size) {
    if (_mcc_vector_size(set) == 0)
        return _mcc_vector_add(set, data, item_size);

    if (_mcc_treeset_contains(set, data, item_size))
        return set;

    // TODO: insert at right place instead of sorting?
    set = _mcc_vector_add(set, data, item_size);
    _mcc_item_size = item_size;
    qsort(set, _mcc_vector_size(set), item_size, _mcc_cmp);

    return set;
}

bool  _mcc_treeset_contains(void* set, void* data, mcc_size_t item_size) {
    // TODO: binary search
    for (mcc_index_t i = 0; i < _mcc_vector_size(set); ++i) {
        int cmp = memcmp((uint8_t*)(set) + i * item_size, data, item_size);
        if (cmp == 0)
            return true;
        else if (cmp > 0)
            return false;
    }

    return false;
}

bool _mcc_treeset_remove(void* set, void* data, mcc_size_t item_size) {
    // TODO: binary search
    for (mcc_index_t i = 0; i < _mcc_vector_size(set); ++i) {
        int cmp = memcmp((uint8_t*)(set) + i * item_size, data, item_size);
        if (cmp == 0) {
            _mcc_vector_remove(set, i, item_size);
            return true;
        }
        else if (cmp > 0)
            return false;
    }

    return false;
}

void  _mcc_treeset_destroy(void* set) {
    _mcc_vector_destroy(set);
}

mcc_size_t _mcc_treeset_size(void* set) {
    return _mcc_vector_size(set);
}
