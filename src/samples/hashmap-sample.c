#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <macrocol/hashmap.h>
#include <macrocol/typehandlers.h>

char* strjoin(const char* a, const char* b) {
    int lena = strlen(a);
    int lenb = strlen(b);
    int len = lena + lenb;
    char* result = (char*) malloc(len + 1);
    
    memcpy(result, a, lena);
    memcpy(result + lena, b, lenb);
    result[len] = '\0';
    
    return result;
}

int main(int argc, char** argv) {
    char **keys, **values;
    const char* new_key, *new_value;
    mcc_hashmap_create_ex(keys, values, mcc_string_hash, mcc_string_equals, 8);
    
    new_key = "greet/en"; new_value = "Hello";
    mcc_hashmap_set(keys, values, new_key, new_value);
    
    new_key = "leave/en"; new_value = "Bye";
    mcc_hashmap_set(keys, values, new_key, new_value);
    
    new_key = "world/en"; new_value = "world";
    mcc_hashmap_set(keys, values, new_key, new_value);
    
    new_key = strjoin("leave/", "en");
    mcc_hashmap_remove(keys, values, new_key);
    
    printf("Map contents:\n");
    for (mcc_index_t i = 0; i < mcc_hashmap_size(keys, values); ++i)
        printf("\t[\"%s\"] => \"%s\"\n", keys[i], values[i]);
        
    return 0;
}
