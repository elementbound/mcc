#include <stdio.h>
#include <stdint.h>
#include <mcc/vector.h>

int main(int argc, char** argv) {
    uint16_t count = 8;
    uint16_t* vector = mcc_vector_create();

    for (int i = 0; i < count; ++i) {
        uint16_t val = 17 + i * 39;
        vector = mcc_vector_add(vector, val);
    }

    printf("Vector contents:\n\t");
    for (mcc_size_t i = 0; i < mcc_vector_size(vector); ++i)
        printf("%d ", vector[i]);
    printf("\n");
    
    mcc_vector_remove(vector, count / 2 - 1);

    uint16_t val = 1024;
    mcc_vector_insert(vector, count / 2 - 1, val);
    
    printf("After replacing the middle item:\n\t");
    for (mcc_size_t i = 0; i < mcc_vector_size(vector); ++i)
        printf("%d ", vector[i]);
    printf("\n");

    printf("Size: %ld; Capacity: %ld\n", mcc_vector_size(vector), mcc_vector_capacity(vector));

    return 0;
}
