#ifndef GMATH_TYPES_H
#define GMATH_TYPES_H

// Default vector struct
/**
 * Defines a vector with up to 4 coordinates.
 * Coordinates meaning is context dependent
 */
typedef struct {
    union {
        struct {float x, y, z, w;};
        float v[4];
    };
} Vector;

/**
 * Defines a 3D vector with 3 coordinates.
 * Coordinates meaning is context dependent
 * The w coordinate is not used in this struct, as it is meant to represent a 3D vector. However, it can be accessed as v[3] if needed.
 */
typedef struct {
    union {
        struct {float x, y, z;};
        float v[3];
    };
} Vector3;


// Default Matrix struct
/**
 * Defines a 4x4 matrix with column-major ordering.
 * Column-Major order: a is column 1, b is column 2 and so on
 */
typedef struct {
    union {
        struct {Vector a, b, c, d;}; // Use the matrix as 4 separate vectors
        float m[16]; // Use the matrix as a single array with 16 entries, still Column-Major
    };
} Matrix;

/**
 * Defines a 3x3 matrix with column-major ordering.
 * Column-Major order: a is column 1, b is column 2 and c is column 3
 */
typedef struct {
    union {
        struct {Vector3 a, b, c;}; // Use the triangle as 3 separate vectors
        float m[9]; // Use the triangle as a single array with 9 entries, still Column-Major
    };
} Matrix3x3;

/**
 * Defines a quaternion with 4 coordinates: x, y, z, w.
 * The x, y, and z coordinates represent the vector part of the quaternion, while the w coordinate represents the scalar part. 
 * To Be used in a future implementation of a separate quaternion.h and .c files
 */
typedef struct {
    union {
            struct {float x, y, z, w;};
            float q[4];
    };
} Quaternion;


#endif
