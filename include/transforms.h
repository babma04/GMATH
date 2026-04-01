//
// Created by me on 4/1/26.
//

#ifndef GMATH_TRANSFORMS_H
#define GMATH_TRANSFORMS_H

#include "types.h"

// Core matrix Operations
Matrix matrix_identity ();
Matrix matrix_mult (Matrix a, Matrix b);
Vector matrix_vector_mult (Matrix a, Vector v);
Matrix matrix_inverse(Matrix m);

// Main Transformations
Matrix matrix_translate (float x, float y, float z);
Matrix matrix_scale (float x, float y, float z);
Matrix matrix_rotate (float x, float y, float z);

// Camera and Viewing
Matrix matrix_look_at (Vector eye, Vector target, Vector up);
Matrix matrix_perspective (float fov_deg, float aspect, float near, float far);

#endif //GMATH_TRANSFORMS_H
