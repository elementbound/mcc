#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mcc/vector.h>
#include <mcc/treeset.h>

int mcc_strcmp(const void* pa, const void* pb, mcc_size_t item_size) {
    const char* a = *(const char**)pa;
    const char* b = *(const char**)pb;
    int result = strcmp(a, b);
    
    if (result > 0)
        printf("[cmp]\"%s\" > \"%s\"\n", a, b);
    else if (result < 0)
        printf("[cmp]\"%s\" < \"%s\"\n", a, b);
    else if (result == 0)
        printf("[cmp]\"%s\" = \"%s\"\n", a, b);
    
    return result;
}

char* strdup(const char* str) {
    int len = strlen(str);
    char* dup = malloc(len+1);
    memcpy(dup, str, len+1);
    
    return dup;
}

int main(int argc, char** argv) {
    char* word_buffer = mcc_vector_create();
    char** distinct_words = mcc_treeset_create_ex(mcc_strcmp);
    const char nullchar = '\0';
    
    const char* text = "a c a b a d";
    int text_len = strlen(text);
    printf("String: \"%s\"\n", text);
    printf("String length: %d\n", text_len);
    
    for (int i = 0; i < text_len; ++i) {
        char c = text[i];
        if (isblank(c)) {
            word_buffer = mcc_vector_add(word_buffer, nullchar);
            char* word = strdup(word_buffer);
            distinct_words = mcc_treeset_add(distinct_words, word);
            
            printf("\"%s\" =>", word, mcc_treeset_size(distinct_words));
            for (mcc_index_t i = 0; i < _mcc_treeset_size(distinct_words); ++i)
                printf(" \"%s\"", distinct_words[i]);
            printf("\n");
            
            // mcc_vector_clear();
            mcc_vector_destroy(word_buffer);
            word_buffer = mcc_vector_create();
            
            continue;
        }
        
        word_buffer = mcc_vector_add(word_buffer, c);
    }
    
    printf("Distinct words:\n\t");
    for (mcc_index_t i = 0; i < mcc_treeset_size(distinct_words); ++i) {
        printf(" \"%s\"", distinct_words[i]);
    }
    printf("\n");
    
    return 0;
}
