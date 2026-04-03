#include "../include/utils.h"
#include <stdio.h>
#include <math.h>

/**
 * Clamps a value between a minimum and maximum range. If the value is less than the minimum, it returns the minimum. If the value is greater than the maximum, it returns the maximum. Otherwise, it returns the original value.
 * @param value The value to be clamped
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 * @return The clamped value, which will be between min and max
 * Example:
 * float value = 5.0f;
 * float min = 0.0f;
 * float max = 10.0f;
 * float result = g_clamp(value, min, max); // result will be 5.0f, as it is already within the range [0, 10]
 * If value were -2.0f, result would be 0.0f, as it is less than the minimum. If value were 12.0f, result would be 10.0f, as it is greater than the maximum.
 * @warning This function does not check for the relationship between min and max, it assumes that min is less than or equal to max. If min is greater than max, the behavior of the function is undefined.
 */
float g_clamp (float value, float min, float max)
{
    if (value < min) return min;
    else if (value > max) return max;
    else return value;
}

/**
 * Returns the minimum of two float values. If a is less than b, it returns a. Otherwise, it returns b.
 * @param a First float value
 * @param b Second float value
 * @return The minimum of a and b
 * Example:
 * float a = 3.5f;
 * float b = 2.0f;
 * float result = g_min(a, b); // result will be 2.0f, as it is the smaller of the two values
 * If a were 1.0f and b were 4.0f, result would be 1.0f, as it is the smaller of the two values.
 */
float g_min (float a, float b)
{
    return (a < b) ? a : b;
}

/**
 * Returns the maximum of two float values. If a is greater than b, it returns a. Otherwise, it returns b.
 * @param a First float value
 * @param b Second float value
 * @return The maximum of a and b
 * Example:
 * float a = 3.5f;
 * float b = 2.0f;
 * float result = g_max(a, b); // result will be 3.5f, as it is the larger of the two values
 * If a were 1.0f and b were 4.0f, result would be 4.0f, as it is the larger of the two values.
 */
float g_max (float a, float b)
{
    return (a > b) ? a : b;
}   

/**
 * Performs a safe division of two float values. If the denominator is nearly equal to zero (within a small epsilon range), it returns 0.0f to avoid division by zero errors. Otherwise, it returns the result of the division.
 * @param numerator The numerator of the division
 * @param denominator The denominator of the division
 * @return The result of the division if the denominator is not nearly zero, or 0.0f if the denominator is nearly zero
 * Example:
 * float numerator = 10.0f;
 * float denominator = 2.0f;
 * float result = g_safe_divide(numerator, denominator); // result will be 5.0f, as the division is valid
 * If denominator were 0.0f, result would be 0.0f, as the function would detect that the denominator is nearly zero and return 0.0f to avoid division by zero errors.
 * @warning This function does not check for the relationship between numerator and denominator, it assumes that they are both valid float values. If the denominator is nearly zero, the function will return 0.0f, which may not be the desired behavior in all cases, so it is important to use this function with caution and ensure that the inputs are appropriate for the context in which it is being used.
 */
float g_safe_divide(float numerator, float denominator) {
    if (g_nearly_equal(denominator, 0.0f)) return 0.0f;
    return numerator / denominator;
}

/**
 * Performs a linear interpolation between two float values a and b using an interpolation factor t. The formula used is: result = a + t * (b - a). If t is 0, the result will be a. If t is 1, the result will be b. If t is between 0 and 1, the result will be a value between a and b.
 * @param a The starting float value
 * @param b The ending float value
 * @param t The interpolation factor, typically between 0 and 1
 * @return The interpolated float value between a and b based on the interpolation factor t
 * Example:
 * float a = 10.0f;
 * float b = 20.0f;
 * float t = 0.5f;
 * float result = g_lerp(a, b, t); // result will be 15.0f, as it is the midpoint between 10.0f and 20.0f based on the interpolation factor of 0.5
 * If t were 0.25f, result would be 12.5f, as it is a quarter of the way from 10.0f to 20.0f. If t were 0.75f, result would be 17.5f, as it is three quarters of the way from 10.0f to 20.0f.
 * @warning This function does not check for the range of t, it assumes that t is a valid interpolation factor. If t is outside the range [0, 1], the result may not be meaningful as it would extrapolate beyond the range defined by a and b. It is important to ensure that t is within the expected range for the context in which this function is being used to avoid unintended results.
 */
float g_lerp(float a, float b, float t) {
    return a + t * (b - a);
}

/**
 * Checks if two float values are nearly equal by comparing the absolute difference between them to a small epsilon value. If the absolute difference is less than epsilon, it returns 1 (true). Otherwise, it returns 0 (false).
 * @param a First float value
 * @param b Second float value
 * @return 1 if a and b are nearly equal, 0 otherwise
 * Example:
 * float a = 0.1f + 0.2f; // Due to floating-point precision, this may not be exactly 0.3f
 * float b = 0.3f;
 * int result = is_nearly_equal(a, b); // result will be 1 (true), as a and b are nearly equal within the precision limits of floating-point representation
 * If a were 0.1f and b were 0.2f, result would be 0 (false), as they are not nearly equal.
 */
int g_nearly_equal (float a, float b)
{
    return fabsf(a - b) < EPSILON;
}

/**
 * Prints the components of a vector to the standard output in a readable format.
 * @param v The vector to be printed
 * @param label The label for the vector to be printed (for labeling purposes)
 * Example:
 * Vector v = {1.0f, 2.0f, 3.0f, 4.0f};
 * g_print_vector(&v, "MyVector"); // This will print "Vector MyVector: ( |1.0000|\n |2.0000|\n |3.0000|\n |4.0000|\n)\n" to the standard output with the components of the vector formatted to four decimal places.
 * @warning This function does not check for the length of the vector, it assumes it is of length 4. The output format is fixed to four decimal places for each component.
 */
void g_print_vector (const Vector *v, const char *label)
{
    printf("Vector %s: ( |%.4f|\n |%.4f|\n |%.4f|\n |%.4f|\n)\n", label, v->x, v->y, v->z, v->w);
}

/**
 * Prints the components of a matrix to the standard output in a readable format. The matrix is printed in column-major order, with each column on a new line.
 * @param m The matrix to be printed
 * @param label The label for the matrix to be printed (for labeling purposes)
 * Example:
 * Matrix m = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             1, 2, 3, 1};
 * g_print_matrix(&m, "MyMatrix"); // This will print the following to the standard output:
 * Matrix MyMatrix:
 * | 1.0000 0.0000 0.0000 0.0000 |
 * | 0.0000 1.0000 0.0000 0.0000 |
 * | 0.0000 0.0000 1.0000 0.0000 |
 * | 1.0000 2.0000 3.0000 1.0000 |
 * @warning This function does not check for the dimensions of the input matrix, it assumes it is a 4x4 matrix. The output format is fixed to four decimal places for each component, and the matrix is printed in column-major order. Each column of the matrix is printed on a new line, with the components of the column separated by spaces and enclosed in vertical bars for readability.
 */
void g_print_matrix (const Matrix *m, const char *label)
{
    printf("Matrix %s:\n", label);
    for (int row = 0; row < MLENGTH; row++) {
        printf("| ");
        for (int col = 0; col < MLENGTH; col++) {
            printf("%.4f ", m->m[col * 4 + row]);
        }
        printf("|\n");
    }
}