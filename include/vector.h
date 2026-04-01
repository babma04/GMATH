//
// Created by me on 4/1/26.
//

#ifndef GMATH_VECTOR_H
#define GMATH_VECTOR_H

#include "types.h"

// Basic Vector Arithmetic
Vector vector_sum (Vector v, Vector u);
Vector vector_sub (Vector v, Vector u);
Vector vecto_scalar (Vector v, float scalar);

// Main Vector Operations
float vector_dot (Vector v, Vector u);
Vector vector_cross (Vector v, Vector u);
float vector_magnitude (Vector v);
Vector vector_normalize (Vector v);

// Interpolation
Vector vector_lerp (Vector v, Vector u, float t);

#endif //GMATH_VECTOR_H
