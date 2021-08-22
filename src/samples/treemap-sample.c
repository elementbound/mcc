#include <stdio.h>
#include <stdint.h>
#include <macrocol/treemap.h>

int main(int argc, char** argv) {
    uint16_t* keys;
    char** strings;

    mcc_treemap_create(keys, strings);

    uint16_t key; char* string;

    key = 2; string = "Hello";
    mcc_treemap_set(keys, strings, key, string);

    key = 4; string = "world!";
    mcc_treemap_set(keys, strings, key, string);

    key = 3; string = "eh";
    mcc_treemap_set(keys, strings, key, string);

    mcc_treemap_remove(keys, strings, key);

    for (mcc_index_t i = 0; i < mcc_treemap_size(keys, strings); ++i)
        printf("[%d] => %s\n", keys[i], strings[i]);

    return 0;
}
