#ifndef GMATH_TYPES_H
#define GMATH_TYPES_H

// Default vector struct
/**
 * Defines a vector with up to 4 coordenates
 * Coordenates meaning is context dependent
 */
typedef struct {
    float x, y, z, w;
} Vector;


// Default Matrix struct
// Column-Major order: a is column 1, b is column 2 and so on
typedef struct {
    Vector a, b, c, d;
} Matrix;

typedef struct {
    union {
        struct {Vector a, b, c, d;}; // Use the matrix as 4 seperate vectors
        float m[16]; // Use the matrix as a single array with 16 entries, still Column-Major
    };
} FMatrix;

#endif
