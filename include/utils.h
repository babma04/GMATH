#ifndef GMATH_UTILS_H
#define GMATH_UTILS_H

#include "types.h"
#include "constants.h"

// Value constraints
float g_clamp (float value, float min, float max);
float g_min (float a, float b);
float g_max (float a, float b);
float g_safe_divide (float numerator, float denominator);
float g_lerp (float a, float b, float t);

// Angle conversions
static inline float g_to_radians (float degrees) {return degrees * DEG2RAD;}
static inline float g_to_degrees (float radians) {return radians * RAD2DEG;}

// Float comparison
int g_nearly_equal (float a, float b);
int g_math_cmp(float a, float b);

// Math visualizer utils
void g_print_vector (const Vector *v, const char *label);
void g_print_matrix (const Matrix *m, const char *label);

#endif //GMATH_UTILS_H
