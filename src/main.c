#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "real_type.h"
#include "int_type.h"
#include "complex_type.h"

static const TypeInfo *choose_type() {
    printf("Выберите тип:\n");
    printf("1 - int\n");
    printf("2 - double\n");
    printf("3 - complex\n");
    printf("Выбор: ");

    int t;
    if (scanf("%d", &t) != 1) return NULL;

    switch (t) {
        case 1: return ofInt();
        case 2: return ofReal();
        case 3: return ofComplex();
        default:
            printf("Неверный тип\n");
            return NULL;
    }
}

static void read_value(const TypeInfo *type, void *out) {
    if (type == ofInt()) {
        scanf("%d", (int *) out);
    } else if (type == ofReal()) {
        scanf("%lf", (double *) out);
    } else if (type == ofComplex()) {
        Complex *c = out;
        printf("real: ");
        scanf("%lf", &c->re);
        printf("imag: ");
        scanf("%lf", &c->im);
    }
}

static Vector *create_vector() {
    const TypeInfo *type = choose_type();
    if (!type) return NULL;

    size_t n;
    printf("Размер: ");

    if (scanf("%zu", &n) != 1) {
        printf("Ошибка ввода \n");
        return NULL;
    }

    Vector *v = vector_create(n, type);
    if (!v) return NULL;

    void *buffer = malloc(type->item_size);
    if (!buffer) {
        vector_destroy(v);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        printf("v[%zu]: ", i);
        read_value(type, buffer);
        vector_set(v, i, buffer);
    }
    free(buffer);
    return v;
}

static void scale(Vector **v) {
    if (!*v) {
        printf("Вектор не задан\n");
        return;
    }

    const TypeInfo *type = vector_type(*v);
    void *scalar = malloc(type->item_size);
    if (!scalar) {
        printf("Ошибка памяти\n");
        return;
    }

    printf("Введите скаляр:\n");
    read_value(type, scalar);

    Vector *r = vector_scale(*v, scalar);
    if (!r) {
        printf("Ошибка\n");
        free(scalar);
        return;
    }

    printf("Результат: ");
    vector_print(r);
    vector_destroy(r);
    free(scalar);
}

static void dot(Vector *a, Vector *b) {
    if (!a || !b) {
        printf("Векторы не заданы\n");
        return;
    }
    if (vector_type(a) != vector_type(b)) {
        printf("Типы различаются\n");
        return;
    }

    const TypeInfo *type = vector_type(a);
    void *result = malloc(type->item_size);
    if (!result) {
        printf("Ошибка памяти\n");
        return;
    }
    if (!vector_dot(a, b, result)) {
        printf("Ошибка\n");
        free(result);
        return;
    }

    printf("Dot = ");
    type->print(result);
    printf("\n");
    free(result);
}

static void add(Vector *a, Vector *b) {
    if (!a || !b) {
        printf("Векторы не заданы\n");
        return;
    }

    Vector *r = vector_add(a, b);

    if (!r) {
        printf("Ошибка сложения\n");
        return;
    }

    printf("A+B = ");
    vector_print(r);
    vector_destroy(r);
}

int main() {
    Vector *A = NULL;
    Vector *B = NULL;

    int run = 1;

    while (run) {
        printf("\n==== VECTOR MENU ====\n");
        printf("1 - Cоздать A\n");
        printf("2 - Cоздать B\n");
        printf("3 - Показать\n");
        printf("4 - A + B\n");
        printf("5 - Скалярное произведение\n");
        printf("6 - Умножение на скаляр\n");
        printf("0 - Выход\n");

        int c;
        printf("Выбор: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                vector_destroy(A);
                A = create_vector();
                break;
            case 2:
                vector_destroy(B);
                B = create_vector();
                break;
            case 3:
                printf("A = ");
                vector_print(A);
                printf("B = ");
                vector_print(B);
                break;
            case 4:
                add(A, B);
                break;
            case 5:
                dot(A, B);
                break;
            case 6: {
                printf("1 - A\n2 - B\n");

                int t;
                scanf("%d", &t);

                if (t == 1) scale(&A);
                else if (t == 2) scale(&B);
                break;
            }
            case 0:
                run = 0;
                break;
        }
    }

    vector_destroy(A);
    vector_destroy(B);

    return 0;
}
