#ifndef VECTOR_H
#define VECTOR_H

#include "type_info.h"

typedef struct {
    size_t size;
    void *data;
    const TypeInfo *type;
} Vector;

const TypeInfo *vector_type(const Vector *v);

Vector *vector_create(size_t size, const TypeInfo *type);
void vector_destroy(Vector *v);

size_t vector_size(const Vector *v);

int vector_set(Vector *v, size_t index, const void *value);
const void *vector_get(const Vector *v, size_t index);

Vector *vector_add(const Vector *a, const Vector *b);
int vector_dot(const Vector *a, const Vector *b, void *result);
Vector *vector_scale(const Vector *v, const void *scalar);

Vector *vector_clone(const Vector *v);
void vector_print(const Vector *v);

#endif
