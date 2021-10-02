#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mcc/treeset.h>
#include <mcc/typehandlers.h>

char* strdup(const char* str) {
    int len = strlen(str);
    char* dup = malloc(len+1);
    memcpy(dup, str, len+1);
    
    return dup;
}

int main(int argc, char** argv) {
    char** uniq_args = mcc_treeset_create_ex(mcc_string_compare);
    printf("Parsing %d words\n", argc-1);
    
    for (int i = 1; i < argc; ++i) 
        uniq_args = mcc_treeset_add(uniq_args, argv[i]);
    
    printf("Distinct words:\n\t");
    for (mcc_index_t i = 0; i < mcc_treeset_size(uniq_args); ++i) {
        printf(" \"%s\"", uniq_args[i]);
    }
    printf("\n");
    
    return 0;
}
