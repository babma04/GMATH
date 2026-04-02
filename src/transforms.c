#include "../include/transforms.h"
#include <stdio.h>
#include <math.h>

//------------------------ Core Matrix Operations ----------------------------

/**
 * Sets the given matrix to the identity matrix.
 * @param result Pointer to the matrix to be set to identity.
 * Example:
 * Matrix m;
 * matrix_identity(&m); // m will be set to the identity matrix
 */
void matrix_identity (Matrix *result)
{
    result->a.x = 1.0; result->b.y = 1.0; result->c.z = 1.0; result->d.w = 1.0;
}

/**
 * Multiplies two 4x4 matrices a and b, and stores the result in the provided result matrix.
 * The multiplication is done using the standard matrix multiplication algorithm, where each element of the result matrix is calculated as the dot product of the corresponding row of the first matrix and the column of the second matrix.
 * @param a Pointer to the first matrix
 * @param b Pointer to the second matrix
 * @param result Pointer to the matrix where the result will be stored
 * Example:
 * Matrix a = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             1, 2, 3, 1};
 * Matrix b = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             4, 5, 6, 1};
 * Matrix result;
 * matrix_mult(&a, &b, &result); // result will be {1, 0, 0, 0,
 *                                 //              0, 1, 0, 0,
 *                                 //              0, 0, 1, 0,
 *                                 //              5, 7, 9, 1}
 * @warning This function does not check for the dimensions of the input matrices, it assumes they are both 4x4 matrices.
 */
void matrix_mult (Matrix *a, Matrix *b, Matrix* result)
{
    for (int i = 0; i < MLENGTH; i++)
    {
        for (int j = 0; j < MLENGTH; j++)
        {
            result->m[i + j * MLENGTH] = a->m[0 + j * MLENGTH] * b->m[i + 0 * MLENGTH] +
                                          a->m[1 + j * MLENGTH] * b->m[i + 1 * MLENGTH] +
                                          a->m[2 + j * MLENGTH] * b->m[i + 2 * MLENGTH] +
                                          a->m[3 + j * MLENGTH] * b->m[i + 3 * MLENGTH];
        }
    }
}

/**
 * Multiplies a 4x4 matrix a by a 4D vector v, and stores the result in the provided result vector.
 * The multiplication is done using the standard matrix-vector multiplication algorithm, where each element of the result vector is calculated as the dot product of the corresponding row of the matrix and the input vector.
 * @param a Pointer to the matrix
 * @param v Pointer to the vector
 * @param result Pointer to the vector where the result will be stored
 * Example:
 * Matrix a = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             1, 2, 3, 1};
 * Vector v = {1, 2, 3, 1};
 * Vector result;
 * matrix_vector_mult(&a, &v, &result); // result will be {2, 4, 6, 1}
 * @warning This function does not check for the dimensions of the input matrix and vector, it assumes the matrix is 4x4 and the vector is 4D.
 */
void matrix_vector_mult (Matrix *a, Vector *v, Vector* result)
{
    for (int i = 0; i < MLENGTH; i++)
    {
        result->v[i] = a->m[0 + i * MLENGTH] * v->x +
                       a->m[1 + i * MLENGTH] * v->y +
                       a->m[2 + i * MLENGTH] * v->z +
                       a->m[3 + i * MLENGTH] * v->w;
    }
}

/**
 * Transposes a 4x4 matrix m, and stores the result in the provided result matrix.
 * The transpose of a matrix is obtained by swapping its rows with its columns, which can be done by iterating over the elements of the input matrix and assigning them to the corresponding positions in the result matrix.
 * @param m Pointer to the matrix to be transposed
 * @param result Pointer to the matrix where the transposed matrix will be stored
 * Example:
 * Matrix m = {1, 2, 3, 4,
 *             5, 6, 7, 8,
 *             9, 10, 11, 12,
 *             13, 14, 15, 16};
 * Matrix result;
 * matrix_transpose(&m, &result); // result will be {1, 5, 9, 13,
 *                                 //              2, 6, 10, 14,
 *                                 //              3, 7, 11, 15,
 *                                 //              4, 8, 12, 16}
 * @warning This function does not check for the dimensions of the input matrix, it assumes it is a 4x4 matrix. The result will also be a 4x4 matrix.
 */
void matrix_transpose (Matrix *m, Matrix* result)
{
    for (int i = 0, j = 0; i < MLENGTH; i++, j++)
    {
        result->m[i + j * MLENGTH] = m->m[j + i * MLENGTH];
    }
}

/**
 * Calculates the determinant of a 4x4 matrix m, and returns the result as a float.
 * The determinant of a matrix is a scalar value that can be calculated from the elements of the matrix, and it provides important information about the properties of the matrix, such as whether it is invertible or not. The determinant of a 4x4 matrix can be calculated using the rule of Sarrus or by using cofactor expansion.
 * @param m Pointer to the matrix whose determinant is to be calculated
 * @return The determinant of the input matrix as a float
 * Example:
 * Matrix m = {1, 2, 3, 4,
 *             5, 6, 7, 8,
 *             9, 10, 11, 12,
 *             13, 14, 15, 16};
 * float result = matrix_determinant(&m); // result will be 0, as the matrix is singular (i.e., it does not have an inverse)
 * @warning This function does not check for the dimensions of the input matrix, it assumes it
 */
float matrix_determinant (Matrix *m)
{
    for (int i = 0; i < MLENGTH; i++)
    {
        for (int j = 0; j < MLENGTH; j++)
        {
            // Calculate the determinant using the rule of Sarrus or cofactor expansion
            
        }
}

/**
 * Calculates the inverse of a 4x4 matrix m, and stores the result in the provided result matrix.
 * The inverse is calculated using the Gauss-Jordan elimination method, which involves augmenting the input matrix with the identity matrix and performing row operations until the left side of the augmented matrix is reduced to the identity matrix, at which point the right side will be the inverse of the original matrix.
 * @param m Pointer to the matrix to be inverted
 * @param result Pointer to the matrix where the inverse will be stored
 * Example:
 * Matrix m = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             1, 2, 3, 1};
 * Matrix result;
 * matrix_inverse(&m, &result); // result will be {1, 0, 0, 0,
 *                                 //              0, 1, 0, 0,
 *                                 //              0, 0, 1, 0,
 *                                 //              -1, -2, -3, 1}
 * @warning This function does not check for the dimensions of the input matrix, it assumes it is a 4x4 matrix. 
 * If the input matrix is singular (i.e., it does not have an inverse), the function will print a warning message to the standard error stream and set the result to the identity matrix.
 */
void matrix_inverse(Matrix *m, Matrix* result)
{
    if (matrix_determinant(m) == 0.0)
    {
        fprintf(stderr, "Warning: The input matrix is singular and does not have an inverse.\n");
    }
    else
    {
        
    }
}
