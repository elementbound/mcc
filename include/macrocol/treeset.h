#ifndef _H_MACROCOL_TREESET
#define _H_MACROCOL_TREESET

#include <macrocol/types.h>

void* _mcc_treeset_create();
void* _mcc_treeset_add(void* set, void* data, mcc_size_t item_size);
bool  _mcc_treeset_contains(void* set, void* data, mcc_size_t item_size);
bool  _mcc_treeset_remove(void* set, void* data, mcc_size_t item_size);
void  _mcc_treeset_destroy(void* set);

mcc_size_t _mcc_treeset_size(void* set);

#define mcc_treeset_create() _mcc_treeset_create()
#define mcc_treeset_add(set, data) _mcc_treeset_add(set, &(data), sizeof(*set))
#define mcc_treeset_contains(set, data) _mcc_treeset_contains(set, &(data), sizeof(*set))
#define mcc_treeset_remove(set, data) _mcc_treeset_remove(set, &(data), sizeof(*set))
#define mcc_treeset_destroy(set) _mcc_treeset_destroy(set)

#define mcc_treeset_size(set) _mcc_treeset_size(set)

#endif
