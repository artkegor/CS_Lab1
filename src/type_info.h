#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <stddef.h>

typedef struct {
    size_t item_size;

    void (*copy)(void *dest, const void *src);

    void (*print)(const void *data);

    void (*add)(void *dest, const void *a, const void *b);

    void (*mul)(void *dest, const void *a, const void *b);

    void (*zero)(void *dest);
} TypeInfo;

#endif
