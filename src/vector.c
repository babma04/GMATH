#include "../include/vector.h"
#include <stdio.h>
#include <math.h>

// Number of coordinates in a vector, defined as a constant for easy modification
static const int VLENGTH = 4;

//------------------------ Basic Vector Arithmetic ----------------------------

/**
 * Sums two vectors by summing their coordinates in pairs.
 * @param v First vector
 * @param u Second vector
 * @return A new vector with the sum of the input vectors
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector u = {5, 6, 7, 8};
 * Vector result = vector_sum(v, u); // result will be {6, 8
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4.
 */
void vector_sum (Vector *v, Vector *u, Vector* result)
{
    // Cycles over both input vectors and returns their coordenates summed in pairs
    for (int i = 0; i < VLENGTH; i++)
    {
        result->v[i] = v->v[i] + u->v[i];
    }
}

/**
 * Subtracts two vectors by subtracting their coordinates in pairs.
 * @param v First vector
 * @param u Second vector
 * @return A new vector with the difference of the input vectors
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector u = {5, 6, 7, 8};
 * Vector result = vector_sub(v, u); // result will be {-4, -4, -4, -4}
 * @warning This function does not check for the length of the
 */
void vector_sub (Vector *v, Vector *u, Vector* result)
{
    // Cycles over both input vectors and returns their coordenates subtracted in pairs
    for (int i = 0; i < VLENGTH; i++)
    {
        result->v[i] = v->v[i] - u->v[i];
    }
}

/**
 * Multiplies a vector by a scalar by multiplying each of its coordinates by the scalar.
 * @param v The vector to be multiplied
 * @param scalar The scalar to multiply the vector by
 * @return A new vector with the input vector multiplied by the scalar
 * Example:
 * Vector v = {1, 2, 3, 4};
 * float scalar = 2;
 * Vector result = vector_scalar(v, scalar); // result will be {2, 4, 6, 8}
 * @warning This function does not check for the length of the vector, it assumes it is of length 4.
 */
void vector_scalar (Vector *v, float scalar, Vector* result)
{
    // Cycles over the input vector and returns its coordenates multiplied by the scalar
    for (int i = 0; i < VLENGTH; i++)
    {
        result->v[i] = v->v[i] * scalar;
    }
}

//------------------------ Angular Vector Operations ----------------------------

/**
 * Calculates the angle between two vectors by using the formula:
 * angle = acos(dot(v, u) / (magnitude(v) * magnitude(u)))
 * @param v First vector
 * @param u Second vector
 * @return The angle between the input vectors in radians
 * Example:
 * Vector v = {1, 0, 0, 0};
 * Vector u = {0, 1, 0, 0};
 * float result = vectors_angle(v, u); // result will be pi/2 (90 degrees)
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4.
 * If either of the input vectors has zero magnitude, the function will print a warning message to the standard error stream and return 0, as the angle is undefined in this case.
 */
float vectors_angle (Vector *v, Vector *u)
{
    // Calculates the angle between the input vectors using the formula: angle = acos(dot(v, u) / (magnitude(v) * magnitude(u)))
    float dot_product = vector_dot(v, u);
    float magnitude_v = vector_magnitude(v);
    float magnitude_u = vector_magnitude(u);
    if (magnitude_v == 0.0 || magnitude_u == 0.0)
    {
        fprintf(stderr, "Warning: One of the input vectors has zero magnitude. Angle is undefined.\n");
        return 0.0;
    }
    float cos_angle = dot_product / (magnitude_v * magnitude_u);
    // Clamps the cosine of the angle to the range [-1, 1] to avoid numerical issues with acos
    if (cos_angle < -1.0) cos_angle = -1.0;
    if (cos_angle > 1.0) cos_angle = 1.0;
    return acosf(cos_angle);
}

//------------------------ Main Vector Operations ----------------------------

/**
 * Calculates the dot product of two vectors by multiplying their coordinates in pairs and summing the results.
 * @param v First vector
 * @param u Second vector
 * @return The dot product of the input vectors
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector u = {5, 6, 7, 8};
 * float result = vector_dot(v, u); // result will be 70 (1*5 + 2*6 + 3*7 + 4*8)
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4.
 */
float vector_dot (Vector *v, Vector *u)
{
    // Initializes the float value of return
    float result = 0.0;
    // Cycles over both input vectors and returns the sum of the products of their coordenates in pairs
    for (int i = 0; i < VLENGTH; i++)
    {
        result += v->v[i] * u->v[i];
    }
    return result;
}

/**
 * Calculates the cross product of two 3D vectors by using the formula:
 * cross(v, u) = (v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x)
 * @param v First vector
 * @param u Second vector
 * @return A new vector with the cross product of the input vectors
 * Example:
 * Vector v = {1, 2, 3, 0};
 * Vector u = {4, 5, 6, 0};
 * Vector result = vector_cross3D(v, u); // result will be {-3, 6, -3, 0}
 * @warning This function does not check for the length of the vectors.
 * It assumes they are both of length 4 and that the w coordinate is not used (i.e., the vectors are 3D vectors). 
 * The w coordinate of the result is set to 0, as the cross product of two 3D vectors is a 3D vector.
 */
