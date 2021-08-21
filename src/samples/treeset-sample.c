#include <stdio.h>
#include <stdint.h>
#include <macrocol/vector.h>
#include <macrocol/treeset.h>

int main(int argc, char** argv) {
    uint16_t count = 12;
    uint16_t* set = mcc_treeset_create();

    for (int i = 0; i < count; ++i) {
        uint16_t val = (17 + i * 39) % 10;
        set = mcc_treeset_add(set, val);
    }

    uint16_t val = 6;
    mcc_treeset_remove(set, val);

    printf("Set contents:\n\t");
    for (mcc_size_t i = 0; i < mcc_treeset_size(set); ++i)
        printf("%d ", set[i]);
    printf("\n");

    return 0;
}
