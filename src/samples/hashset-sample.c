#include <stdio.h>
#include <mcc/hashset.h>
#include <mcc/typehandlers.h>

int main(int argc, char** argv) {
    mcc_size_t capacity = argc * 100 / 75;
    printf("Creating hashset with capacity %ld\n", capacity);
    char** uniq_args = mcc_hashset_create_ex(mcc_string_hash, mcc_string_equals, argc * 100 / 75);
    
    printf("All arguments:\n\t");
    for (int i = 1; i < argc; ++i) {
        printf("%s ", argv[i]);
        uniq_args = mcc_hashset_add(uniq_args, argv[i]);
    }
    printf("\n");
    
    printf("Unique arguments:\n\t");
    for (mcc_index_t i = 0; i < mcc_hashset_size(uniq_args); ++i)
        printf("%s ", uniq_args[i]);
    printf("\n");
    
    return 0;
}
