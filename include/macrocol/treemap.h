#ifndef _H_MACROCOL_TREEMAP
#define _H_MACROCOL_TREEMAP

#include <macrocol/types.h>

void  _mcc_treemap_create(void** keys, void** values, mcc_compare_fn_t key_comparator);
void  _mcc_treemap_set(void** keys, void** values, void* key, void* value, mcc_size_t key_size, mcc_size_t value_size);
bool  _mcc_treemap_has(void** keys, void** values, void* key, mcc_size_t key_size);
void* _mcc_treemap_get(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size);
bool  _mcc_treemap_remove(void** keys, void** values, void* key, mcc_size_t key_size, mcc_size_t value_size);
void  _mcc_treemap_destroy(void** keys, void** values);

mcc_size_t _mcc_treemap_size(void** keys, void** values);

#define mcc_treemap_create(keys, values) _mcc_treemap_create((void**)(&(keys)), (void**)(&(values)), NULL)
#define mcc_treemap_create_ex(keys, values, key_comparator) _mcc_treemap_create((void**)(&(keys)), (void**)(&(values)), key_comparator)
#define mcc_treemap_set(keys, values, key, value) _mcc_treemap_set((void**)(&(keys)), (void**)(&(values)), &(key), &(value), sizeof(*keys), sizeof(*values))
#define mcc_treemap_has(keys, values, key) _mcc_treemap_has((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*keys))
#define mcc_treemap_get(keys, values, key) _mcc_treemap_get((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*keys), sizeof(*values))
#define mcc_treemap_remove(keys, values, key) _mcc_treemap_remove((void**)(&(keys)), (void**)(&(values)), &(key), sizeof(*keys), sizeof(*values))
#define mcc_treemap_destroy(keys, values) _mcc_treemap_destroy((void**)(&(keys)), (void**)(&(values)))

#define mcc_treemap_size(keys, values) _mcc_treemap_size((void**)(&(keys)), (void**)(&(values)))

#endif
