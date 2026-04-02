#ifndef GMATH_CONSTANTS_H
#define GMATH_CONSTANTS_H

// Number of coordinates in a vector, defined as a constant for easy modification
static const int VLENGTH = 4;
// Number of elements in a matrix, defined as a constant for easy modification
static const int MVLENGTH = 4;
static const int MLENGTH = 16;

// Error rounding value
#define EPSILON 0.000001f
// Pi value
#define PI 3.14159265358979323846f
// Degrees and radian convertion constants
#define DEG2RAD (PI / 180.0f)
#define RAD2DEG (180.0f / PI)

#endif //GMATH_CONSTANTS_H
