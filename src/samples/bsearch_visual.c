#include <stdio.h>
#include <string.h>

typedef struct {
    int* values;
    int count;
    int lower, upper, mid;
} bsearch_state_t;

void print_state(bsearch_state_t state) {
    int at = 0;
    char buf[32];

    int lower_at, upper_at, mid_at;

    for (int i = 0; i < state.count; ++i) {
        if (i == state.lower) lower_at = at;
        if (i == state.upper) upper_at = at;
        if (i == state.mid) mid_at = at;

        printf("%d ", state.values[i]);
        at += sprintf(buf, "%d ", state.values[i]);
    }
    printf("\n");

    for (int i = 0; i < at; i++) {
        if (i == lower_at && i == upper_at) printf("|");
        else if (i == lower_at) printf("v");
        else if(i == mid_at) printf("+");
        else if(i == upper_at) printf("^");
        else printf(" ");
    }
    printf("\n");
}

void find_any(bsearch_state_t state, int key) {
    state.lower = 0;
    state.upper = state.count - 1;

    while (state.lower < state.upper) {
        state.mid = (state.lower + state.upper) / 2;
        print_state(state);

        if (state.values[state.mid] > key)
            state.upper = state.mid - 1;
        else
            state.lower = state.mid + 1;
    }
    print_state(state);

    // printf("Final mid is #%d %d\n", state.lower, state.values[state.mid]);
    if (state.values[state.lower] == key) {
        printf("Found %d at #%d\n", key, state.lower);
    }
    printf("[any] Final bounds [%d, %d]\n", state.lower, state.upper);
}

void find_lower(bsearch_state_t state, int key) {
    state.lower = 0;
    state.upper = state.count - 1;

    if (state.values[0] >= key) {
        printf("[lower] Key out of bounds! %d >= %d\n", state.values[0], key);
        return;
    }

    while (state.lower < state.upper) {
        state.mid = (state.upper + state.lower) / 2;

        if (state.values[state.mid] < key)
            state.lower = state.mid + 1;
        else
            state.upper = state.mid;

        print_state(state);
    }

    --state.lower;

    printf("Lower bound to %d is [%d]%d\n", key, state.lower, state.values[state.lower]);
}

void find_upper(bsearch_state_t state, int key) {
    state.lower = 0;
    state.upper = state.count - 1;

    if (key >= state.values[state.count - 1]) {
        printf("[upper] Key out of bounds! %d >= %d\n", key, state.values[state.count - 1]);
        return;
    }

    while (state.lower < state.upper) {
        state.mid = (state.upper + state.lower) / 2;

        if (state.values[state.mid] > key)
            state.upper = state.mid;
        else
            state.lower = state.mid + 1;

        print_state(state);
    }

    // state.upper;

    printf("Upper bound to %d is [%d]%d\n", key, state.upper, state.values[state.upper]);
}

int main(int argc, char** argv) {
    int values[] = {3, 5, 8, 13, 21, 34, 55, 89};
    bsearch_state_t state = {
        .values = values,
        .count = sizeof(values) / sizeof(values[0]) 
    };

    int key = 22;

    find_any(state, key);
    find_lower(state, key);
    find_upper(state, key);

    // printf("Upper bound to %d is [%d]%d\n", key, state.upper, state.values[state.upper]);

    return 0;
}