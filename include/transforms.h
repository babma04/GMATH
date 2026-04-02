#ifndef GMATH_TRANSFORMS_H
#define GMATH_TRANSFORMS_H

#include "types.h"
#include "constants.h"

// Core Matrix Operations
void matrix_identity (Matrix *result);
void matrix_mult (Matrix *a, Matrix *b, Matrix* result);
void matrix_vector_mult (Matrix *a, Vector *v, Vector* result);
void matrix_transpose (Matrix *m, Matrix* result);
float matrix_determinant (Matrix *m);
float matrix3x3_determinant (Matrix3x3 *m);
void matrix_inverse(Matrix *m, Matrix* result);

// Main Transformations
void matrix_translate (float x, float y, float z, Matrix* result);
void matrix_scale (float x, float y, float z, Matrix* result);
void matrix_rotate (float x, float y, float z, Matrix* result);

// Camera and Viewing
void matrix_look_at (Vector *eye, Vector *target, Vector *up, Matrix* result);
void matrix_perspective (float fov_deg, float aspect, float near, float far, Matrix* result);
#endif //GMATH_TRANSFORMS_H
