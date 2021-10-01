#include <macrocol/typehandlers.h>
#include <string.h>

int mcc_generic_compare(const void* pa, const void* pb, mcc_size_t item_size) {
    return memcmp(pa, pb, item_size);
}

int mcc_string_compare(const void* pa, const void* pb, mcc_size_t item_size) {
    const char* a = *(const char**)pa;
    const char* b = *(const char**)pb;
    
    return strcmp(a, b);
}

int mcc_generic_equals(const void* pa, const void* pb, mcc_size_t item_size) {
    return mcc_generic_compare(pa, pb, item_size);
}

int mcc_string_equals(const void* pa, const void* pb, mcc_size_t item_size) {
    return mcc_string_compare(pa, pb, item_size);
}

mcc_hash_t mcc_generic_hash(const void* pv, mcc_size_t item_size) {
    // djb2
    mcc_hash_t hash = 5381;
    
    const uint8_t* v = (const uint8_t*) pv;
    for (mcc_index_t i = 0; i < item_size; ++i)
        hash = ((hash << 5) + hash) + v[i];
    
    return hash;
}

mcc_hash_t mcc_string_hash(const void* pv, mcc_size_t item_size) {
    //djb2
    mcc_hash_t hash = 5381;
    
    const uint8_t* v = (const uint8_t*)(*(const char**)pv);
    
    uint8_t c;
    while((c = *v++))
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}
