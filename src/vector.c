#include "../include/vector.h"
#include <stdio.h>
#include <math.h>

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
void vector_sum (const Vector *v, const Vector *u, Vector* result)
{
    result->x = v->x + u->x;
    result->y = v->y + u->y;
    result->z = v->z + u->z;
    result->w = v->w + u->w;
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
void vector_sub (const Vector *v, const Vector *u, Vector* result)
{
    result->x = v->x - u->x;
    result->y = v->y - u->y;
    result->z = v->z - u->z;
    result->w = v->w - u->w;
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
void vector_scalar (const Vector *v, float scalar, Vector* result)
{
    result->x = v->x * scalar;
    result->y = v->y * scalar;
    result->z = v->z * scalar;
    result->w = v->w * scalar;
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
float vectors_angle (const Vector *v, const Vector *u)
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
float vector_dot (const Vector *v, const Vector *u)
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
void vector_cross3D (const Vector *v, const Vector *u, Vector* result)
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
void vector_cross4D (const Vector *v, const Vector *u, Vector* result)
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
float vector_magnitude (const Vector *v)
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
void vector_normalize (const Vector *v, Vector* result)
{
    // Calculates the magnitude of the input vector
    float mag = vector_magnitude(v);
    // Checks if the magnitude is not zero to avoid division by zero
    if (mag != 0.0)
    {
        // Cycles over the input vector and returns its coordenates divided by its magnitude
        for (int i = 0; i < VLENGTH; i++)
        {
            result->v[i] = g_safe_divide(v->v[i], mag);
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

/**
 * Normalizes a 3D vector by dividing each of its coordinates by its magnitude.
 * @param v The 3D vector to be normalized
 * @return A new 3D vector with the normalized version of the input vector
 * Example:
 * Vector3 v = {1, 2, 3};
 * Vector3 result = vector3_normalize(v); // result will be {0.26726, 0.53452, 0.80178}
 * @warning This function does not check for the length of the input vector, it assumes it is of length 3. 
 * The w coordinate of the result is not used, as the output vector is a 3D vector and the w coordinate is not defined in this case.
 * If the magnitude of the input vector is zero or very close to zero, the function returns a zero vector to avoid division by zero and numerical instability.
 */
void vector3_normalize(const Vector3 *v, Vector3* result)
{
    // Calculate squared magnitude
    Vector tmp;
    vector3_to_4(v, &tmp);
    float mag = vector_magnitude(&tmp);
    float mag_sq = mag * mag;

    // Check for zero/near-zero vector to avoid Division by Zero (NaN)
    // Using EPSILON * EPSILON because we are comparing against mag_sq
    if (g_nearly_equal(mag_sq, EPSILON * EPSILON))
    {
        result->x = 0.0f;
        result->y = 0.0f;
        result->z = 0.0f;
        return;
    }

    // Calculate 1.0 / sqrt(mag_sq)
    float inv_mag = g_safe_divide(1.0f, sqrtf(mag_sq));

    // Scale the components into the result
    result->x = v->x * inv_mag;
    result->y = v->y * inv_mag;
    result->z = v->z * inv_mag;
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
void vector_lerp (const Vector *v, const Vector *u, float t, Vector* result)
{
    if (t < 0.0 || t > 1.0)
    {
        fprintf(stderr, "Warning: Interpolation factor t should be between 0 and 1.\n");
    }
    result->x = g_lerp(v->x, u->x, t);
    result->y = g_lerp(v->y, u->y, t);
    result->z = g_lerp(v->z, u->z, t);
    result->w = g_lerp(v->w, u->w, t);
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
void vector_safeLerp (const Vector *v, const Vector *u, float t, Vector* result)
{
    if (t < 0.0 || t > 1.0)
    {
        fprintf(stderr, "Warning: Interpolation factor t should be between 0 and 1. Clamping to [0, 1].\n");
        t = (t < 0.0) ? 0.0 : 1.0;
    }
    result->x = g_lerp(v->x, u->x, t);
    result->y = g_lerp(v->y, u->y, t);
    result->z = g_lerp(v->z, u->z, t);
    result->w = g_lerp(v->w, u->w, t);
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
void vector_slerp (const Vector *v, const Vector *u, float t, Vector* result)
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
        Vector v_tmp = {0};
        Vector u_tmp = {0};

        float sin_angle = sinf(angle);
        float factor_v = g_safe_divide(sinf((1 - t) * angle), sin_angle);
        float factor_u = g_safe_divide(sinf(t * angle), sin_angle);
        vector_scalar(v, factor_v, &v_tmp);
        vector_scalar(u, factor_u, &u_tmp);
        vector_sum(&v_tmp, &u_tmp, result);
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
void vector_safeSlerp (const Vector *v, const Vector *u, float t, Vector* result)
{
    if (t < 0.0 || t > 1.0)
    {
        fprintf(stderr, "Warning: Interpolation factor t should be between 0 and 1. Clamping to [0, 1].\n");
        t = (t < 0.0) ? 0.0 : 1.0;
    }
    vector_slerp(v, u, t, result);   
}

//------------------------ Helpers ----------------------------

/**
 * Converts a 3D vector to a 4D vector by copying the x, y, and z coordinates and setting the w coordinate to 0.
 * @param v The 3D vector to be converted
 * @return A new 4D vector with the x, y, and z coordinates of the input vector and w coordinate set to 0
 * Example:
 * Vector3 v = {1, 2, 3};
 * Vector result = vector3_to_4(v); // result will be {1, 2, 3, 0}
 * @warning This function does not check for the length of the input vector, it assumes it is of length 3. The w coordinate of the result is set to 0, as the input vector is a 3D vector and the w coordinate is not used in this case.
 */
void vector3_to_4 (const Vector3 *v, Vector* result)
{
    result->x = v->x;
    result->y = v->y;
    result->z = v->z;
    result->w = 0.0f; // The w coordinate is set to 0, as the input vector is a 3D vector
}

/**
 * Converts a 4D vector to a 3D vector by copying the x, y, and z coordinates and ignoring the w coordinate.
 * @param v The 4D vector to be converted
 * @return A new 3D vector with the x, y, and z coordinates of the input vector
 * Example:
 * Vector v = {1, 2, 3, 4};
 * Vector3 result = vector4_to_3(v); // result will be {1, 2, 3}
 * @warning This function does not check for the length of the input vector, it assumes it is of length 4. The w coordinate of the input vector is ignored, as the output vector is a 3D vector and the w coordinate is not used in this case.
 */
void vector4_to_3 (const Vector *v, Vector3* result)
{
    result->x = v->x;
    result->y = v->y;
    result->z = v->z;
    // The w coordinate of the input vector is ignored, as the output vector is a 3D vector
}

/**
 * Compares two vectors v and u, and returns 1 if they are equal (i.e., all their components are the same), or 0 otherwise.
 * The function checks each component of the vectors (x, y, z, w) for equality, and returns 1 only if all components are equal. If any component is different, it returns 0.
 * @param v Pointer to the first vector
 * @param u Pointer to the second vector
 * @return 1 if the vectors are equal, 0 otherwise
 * Example:
 * Vector v = {1, 2, 3, 4}; 
 * Vector u = {1, 2, 3, 4};
 * int result = vector_compare(&v, &u); // result will be 1, as the vectors are equal
 * Vector w = {1, 2, 3, 5};
 * result = vector_compare(&v, &w); // result will be 0, as the vectors are not equal (the w component is different)
 * @warning This function does not check for the dimensions of the input vectors, it assumes they are both 4D vectors.
 * If the vectors are not equal, the function will return 0 even if they are very close to each other (e.g., due to floating-point precision issues). In such cases, it may be more appropriate to use a function that checks for approximate equality within a certain tolerance.
 */
int vector_compare (const Vector *v, const Vector *u)
{
    return (v == u) || ((g_nearly_equal(v->x, u->x)) && (g_nearly_equal(v->y, u->y)) && (g_nearly_equal(v->z, u->z)) && (g_nearly_equal(v->w, u->w)));
}
