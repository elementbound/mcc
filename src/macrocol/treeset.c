#include <macrocol/treeset.h>
#include <macrocol/vector.h>

#include <stdlib.h>
#include <string.h>

#define max(a,b) ((a) > (b)) ? (a) : (b)

mcc_size_t _mcc_item_size;
bool _mcc_treeset_search(void* set, void* data, mcc_size_t item_size, mcc_index_t* index);

int _mcc_scmp(const void* set, mcc_index_t a, const void* pb, mcc_size_t item_size) {
    const void* pa = (uint8_t*)(set) + a * item_size;
    const mcc_compare_fn_t cmp = _mcc_vector_get_userdata(set);

    return cmp != NULL
        ? cmp(pa, pb, item_size)
        : memcmp(pa, pb, item_size);
}

void* _mcc_treeset_create() {
    return _mcc_vector_create(NULL);
}

void* _mcc_treeset_create_ex(mcc_compare_fn_t compare_fn) {
    return _mcc_vector_create(compare_fn);
}

void* _mcc_treeset_add(void* set, void* data, mcc_size_t item_size) {
    if (_mcc_vector_size(set) == 0) {
        return _mcc_vector_add(set, data, item_size);
    }

    if (_mcc_treeset_contains(set, data, item_size, NULL)) {
        return set;
    }

    mcc_index_t idx = _mcc_treeset_lower_bound(set, data, item_size);
    
    return _mcc_vector_insert(set, idx, data, item_size);
}

bool _mcc_treeset_contains(void* set, void* data, mcc_size_t item_size, mcc_index_t* idx) {
    return _mcc_treeset_search(set, data, item_size, idx);
}

bool _mcc_treeset_remove(void* set, void* data, mcc_size_t item_size) {
    mcc_index_t idx;
    if (_mcc_treeset_search(set, data, item_size, &idx)) {
        _mcc_vector_remove(set, idx, item_size);
        return true;
    } else
        return false;
}

void  _mcc_treeset_destroy(void* set) {
    _mcc_vector_destroy(set);
}


mcc_index_t _mcc_treeset_lower_bound(void* set, void* data, mcc_size_t item_size) {
    mcc_size_t size = _mcc_vector_size(set);
    mcc_index_t lower = 0;
    mcc_index_t upper = size;
    mcc_index_t mid;
    
    if (size == 0)
        return 0;

    if (_mcc_scmp(set, 0, data, item_size) > 0)
        return 0;

    while (lower < upper) {
        mid = (lower + upper) / 2;
        int cmp = _mcc_scmp(set, mid, data, item_size);

        if (cmp < 0)
            lower = mid + 1;
        else
            upper = mid;
    }

    return lower;
}

bool _mcc_treeset_search(void* set, void* data, mcc_size_t item_size, mcc_index_t* index) {
    mcc_size_t size = _mcc_vector_size(set);
    mcc_index_t lower = 0;
    mcc_index_t upper = size - 1;
    mcc_index_t mid;
    
    if (size == 0)
        return false;

    while (lower <= upper) {
        mid = (lower + upper) / 2;
        int cmp = _mcc_scmp(set, mid, data, item_size);

        if (cmp > 0) {
            if (mid == 0) break;
            else upper = mid - 1;
        } else if (cmp < 0)
            lower = mid + 1;
        else {
            if (index) *index = mid;
            return true;
        }
    }
    
    return false;
}

mcc_size_t _mcc_treeset_size(void* set) {
    return _mcc_vector_size(set);
}