void vector_cross3D (Vector *v, Vector *u, Vector* result)
{
    // Calculates the cross product of the input vectors using the formula:    
    result->x = v->y * u->z - v->z * u->y;
    result->y = v->z * u->x - v->x * u->z;
    result->z = v->x * u->y - v->y * u->x;
    // The w coordinate is set to 0, as the cross product of two 3D vectors is a 3D vector
    result->w = 0.0;
    
}

/**
 * Calculates the cross product of two 4D vectors by using the formula:
 * cross(v, u) = (v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x, v.y * u.w - v.w * u.y)
 * @param v First vector
 * @param u Second vector
 * @return A new vector with the cross product of the input vectors
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector u = {5, 6, 7, 8};
 * Vector result = vector_cross4D(v, u); // result will be {-4, -4, -4, -4}
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4. 
 * The cross product of two 4D vectors is not a well-defined operation in the same way as for 3D vectors, so this function uses a specific formula that is not universally accepted. 
 * The w coordinate of the result is calculated using the formula: v.y * u.w - v.w * u.y, which is not a standard definition of the cross product for 4D vectors. 
 * This function is provided for completeness, but its use should be carefully considered in the context of the specific application as its output is a plane defined by the two input vectors, and not a vector perpendicular to both as in the 3D case.
 */
void vector_cross4D (Vector *v, Vector *u, Vector* result)
{
    // XY Plane component
    result->x = (v->x * u->y) - (v->y * u->x);
    // XZ Plane component
    result->y = (v->x * u->z) - (v->z * u->x);
    // XW Plane component
    result->z = (v->x * u->w) - (v->w * u->x);
    // YZ Plane component
    result->w = (v->y * u->z) - (v->z * u->y);
}

/**
 * Calculates the magnitude of a vector by using the formula:
 * magnitude(v) = sqrt(v.x^2 + v.y^2 + v.z^2 + v.w^2)
 * @param v The vector for which to calculate the magnitude
 * @return The magnitude of the input vector
 * Example:
 * Vector v = {1, 2, 3, 4};
 * float result = vector_magnitude(v); // result will be sqrt(30)
 * @warning This function does not check for the length of the vector, it assumes it is of length 4.
 */
float vector_magnitude (Vector *v)
{
    // Initializes the float value of return
    float result = 0.0;
    // Cycles over the input vector and returns the square root of the sum of the squares of its coordenates
    for (int i = 0; i < VLENGTH; i++)
    {
        result += v->v[i] * v->v[i];
    }
    return sqrtf(result);
}

/**
 * Normalizes a vector by dividing each of its coordinates by its magnitude.
 * @param v The vector to be normalized
 * @return A new vector with the normalized version of the input vector
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector result = vector_normalize(v); // result will be {0.18257, 0.36515, 0.54772, 0.73030}
 * @warning This function does not check for the length of the vector, it assumes it is of length 4.
 * If the magnitude of the input vector is zero, the function returns a zero vector to avoid division by zero.
 */
void vector_normalize (Vector *v, Vector* result)
{
    // Calculates the magnitude of the input vector
    float mag = vector_magnitude(v);
    // Checks if the magnitude is not zero to avoid division by zero
    if (mag != 0.0)
    {
        // Cycles over the input vector and returns its coordenates divided by its magnitude
        for (int i = 0; i < VLENGTH; i++)
        {
            result->v[i] = v->v[i] / mag;
        }
    }
    else
    {
        // If the magnitude is zero, returns a zero vector
        for (int i = 0; i < VLENGTH; i++)
        {
            result->v[i] = 0.0;
        }
    }
}

// ------------------------ Interpolation ----------------------------

/**
 * Calculates the linear interpolation between two vectors by using the formula:
 * lerp(v, u, t) = v + t * (u - v)
 * @param v First vector
 * @param u Second vector
 * @param t The interpolation factor, between 0 and 1
 * @return A new vector with the linear interpolation of the input vectors
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4.
 * If the interpolation factor t is outside the range [0, 1], the function will print a warning message to the standard error stream.
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector u = {5, 6, 7, 8};
 * float t = 0.5;
 * Vector result = vector_lerp(v, u, t); // result will be {3, 4, 5, 6}
 */
void vector_lerp (Vector *v, Vector *u, float t, Vector* result)
{
    if (t < 0.0 || t > 1.0)
    {
        fprintf(stderr, "Warning: Interpolation factor t should be between 0 and 1.\n");
    }
    result->x = v->x + t * (u->x - v->x);
    result->y = v->y + t * (u->y - v->y);
    result->z = v->z + t * (u->z - v->z);
    result->w = v->w + t * (u->w - v->w);
}

