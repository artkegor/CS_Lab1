#include "complex_type.h"
#include <stdio.h>

static void complex_copy(void *d, const void *s) {
    *(Complex *) d = *(const Complex *) s;
}

static void complex_print(const void *d) {
    const Complex *c = d;
    printf("(%.2f%+.2fi)", c->re, c->im);
}

static void complex_add(void *d, const void *a, const void *b) {
    Complex *res = d;
    const Complex *x = a;
    const Complex *y = b;

    res->re = x->re + y->re;
    res->im = x->im + y->im;
}

static void complex_mul(void *d, const void *a, const void *b) {
    Complex *res = d;
    const Complex *x = a;
    const Complex *y = b;

    res->re = x->re * y->re - x->im * y->im;
    res->im = x->re * y->im + x->im * y->re;
}

static void complex_zero(void *d) {
    Complex *c = d;
    c->re = 0.0;
    c->im = 0.0;
}

static const TypeInfo ComplexType = {
    sizeof(Complex),
    complex_copy,
    complex_print,
    complex_add,
    complex_mul,
    complex_zero
};

const TypeInfo *ofComplex() {
    return &ComplexType;
}
