#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <mcc/treemap.h>
#include <mcc/typehandlers.h>

int main(int argc, char** argv) {
    char** keys;
    char** strings;

    mcc_treemap_create_ex(keys, strings, mcc_string_compare);

    char* key; char* string;

    key = "greet/1"; string = "Hello";
    mcc_treemap_set(keys, strings, key, string);

    key = "greet/3"; string = "world!";
    mcc_treemap_set(keys, strings, key, string);

    key = "greet/2"; string = "eh";
    mcc_treemap_set(keys, strings, key, string);

    char* dynamic_key = calloc(64, sizeof(char));
    strcat(dynamic_key, "greet/");
    strcat(dynamic_key, "2");

    printf("Removing dynamic key \"%s\"\n", dynamic_key);
    mcc_treemap_remove(keys, strings, dynamic_key);
    free(dynamic_key);

    printf("Map contents:\n");
    for (mcc_index_t i = 0; i < mcc_treemap_size(keys, strings); ++i)
        printf("\t[%s] => %s\n", keys[i], strings[i]);

    return 0;
}
