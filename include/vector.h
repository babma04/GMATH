#ifndef GMATH_VECTOR_H
#define GMATH_VECTOR_H

#include "types.h"
#include "constants.h"

// Basic Vector Arithmetic
void vector_sum (Vector *v, Vector *u, Vector* result);
void vector_sub (Vector *v, Vector *u, Vector* result);
void vector_scalar (Vector *v, float scalar, Vector* result);

// Angular Vector Operations
float vectors_angle (Vector *v, Vector *u);


// Main Vector Operations
float vector_dot (Vector *v, Vector *u);
void vector_cross3D (Vector *v, Vector *u, Vector* result);
void vector_cross4D (Vector *v, Vector *u, Vector* result);
float vector_magnitude (Vector *v);
void vector_normalize (Vector *v, Vector* result);

// Interpolation
void vector_lerp (Vector *v, Vector *u, float t, Vector* result);
void vector_safeLerp (Vector *v, Vector *u, float t, Vector* result);
void vector_slerp (Vector *v, Vector *u, float t, Vector* result);
void vector_safeSlerp (Vector *v, Vector *u, float t, Vector* result);

#endif //GMATH_VECTOR_H
