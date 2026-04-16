#include "int_type.h"
#include <stdio.h>

static void int_copy(void *d, const void *s) {
    *(int *) d = *(const int *) s;
}

static void int_print(const void *d) {
    printf("%d", *(const int *) d);
}

static void int_add(void *d, const void *a, const void *b) {
    *(int *) d = (*(const int *) a) + (*(const int *) b);
}

static void int_mul(void *d, const void *a, const void *b) {
    *(int *) d = (*(const int *) a) * (*(const int *) b);
}

static void int_zero(void *d) {
    *(int *) d = 0;
}

static const TypeInfo IntType = {
    sizeof(int),
    int_copy,
    int_print,
    int_add,
    int_mul,
    int_zero
};

const TypeInfo *ofInt() {
    return &IntType;
}