/**
 * Calculates the linear interpolation between two vectors by using the formula:
 * safeLerp(v, u, t) = v + t * (u - v)
 * @param v First vector
 * @param u Second vector
 * @param t The interpolation factor, between 0 and 1
 * @return A new vector with the linear interpolation of the input vectors
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4.
 * If the interpolation factor t is outside the range [0, 1], the function will print a warning message to the standard error stream and clamp t to the range [0, 1].
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector u = {5, 6, 7, 8};
 * float t = 1.5;
 * Vector result = vector_safeLerp(v, u, t); // result will be {5, 6, 7, 8} and a warning message will be printed to the standard error stream because t is greater than 1. 
 * If t were -0.5, result would be {1, 2, 3, 4} and a warning message would be printed to the standard error stream because t is less than 0.
 */
void vector_safeLerp (Vector *v, Vector *u, float t, Vector* result)
{
    if (t < 0.0 || t > 1.0)
    {
        fprintf(stderr, "Warning: Interpolation factor t should be between 0 and 1. Clamping to [0, 1].\n");
        t = (t < 0.0) ? 0.0 : 1.0;
    }
    result->x = v->x + t * (u->x - v->x);
    result->y = v->y + t * (u->y - v->y);
    result->z = v->z + t * (u->z - v->z);
    result->w = v->w + t * (u->w - v->w);
}

/**
 * Calculates the spherical linear interpolation between two vectors by using the formula:
 * slerp(v, u, t) = (sin((1 - t) * angle) * v + sin(t * angle) * u) / sin(angle)
 * where angle is the angle between v and u calculated using the vectors_angle function.
 * @param v First vector
 * @param u Second vector
 * @param t The interpolation factor, between 0 and 1
 * @return A new vector with the spherical linear interpolation of the input vectors
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4.
 * If the interpolation factor t is outside the range [0, 1], the function will print a warning message to the standard error stream.
 * If the angle between the input vectors is zero, the function will print a warning message to the standard error stream and return the result of linear interpolation, as the spherical linear interpolation is undefined in this case.
 * Example:
 * Vector v = {1, 0, 0, 0};
 * Vector u = {0, 1, 0, 0};
 * float t = 0.5;
 * Vector result = vector_slerp(v, u, t); // result will be {0.70711, 0.70711, 0, 0} and a warning message will be printed to the standard error stream because the angle between v and u is 90 degrees, which is not zero but the function will still return the correct result. 
 * If v and u were parallel, for example v = {1, 0, 0, 0} and u = {2, 0, 0, 0}, result would be {1.5, 0, 0, 0} and a warning message would be printed to the standard error stream because the angle between v and u is zero.
 */
void vector_slerp (Vector *v, Vector *u, float t, Vector* result)
{
    if (t < 0.0 || t > 1.0)
    {
        fprintf(stderr, "Warning: Interpolation factor t should be between 0 and 1.\n");
    }
    float angle = vectors_angle(v, u);
    if (angle == 0.0)
    {
        // If the angle is zero, the vectors are parallel and we can use linear interpolation
        vector_lerp(v, u, t, result);
    }
    else
    {
        Vector *v_tmp = {0};
        Vector *u_tmp = {0};

        float sin_angle = sinf(angle);
        float factor_v = sinf((1 - t) * angle) / sin_angle;
        float factor_u = sinf(t * angle) / sin_angle;
        vector_scalar(v, factor_v, v_tmp);
        vector_scalar(u, factor_u, u_tmp);
        vector_add(v_tmp, u_tmp, result);
    }
}

/**
 * Calculates the spherical linear interpolation between two vectors with safety checks.
 * If the interpolation factor t is outside the range [0, 1], the function will print a warning message to the standard error stream and clamp t to the range [0, 1].
 * Else, it will call the vector_slerp function to perform the interpolation.
 * @param v First vector
 * @param u Second vector
 * @param t The interpolation factor, between 0 and 1
 * @param result A pointer to the vector where the result will be stored
 * @return A new vector with the spherical linear interpolation of the input vectors
 * @warning This function does not check for the length of the vectors, it assumes they are both of length 4.
 * If the interpolation factor t is outside the range [0, 1], the function will print a warning message to the standard error stream and clamp t to the range [0, 1].
 * If the angle between the input vectors is zero, the function will print a warning message to the standard error stream and return the result of linear interpolation, as the spherical linear interpolation is undefined in this case.
 * Example:
 * Vector v = {1, 0, 0, 0};
 * Vector u = {0, 1, 0, 0};
 * float t = 1.5;
 * Vector result = vector_safeSlerp(v, u, t); // result will be {0, 1, 0, 0} and a warning message will be printed to the standard error stream because t is greater than 1. 
 * If t were -0.5, result would be {1, 0, 0, 0} and a warning message would be printed to the standard error stream because t is less than 0. 
 * If v and u were parallel, for example v = {1, 0, 0, 0} and u = {2, 0, 0, 0}, result would be {1.5, 0, 0, 0} and a warning message would be printed to the standard error stream because the angle between v and u is zero.
 */
void vector_safeSlerp (Vector *v, Vector *u, float t, Vector* result)
{
    if (t < 0.0 || t > 1.0)
    {
        fprintf(stderr, "Warning: Interpolation factor t should be between 0 and 1. Clamping to [0, 1].\n");
        t = (t < 0.0) ? 0.0 : 1.0;
    }
    vector_slerp(v, u, t, result);   
}

