#include "real_type.h"
#include <stdio.h>

static void real_copy(void *d, const void *s) {
    *(double *) d = *(const double *) s;
}

static void real_print(const void *d) {
    printf("%.2f", *(const double *) d);
}

static void real_add(void *d, const void *a, const void *b) {
    *(double *) d = *(const double *) a + *(const double *) b;
}

static void real_mul(void *d, const void *a, const void *b) {
    *(double *) d = *(const double *) a * *(const double *) b;
}

static void real_zero(void *d) {
    *(double *) d = 0.0;
}

static const TypeInfo RealType = {
    sizeof(double),
    real_copy,
    real_print,
    real_add,
    real_mul,
    real_zero
};

const TypeInfo *ofReal() {
    return &RealType;
}
