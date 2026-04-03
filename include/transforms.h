#ifndef GMATH_TRANSFORMS_H
#define GMATH_TRANSFORMS_H

#include "types.h"
#include "constants.h"
#include "vector.h"
#include "utils.h"

// Core Matrix Operations
void matrix_identity (Matrix *result);
void matrix_identity3x3 (Matrix3x3 *result);
void matrix_mult (const Matrix *a, const Matrix *b, Matrix* result);
void matrix_vector_mult (const Matrix *a, const Vector *v, Vector* result);
void matrix3_vector3_mult (const Matrix3x3 *m, const Vector3 *v, Vector3* result);
void matrix_transpose (const Matrix *m, Matrix* result);
float matrix_determinant (const Matrix *m);
float matrix3x3_determinant (const Matrix3x3 *m);
void matrix_inverse(const Matrix *m, Matrix* result);

// Main Transformations
void matrix_translate (float x, float y, float z, Matrix* result);
void matrix_scale (float x, float y, float z, Matrix* result);
void matrix_rotate (Vector *axis, float angle_radians, Matrix* result);

// Camera and Viewing
void matrix_look_at (const Vector *eye, const Vector *target, const Vector *up, Matrix* result);
void matrix_perspective (float fov_deg, float aspect, float near, float far, Matrix* result);
void matrix_perspective_reversed_z(float fov_deg, float aspect, float near, float far, Matrix* result);
void matrix_perspective_infinite_reversed_z(float fov_deg, float aspect, float near, Matrix* result);
void matrix_ortho(float left, float right, float bottom, float top, float near, float far, Matrix* result);
void matrix_to_normal_matrix(const Matrix *model, Matrix3x3 *result);
void matrix_extract_frustum(const Matrix *view_proj, Vector planes[6]);
void matrix_extract_frustum_rev_z(const Matrix *view_proj, Vector planes[6]);

// Helpers
int matrix_compare (const Matrix *a, const Matrix *b);
void matrix_convert (int row_to_remove, int column_to_remove, const Matrix *input, Matrix3x3 *result);
void matrix3x3_convert (const Matrix3x3 *m, Matrix *result);
void matrix_cofactor(const Matrix *m, Matrix *result);
void matrix_set_to_zero (Matrix *m);
#endif //GMATH_TRANSFORMS_H
