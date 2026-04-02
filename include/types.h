#ifndef GMATH_TYPES_H
#define GMATH_TYPES_H

// Default vector struct
/**
 * Defines a vector with up to 4 coordinates.
 * Coordinates meaning is context dependent
 */
typedef struct {
    union {
        float x, y, z, w;
        float v[4];
    };
} Vector;


// Default Matrix struct
// Column-Major order: a is column 1, b is column 2 and so on
typedef struct {
    union {
        struct {Vector a, b, c, d;}; // Use the matrix as 4 separate vectors
        float m[16]; // Use the matrix as a single array with 16 entries, still Column-Major
    };
} Matrix;

#endif
