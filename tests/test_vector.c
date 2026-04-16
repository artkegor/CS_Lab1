#include <stdio.h>
#include <stdbool.h>
#include "../src/vector.h"
#include "../src/real_type.h"
#include "../src/int_type.h"
#include "../src/complex_type.h"

#define TITLE(name) printf("\n================ %s ================\n", name)

static int tests_run = 0;
static int tests_passed = 0;

void print_test(const char *name, bool ok) {
    tests_run++;

    if (ok) {
        tests_passed++;
        printf("[PASS] %s\n", name);
    } else {
        printf("[FAIL] %s\n", name);
    }
}

void print_vec(const char *name, Vector *v) {
    printf("%s = ", name);
    if (v)
        vector_print(v);
    else
        printf("NULL\n");
}

void test_real_all() {
    TITLE("REAL");

    Vector *a = vector_create(3, ofReal());
    Vector *b = vector_create(3, ofReal());

    double v1[] = {1, 2, 3};
    double v2[] = {4, 5, 6};

    for (int i = 0; i < 3; i++) {
        vector_set(a, i, &v1[i]);
        vector_set(b, i, &v2[i]);
    }

    print_vec("A", a);
    print_vec("B", b);

    printf("\n-- add --\n");
    Vector *c = vector_add(a, b);
    print_vec("A+B", c);
    print_test("real add", c != NULL);

    printf("\n-- dot --\n");
    double dot;
    bool ok = vector_dot(a, b, &dot);
    printf("dot(A,B) = %.2f\n", dot);
    print_test("real dot", ok && dot == 32);

    printf("\n-- scale --\n");
    double s = 2.0;
    Vector *scaled = vector_scale(a, &s);
    print_vec("A*2", scaled);
    print_test("real scale", scaled != NULL);

    printf("\n-- clone --\n");
    Vector *copy = vector_clone(a);
    print_vec("clone(A)", copy);
    print_test("real clone", copy != NULL);

    vector_destroy(a);
    vector_destroy(b);
    vector_destroy(c);
    vector_destroy(scaled);
    vector_destroy(copy);
}

void test_int_all() {
    TITLE("INT");

    Vector *a = vector_create(3, ofInt());
    Vector *b = vector_create(3, ofInt());

    int v1[] = {1, 2, 3};
    int v2[] = {4, 5, 6};

    for (int i = 0; i < 3; i++) {
        vector_set(a, i, &v1[i]);
        vector_set(b, i, &v2[i]);
    }

    print_vec("A", a);
    print_vec("B", b);

    printf("\n-- add --\n");
    Vector *c = vector_add(a, b);
    print_vec("A+B", c);
    print_test("int add", c != NULL);

    printf("\n-- dot --\n");
    int dot;
    bool ok = vector_dot(a, b, &dot);
    printf("dot(A,B) = %d\n", dot);
    print_test("int dot", ok && dot == 32);

    printf("\n-- scale --\n");
    int s = 3;
    Vector *scaled = vector_scale(a, &s);
    print_vec("A*3", scaled);
    print_test("int scale", scaled != NULL);

    printf("\n-- clone --\n");
    Vector *copy = vector_clone(a);
    print_vec("clone(A)", copy);
    print_test("int clone", copy != NULL);

    vector_destroy(a);
    vector_destroy(b);
    vector_destroy(c);
    vector_destroy(scaled);
    vector_destroy(copy);
}

void test_complex_all() {
    TITLE("COMPLEX");

    Vector *a = vector_create(2, ofComplex());
    Vector *b = vector_create(2, ofComplex());

    Complex v1[] = {{1, 2}, {5, 6}};
    Complex v2[] = {{3, 4}, {7, 8}};

    for (int i = 0; i < 2; i++) {
        vector_set(a, i, &v1[i]);
        vector_set(b, i, &v2[i]);
    }

    print_vec("A", a);
    print_vec("B", b);

    printf("\n-- add --\n");
    Vector *c = vector_add(a, b);
    print_vec("A+B", c);
    print_test("complex add", c != NULL);

    printf("\n-- dot --\n");
    Complex dot;
    bool ok = vector_dot(a, b, &dot);
    printf("dot(A,B) = (%.2f%+.2fi)\n", dot.re, dot.im);
    print_test("complex dot", ok);

    printf("\n-- scale --\n");
    Complex s = {3, 4};
    Vector *scaled = vector_scale(a, &s);
    print_vec("A*(3+4i)", scaled);
    print_test("complex scale", scaled != NULL);

    printf("\n-- clone --\n");
    Vector *copy = vector_clone(a);
    print_vec("clone(A)", copy);
    print_test("complex clone", copy != NULL);

    vector_destroy(a);
    vector_destroy(b);
    vector_destroy(c);
    vector_destroy(scaled);
    vector_destroy(copy);
}

void test_size_mismatch() {
    TITLE("SIZE MISMATCH");

    Vector *a = vector_create(2, ofReal());
    Vector *b = vector_create(3, ofReal());

    printf("-- add mismatch --\n");

    Vector *add = vector_add(a, b);
    printf("result = %s\n", add ? "vector" : "NULL");
    print_test("size mismatch add", add == NULL);

    printf("\n-- dot mismatch --\n");

    double r;
    bool dot = vector_dot(a, b, &r);
    printf("result = %s\n", dot ? "true" : "false");
    print_test("size mismatch dot", !dot);

    vector_destroy(a);
    vector_destroy(b);
}

void test_type_mismatch() {
    TITLE("TYPE MISMATCH");

    Vector *a = vector_create(3, ofReal());
    Vector *b = vector_create(3, ofInt());

    printf("-- add mismatch --\n");
    Vector *add = vector_add(a, b);
    printf("result = %s\n", add ? "vector" : "NULL");
    print_test("type mismatch add", add == NULL);

    printf("-- dot mismatch --\n");
    double r;
    bool dot = vector_dot(a, b, &r);
    printf("result = %s\n", dot ? "true" : "false");
    print_test("type mismatch dot", !dot);

    vector_destroy(a);
    vector_destroy(b);
}

int main() {
    printf("VECTOR TESTS\n");

    test_real_all();
    test_int_all();
    test_complex_all();
    test_size_mismatch();
    test_type_mismatch();

    printf("\n====================================\n");
    printf("RESULT: %d / %d tests passed\n", tests_passed, tests_run);
    printf("====================================\n");

    return 0;
}
