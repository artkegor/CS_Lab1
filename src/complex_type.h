#ifndef COMPLEX_TYPE_H
#define COMPLEX_TYPE_H

#include "type_info.h"

typedef struct {
    double re;
    double im;
} Complex;

const TypeInfo *ofComplex();

#endif
