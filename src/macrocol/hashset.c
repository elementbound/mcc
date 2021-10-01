#include <macrocol/hashset.h>
#include <macrocol/vector.h>
#include <macrocol/typehandlers.h>
#include <stdlib.h>
#include <string.h>

#ifndef MCC_DEFAULT_BUCKETS
    #define MCC_HASHSET_DEFAULT_BUCKETS 32
#endif
    
typedef struct {
    mcc_hash_fn_t hash_func;
    mcc_equals_fn_t equals_func;
    
    mcc_size_t bucket_count;
    mcc_index_t* bucket_start_idx;
} mcc_hashset_meta_t;

mcc_hashset_meta_t* _mcc_hashset_get_meta(void* set) {
    return (mcc_hashset_meta_t*) _mcc_vector_get_userdata(set);
}

void* _mcc_hashset_create() {
    return _mcc_hashset_create_ex(NULL, NULL, MCC_HASHSET_DEFAULT_BUCKETS);
}

void* _mcc_hashset_create_ex(mcc_hash_fn_t hash_func, mcc_equals_fn_t equals_func, mcc_size_t buckets) {
    if (!hash_func) hash_func = mcc_generic_hash;
    if (!equals_func) equals_func = mcc_generic_equals;
    
    mcc_hashset_meta_t* meta = (mcc_hashset_meta_t*) malloc(sizeof(mcc_hashset_meta_t));
    
    meta->hash_func = hash_func;
    meta->equals_func = equals_func;
    meta->bucket_count = buckets;
    meta->bucket_start_idx = (mcc_index_t*) malloc(sizeof(mcc_index_t) * buckets);
    
    for (mcc_index_t i = 0; i < buckets; ++i)
        meta->bucket_start_idx[i] = 0;
    
    return _mcc_vector_create(meta);
}

void _mcc_hashset_destroy(void* set) {
    mcc_hashset_meta_t* meta = _mcc_hashset_get_meta(set);
    
    free(meta->bucket_start_idx);
    free(meta);
    _mcc_vector_destroy(set);
}

void* _mcc_hashset_add(void* set, void* data, mcc_size_t item_size) {
    mcc_index_t idx, bucket_idx;
    if (_mcc_hashset_find(set, data, item_size, &idx, &bucket_idx))
        // Already in set
        return set;
    
    set = _mcc_vector_insert(set, idx, data, item_size);
    mcc_hashset_meta_t* meta = _mcc_hashset_get_meta(set);
    
    for (mcc_index_t i = bucket_idx + 1; i < meta->bucket_count; ++i)
        ++meta->bucket_start_idx[i];
    
    return set;
}

bool _mcc_hashset_remove(void* set, void* data, mcc_size_t item_size) {
    mcc_index_t idx, bucket_idx;
    if (!_mcc_hashset_find(set, data, item_size, &idx, &bucket_idx))
        // Already removed
        return false;

    _mcc_vector_remove(set, idx, item_size);
    
    mcc_hashset_meta_t* meta = _mcc_hashset_get_meta(set);
    for (mcc_index_t i = bucket_idx + 1; i < meta->bucket_count; ++i)
        --meta->bucket_start_idx[i];
    
    return true;
}

bool _mcc_hashset_find(void* set, void* data, mcc_size_t item_size, mcc_index_t* idx, mcc_index_t* out_bucket_idx) {
    mcc_size_t size = _mcc_vector_size(set);
    
    mcc_hashset_meta_t* meta = _mcc_hashset_get_meta(set);
    mcc_hash_t hash = meta->hash_func(data, item_size);
    mcc_index_t bucket_idx = hash % meta->bucket_count;
    
    mcc_index_t bucket_start = meta->bucket_start_idx[bucket_idx];
    mcc_index_t bucket_end = (bucket_idx + 1 >= meta->bucket_count)
        ? size
        : meta->bucket_start_idx[bucket_idx + 1];
        
    for (mcc_index_t i = bucket_start; i < bucket_end; ++i) {
        if (meta->equals_func(((uint8_t*) set) + item_size * i, data, item_size) == 0) {
            if (idx) *idx = i;
            if (out_bucket_idx) *out_bucket_idx = bucket_idx;
            return true;
        }
    }
    
    if (idx) *idx = bucket_end;
    if (out_bucket_idx) *out_bucket_idx = bucket_idx;
    
    return false;
}

mcc_size_t _mcc_hashset_size(void* set) {
    return _mcc_vector_size(set);
}
