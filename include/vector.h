#ifndef GMATH_VECTOR_H
#define GMATH_VECTOR_H

#include "types.h"
#include "constants.h"

// Basic Vector Arithmetic
void vector_sum (const Vector *v, const Vector *u, Vector* result);
void vector_sub (const Vector *v, const Vector *u, Vector* result);
void vector_scalar (const Vector *v, float scalar, Vector* result);

// Angular Vector Operations
float vectors_angle (const Vector *v, const Vector *u);


// Main Vector Operations
float vector_dot (const Vector *v, const Vector *u);
void vector_cross3D (const Vector *v, const Vector *u, Vector* result);
void vector_cross4D (const Vector *v, const Vector *u, Vector* result);
float vector_magnitude (const Vector *v);
void vector_normalize (const Vector *v, Vector* result);
void vector3_normalize(const Vector3 *v, Vector3* result);

// Interpolation
void vector_lerp (const Vector *v, const Vector *u, float t, Vector* result);
void vector_safeLerp (const Vector *v, const Vector *u, float t, Vector* result);
void vector_slerp (const Vector *v, const Vector *u, float t, Vector* result);
void vector_safeSlerp (const Vector *v, const Vector *u, float t, Vector* result);

// Helpers
void vector3_to_4 (const Vector3 *v, Vector* result);
void vector4_to_3 (const Vector *v, Vector3* result);
int vector_compare (const Vector *v, const Vector *u);


#endif //GMATH_VECTOR_H
