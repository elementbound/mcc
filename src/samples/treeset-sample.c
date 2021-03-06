#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <mcc/treeset.h>
#include <mcc/typehandlers.h>

void print_treeset(uint16_t* set) {
    for (mcc_size_t i = 0; i < mcc_treeset_size(set); ++i)
        printf("%d ", set[i]);
}

int main(int argc, char** argv) {
    uint16_t count = 14;
    uint16_t* set = mcc_treeset_create();

    for (int i = 0; i < count; ++i) {
        uint16_t val = (17 + i * 39) % 10;
        set = mcc_treeset_add(set, val);
        
        printf("Push %d -> ", val);
        print_treeset(set);
        printf("\n");
    }

    uint16_t val = 6;
    mcc_treeset_remove(set, val);

    printf("Set contents (%ld):\n\t", mcc_treeset_size(set));
    for (mcc_size_t i = 0; i < mcc_treeset_size(set); ++i)
        printf("%d ", set[i]);
    printf("\n");

    return 0;
}
