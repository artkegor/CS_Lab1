#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

Vector *vector_create(size_t size, const TypeInfo *type) {
    if (!type) return NULL;

    Vector *v = malloc(sizeof(Vector));
    if (!v) return NULL;

    v->size = size;
    v->type = type;
    v->data = malloc(size * type->item_size);
    if (size && !v->data) {
        free(v);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        void *e = (char *) v->data + i * type->item_size;
        type->zero(e);
    }
    return v;
}

void vector_destroy(Vector *v) {
    if (!v) return;

    free(v->data);
    free(v);
}

size_t vector_size(const Vector *v) {
    return v ? v->size : 0;
}

const TypeInfo *vector_type(const Vector *v) {
    return v ? v->type : NULL;
}

int vector_set(Vector *v, size_t i, const void *val) {
    if (!v || i >= v->size || !val) return 0;
    void *dst = (char *) v->data + i * v->type->item_size;

    v->type->copy(dst, val);
    return 1;
}

const void *vector_get(const Vector *v, size_t i) {
    if (!v || i >= v->size) return NULL;
    return (char *) v->data + i * v->type->item_size;
}

Vector *vector_add(const Vector *a, const Vector *b) {
    if (!a || !b || a->size != b->size || a->type != b->type) return NULL;

    Vector *r = vector_create(a->size, a->type);
    if (!r) return NULL;

    for (size_t i = 0; i < a->size; i++) {
        const void *da = (char *) a->data + i * a->type->item_size;
        const void *db = (char *) b->data + i * b->type->item_size;
        void *dr = (char *) r->data + i * r->type->item_size;
        a->type->add(dr, da, db);
    }
    return r;
}

int vector_dot(const Vector *a, const Vector *b, void *result) {
    if (!a || !b || !result)
        return 0;

    if (a->size != b->size)
        return 0;

    if (a->type != b->type)
        return 0;

    const TypeInfo *t = a->type;
    t->zero(result);

    void *tmp = malloc(t->item_size);
    if (!tmp) return 0;

    for (size_t i = 0; i < a->size; i++) {
        const void *da = (char *) a->data + i * t->item_size;
        const void *db = (char *) b->data + i * t->item_size;

        t->mul(tmp, da, db);
        t->add(result, result, tmp);
    }
    free(tmp);
    return 1;
}

Vector *vector_clone(const Vector *v) {
    if (!v) return NULL;

    Vector *r = vector_create(v->size, v->type);
    if (!r) return NULL;

    for (size_t i = 0; i < v->size; i++) {
        const void *src = (char *) v->data + i * v->type->item_size;
        void *dst = (char *) r->data + i * v->type->item_size;
        v->type->copy(dst, src);
    }
    return r;
}

Vector *vector_scale(const Vector *v, const void *s) {
    if (!v || !s) return NULL;

    Vector *r = vector_create(v->size, v->type);
    if (!r) return NULL;

    for (size_t i = 0; i < v->size; i++) {
        const void *src = (char *) v->data + i * v->type->item_size;
        void *dst = (char *) r->data + i * v->type->item_size;
        v->type->mul(dst, src, s);
    }
    return r;
}

void vector_print(const Vector *v) {
    if (!v) {
        printf("null\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v->size; i++) {
        const void *e = (char *) v->data + i * v->type->item_size;
        v->type->print(e);
        if (i + 1 < v->size) printf(", ");
    }
    printf("]\n");
}
