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
 * Sets the given 3x3 matrix to the identity matrix.
 * @param result Pointer to the 3x3 matrix to be set to identity.
 * Example:
 * Matrix3x3 m;
 * matrix_identity3x3(&m); // m will be set to the 3x3 identity matrix
 */
void matrix_identity3x3 (Matrix3x3 *result)
{
    result->a.x = 1.0; result->b.y = 1.0; result->c.z = 1.0;
}

/**
 * Multiplies two 4x4 matrices a and b, and stores the result in the provided result matrix.
 * The multiplication is done using the standard matrix multiplication algorithm, where each element of the result matrix is calculated as the dot product of the corresponding row of the first matrix and the corresponding column of the second matrix. The function iterates over each column and row of the result matrix, calculating the sum of products for each element.
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
void matrix_mult (const Matrix *a, const Matrix *b, Matrix* result)
{
    Matrix tmp;
    for (int col = 0; col < MLENGTH; col++) {
        for (int row = 0; row < MLENGTH; row++) {
            float sum = 0.0f;
            for (int k = 0; k < MLENGTH; k++) {
                // (Row 'row' of A) * (Column 'col' of B)
                // In Column-Major:
                // Row 'row', Col 'k' is: [k * 4 + row]
                // Row 'k', Col 'col' is: [col * 4 + k]
                sum += a->m[k * 4 + row] * b->m[col * 4 + k];
            }
            tmp.m[col * 4 + row] = sum;
        }
    }
    *result = tmp;
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
void matrix_vector_mult (const Matrix *a, const Vector *v, Vector* result)
{
    for (int i = 0; i < MLENGTH; i++)
    {
        result->v[i] = a->m[i + 0] * v->x + 
                       a->m[i + 4] * v->y + 
                       a->m[i + 8] * v->z + 
                       a->m[i + 12] * v->w; 
    }
}

/**
 * Multiplies a 3x3 matrix m by a 3D vector v, and stores the result in the provided result vector. 
 * The multiplication is done using the standard matrix-vector multiplication algorithm, where each element of the result vector is calculated as the dot product of the corresponding row of the matrix and the input vector.
 * @param m Pointer to the 3x3 matrix
 * @param v Pointer to the 3D vector
 * @param result Pointer to the 3D vector where the result will be stored
 * Example:
 * Matrix3x3 m = {1, 0, 0,
 *               0, 1, 0,
 *              0, 0, 1};
 * Vector3 v = {1, 2, 3};
 * Vector3 result;
 * matrix3_vector3_mult(&m, &v, &result); // result will be {1, 2, 3} as the input matrix is the identity matrix
 * @warning This function does not check for the dimensions of the input matrix and vector, it assumes the input matrix is 3x3 and the vector is 3D. The resulting vector will be a 3D vector that is the product of the input matrix and vector.
 * 
 */
void matrix3_vector3_mult (const Matrix3x3 *m, const Vector3 *v, Vector3* result)
{
    float x = m->m[0] * v->x + m->m[3] * v->y + m->m[6] * v->z;
    float y = m->m[1] * v->x + m->m[4] * v->y + m->m[7] * v->z;
    float z = m->m[2] * v->x + m->m[5] * v->y + m->m[8] * v->z;

    result->x = x;
    result->y = y;
    result->z = z;
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
void matrix_transpose (const Matrix *m, Matrix* result)
{
    for (int col = 0; col < MLENGTH; col++)
    {
        for (int row = 0; row < MLENGTH; row++)
        {
            result->m[col + row * MLENGTH] = m->m[row + col * MLENGTH];
        }
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
float matrix_determinant (const Matrix *m)
{
    float det = 0.0f;
    Matrix3x3 minor;
    float sign = 1.0f;

    for (int i = 0; i < MLENGTH; i++)
    {
        // gets the 3x3 submatrix for the laplace expansion
        matrix_convert(0, i, m, &minor); 
        // Uses the laplace expansion to calculate the determinant of the 4x4 matrix, by multiplying the element of the first row with the determinant of the corresponding 3x3 submatrix, and alternating the sign for each term.
        det += sign * m->m[i * 4] * matrix3x3_determinant(&minor); 
        // Alternates the sign for the next term in the expansion
        sign = -sign;
    }
    return det;
}

/**
 * Calculates the determinant of a 3x3 matrix m, and returns the result as a float.
 * The determinant of a matrix is a scalar value that can be calculated from the elements of the matrix, and it provides important information about the properties of the matrix, such as whether it is invertible or not. The determinant of a 3x3 matrix can be calculated using the rule of Sarrus or by using cofactor expansion.
 * @param m Pointer to the 3x3 matrix whose determinant is to be calculated
 * @return The determinant of the input 3x3 matrix as a float
 * Example:
 * Matrix3x3 m = {1, 2, 3,
 *                4, 5, 6,
 *                7, 8, 9};
 * float result = matrix3_determinant(&m); // result will be 0, as the matrix is singular (i.e., it does not have an inverse)
 * @warning This function does not check for the dimensions of the input matrix, it assumes it is a 3x3 matrix.
 */
float matrix3x3_determinant (const Matrix3x3 *m)
{
    // Calculate the determinant of the upper-left 3x3 submatrix of m
    return m->a.x * (m->b.y * m->c.z - m->b.z * m->c.y) -
           m->b.x * (m->a.y * m->c.z - m->a.z * m->c.y) +
           m->c.x * (m->a.y * m->b.z - m->a.z * m->b.y);
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
void matrix_inverse(const Matrix *m, Matrix* result)
{   
    // Validating the determinant
    float det = matrix_determinant(m);
    if (g_nearly_equal(det, 0.0f) == 1)
    {
        fprintf(stderr, "Warning: The input matrix is singular and does not have an inverse.\n");
        matrix_identity(result);
    }
    else
    {
        // Getting the cofactor matrix
        Matrix cofactor;
        matrix_cofactor(m, &cofactor);

        // Transposing the cofactor matrix to get the adjugate matrix
        Matrix adjugate;
        matrix_transpose(&cofactor, &adjugate);

        // Calculating the inverse by dividing the adjugate matrix by the determinant
        float inv_det = 1.0f / det; 
        // Dividing the adjugate matrix by the determinant to get the inverse
        for (int i = 0, length = MLENGTH * MLENGTH; i < length; i++)
        {
            result->m[i] = adjugate.m[i] * inv_det;
        }
    }    
}

//------------------------ Main Transformations ----------------------------

/**
 * Creates a translation matrix that translates by the given x, y, and z values, and stores the result in the provided result matrix.
 * The translation matrix is a 4x4 matrix that can be used to perform translations in 3D space. The matrix is constructed by setting the diagonal elements to 1, and the last column to the translation values (x, y, z) and 1 in the bottom-right corner.
 * @param x The translation value along the x-axis
 * @param y The translation value along the y-axis
 * @param z The translation value along the z-axis
 * @param result Pointer to the matrix where the translation matrix will be stored
 * Example:
 * Matrix result;
 * matrix_translate(1, 2, 3, &result);  result will be {1, 0, 0, 0,
 *                                 //              0, 1, 0, 0,
 *                                 //              0, 0, 1, 0,
 *                                 //              1, 2, 3, 1}
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix. The resulting translation matrix will have the translation values in the last column, and the rest of the matrix will be set to the identity matrix.
 */
void matrix_translate (float x, float y, float z, Matrix* result)
{
    matrix_identity(result);
    result->d.x = x;
    result->d.y = y;
    result->d.z = z;
}

/**
 * Creates a scaling matrix that scales by the given x, y, and z values, and stores the result in the provided result matrix.
 * The scaling matrix is a 4x4 matrix that can be used to perform scaling transformations in 3D space. The matrix is constructed by setting the diagonal elements to the scaling values (x, y, z) and 1 in the bottom-right corner, while the rest of the elements are set to 0.
 * @param x The scaling factor along the x-axis
 * @param y The scaling factor along the y-axis
 * @param z The scaling factor along the z-axis
 * @param result Pointer to the matrix where the scaling matrix will be stored
 * Example:
 * Matrix result;
 * matrix_scale(2, 3, 4, &result); // result will be {2, 0, 0, 0,
 *                                 //              0, 3, 0, 0,
 *                                 //              0, 0, 4, 0,
 *                                 //              0, 0, 0, 1}
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix. The resulting scaling matrix will have the scaling values on the diagonal and zeros elsewhere except for the bottom-right corner which will be set to 1.
 */
void matrix_scale (float x, float y, float z, Matrix* result)
{
    matrix_identity(result);
    result->a.x = x;
    result->b.y = y;
    result->c.z = z;
    result->d.w = 1.0f;
}   

/**
 * Creates a rotation matrix that rotates by the given angle (in radians) around the specified axis, and stores the result in the provided result matrix.
 * The rotation matrix is a 4x4 matrix that can be used to perform rotation transformations in 3D space. The matrix is constructed using the Rodrigues' rotation formula, which combines the identity matrix, the outer product of the axis vector, and the skew-symmetric matrix of the axis vector, scaled by the sine and cosine of the rotation angle. The input axis vector is normalized to ensure it has a length of 1, which is necessary for the rotation to be applied correctly.
 * @param axis The vector representing the axis of rotation (should be normalized)
 * @param angle_radians The angle of rotation in radians
 * @param result Pointer to the matrix where the rotation matrix will be stored
 * Example:
 * Vector axis = {0, 1, 0, 0}; // Rotate around the y-axis
 * Matrix result;
 * matrix_rotate(axis, M_PI / 2, &result); // result will be {0, 0, 1, 0,
 *                                 //              0, 1, 0, 0,
 *                                 //              -1, 0, 0, 0,
 *                                 //              0, 0, 0, 1}
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix and the axis is a 4D vector. The input axis vector should be normalized (i.e., it should have a length of 1) for the rotation to be applied correctly. If the axis vector is not normalized, the resulting rotation matrix may not represent the intended rotation. The resulting rotation matrix will be a 4x4 matrix that can be used to rotate points or other matrices in 3D space around the specified axis by the given angle.
 */
void matrix_rotate (Vector *axis, float angle_radians, Matrix* result)
{
    matrix_identity(result);
    float c = cosf(angle_radians);
    float s = sinf(angle_radians);
    float t = 1.0f - c;

    // Normalizing the rotation axis to ensure it has a length of 1, which is necessary for the rotation to be applied correctly. The normalization is done by dividing each component of the axis vector by its magnitude.
    vector_normalize(axis, axis);
    float x = axis->x, y = axis->y, z = axis->z;
    
    // Column 0 (a)
    result->a.x = t * x * x + c;
    result->a.y = t * x * y + s * z; // Note: +sz
    result->a.z = t * x * z - s * y; // Note: -sy

    // Column 1 (b)
    result->b.x = t * x * y - s * z; // Note: -sz
    result->b.y = t * y * y + c;
    result->b.z = t * y * z + s * x; // Note: +sx

    // Column 2 (c)
    result->c.x = t * x * z + s * y; // Note: +sy
    result->c.y = t * y * z - s * x; // Note: -sx
    result->c.z = t * z * z + c;
    
    result->d.w = 1.0f;
}

//------------------------ Camera and Viewing ----------------------------

/**
 * Creates a view matrix that represents a camera looking from the position specified by 'eye' towards the 'target' point, with the 'up' vector defining the upward direction of the camera, and stores the result in the provided result matrix.
 * The view matrix is a 4x4 matrix that can be used to transform world coordinates into camera (or view) coordinates. The function calculates the forward, right, and up vectors based on the input parameters, and then constructs the view matrix using these vectors. The forward vector is calculated as the normalized difference between the target and eye positions, the right vector is calculated as the cross product of the forward vector and the up vector, and the true up vector is calculated as the cross product of the right and forward vectors. The resulting view matrix is constructed in column-major order, with the right, up, and negative forward vectors forming the rotation part of the matrix, and the translation part is calculated to move the world by the negative of the camera position.
 * @param eye The position of the camera in world space
 * @param target The point in world space that the camera is looking at
 * @param up The up direction for the camera, which helps to define the orientation of the camera
 * @param result Pointer to the matrix where the view matrix will be stored
 * Example:
 * Vector eye = {0, 0, 5, 1}; // Camera position
 * Vector target = {0, 0, 0, 1}; // Point the camera is looking at
 * Vector up = {0, 1, 0, 0}; // Up direction
 * Matrix result;
 * matrix_look_at(&eye, &target, &up, &result); // result will be a view matrix that transforms world coordinates into camera coordinates based on the specified eye, target, and up vectors.
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix and the vectors are 4D. If the eye and target positions are the same, the function will print a warning message to the standard error stream and set the result to the identity matrix, as the view matrix would not be able to represent a valid camera transformation in that case. Additionally, if the forward vector (calculated as target - eye) is nearly zero, the function will also print a warning and set the result to the identity matrix, as this would indicate that the camera is looking in an undefined direction. If the right vector (calculated as the cross product of the forward vector and the up vector) is nearly zero, the function will attempt to use a fallback up vector to calculate the right vector, and if that also fails, it will print a warning and set the result to the identity matrix. The resulting view matrix will be a 4x4 matrix that can be used to transform world coordinates into camera coordinates, and it will be based on the specified eye, target, and up vectors.
 */
void matrix_look_at (const Vector *eye, const Vector *target, const Vector *up, Matrix* result)
{
    Vector f, r, u;
    
    // 1. Calculate Forward vector 
    // For Right-Handed (OpenGL), the camera looks down the NEGATIVE Z-axis.
    // Therefore: Forward = eye - target (points toward the camera)
    vector_sub(eye, target, &f); 
    
    float mag_f = vector_magnitude(&f);
    if (g_nearly_equal(mag_f, EPSILON))
    {
        fprintf(stderr, "Error: Eye and Target are coincidental.\n");
        matrix_identity(result);
        return;
    }
    vector_normalize(&f, &f); // Normalize

    // 2. Calculate Right vector (r = up x f)
    // We do this manually to ensure we stay in 3D space and avoid 4D cross-product overhead
    r.x = up->y * f.z - up->z * f.y;
    r.y = up->z * f.x - up->x * f.z;
    r.z = up->x * f.y - up->y * f.x;
    r.w = 0.0f;

    float mag_r = vector_magnitude(&r);
    if (g_nearly_equal(mag_r, EPSILON)) 
    {
        // Handle "Gimbal Lock": happens if looking straight up or down
        Vector fallback_up = {{0.0f, 0.0f, 1.0f, 0.0f}};
        if (fabsf(f.z) > 0.9f) { fallback_up.z = 0.0f; fallback_up.x = 1.0f; }
        
        // Recalculate Right with fallback
        r.x = fallback_up.y * f.z - fallback_up.z * f.y;
        r.y = fallback_up.z * f.x - fallback_up.x * f.z;
        r.z = fallback_up.x * f.y - fallback_up.y * f.x;
        mag_r = vector_magnitude(&r);
    }
    vector_normalize(&r, &r);

    // 3. Calculate True Up vector (u = f x r)
    u.x = f.y * r.z - f.z * r.y;
    u.y = f.z * r.x - f.x * r.z;
    u.z = f.x * r.y - f.y * r.x;
    u.w = 0.0f;

    // 4. Build the 4x4 View Matrix (Column-Major)
    matrix_identity(result);

    // Column 0
    result->m[0] = r.x;
    result->m[1] = u.x;
    result->m[2] = f.x;

    // Column 1
    result->m[4] = r.y;
    result->m[5] = u.y;
    result->m[6] = f.y;

    // Column 2
    result->m[8] = r.z;
    result->m[9] = u.z;
    result->m[10] = f.z;

    // Column 3 (Translation: -Dot products)
    // To move the camera to the origin, we rotate the world then translate by -Eye.
    result->m[12] = -vector_dot(&r, eye);
    result->m[13] = -vector_dot(&u, eye);
    result->m[14] = -vector_dot(&f, eye);
}

/**
 * Creates a perspective projection matrix based on the given field of view, aspect ratio, and near/far clipping planes, and stores the result in the provided result matrix.
 * The perspective projection matrix is a 4x4 matrix that can be used to perform perspective transformations in 3D space, which simulate the way objects appear smaller as they get further away from the viewer. The matrix is constructed using the field of view (FOV), aspect ratio, and near/far clipping planes to determine how the 3D scene is projected onto a 2D screen. The resulting matrix will have the perspective divide built into it, which means that after transforming a point by this matrix, you will need to perform a perspective divide (i.e., divide the x, y, and z components by the w component) to get the correct screen coordinates.
 * @param fov_deg The field of view in degrees (the vertical angle of the camera's view)
 * @param aspect The aspect ratio of the viewport (width / height)
 * @param near The distance to the near clipping plane
 * @param far The distance to the far clipping plane
 * @param result Pointer to the matrix where the result will be stored
 * Example:
 * Matrix result;
 * matrix_perspective(45.0f, 1.33f, 0.1f, 100.0f, &result); // result will be a perspective projection matrix based on the provided parameters
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix. The resulting perspective projection matrix will be a 4x4 matrix that can be used to transform points from world space to clip space in a perspective projection. After transforming a point by this matrix, you will need to perform a perspective divide (i.e., divide the x, y, and z components by the w component) to get the correct screen coordinates.
 */
void matrix_perspective (float fov_deg, float aspect, float near, float far, Matrix* result)
{
    matrix_set_to_zero(result); 
    
    float fov_rad = g_to_radians(fov_deg);
    float tanHalfFovy = tanf(fov_rad / 2.0f);

    result->m[0] = 1.0f / (aspect * tanHalfFovy); // Scale X
    result->m[5] = 1.0f / tanHalfFovy;            // Scale Y
    
    // Standard OpenGL Perspective mapping:
    // Maps the Z range [near, far] to [-1, 1]
    result->m[10] = -(far + near) / (far - near);
    result->m[11] = -1.0f; 
    result->m[14] = -(2.0f * far * near) / (far - near);
}

/**
 * Creates a perspective projection matrix with reversed Z (i.e., far plane maps to 0 and near plane maps to 1) based on the given field of view, aspect ratio, and near/far clipping planes, and stores the result in the provided result matrix.
 * The reversed Z perspective projection matrix is a 4x4 matrix that can be used to perform perspective transformations in 3D space with a reversed depth range, which can improve depth buffer precision and reduce z-fighting issues. The matrix is constructed using the field of view (FOV), aspect ratio, and near/far clipping planes to determine how the 3D scene is projected onto a 2D screen. The resulting matrix will have the perspective divide built into it, which means that after transforming a point by this matrix, you will need to perform a perspective divide (i.e., divide the x, y, and z components by the w component) to get the correct screen coordinates. In this reversed Z configuration, the depth values will be mapped such that the near plane corresponds to a depth of 1 and the far plane corresponds to a depth of 0, which can help improve depth buffer precision, especially for scenes with a large depth range.
 * @param fov_deg The field of view in degrees (the vertical angle of the camera's view)
 * @param aspect The aspect ratio of the viewport (width / height)
 * @param near The distance to the near clipping plane
 * @param far The distance to the far clipping plane
 * @param result Pointer to the matrix where the result will be stored
 * Example:
 * Matrix result;
 * matrix_perspective_reversed_z(45.0f, 1.33f, 0.1f, 100.0f, &result); // result will be a reversed Z perspective projection matrix based on the provided parameters
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix. The resulting reversed Z perspective projection matrix will be a 4x4 matrix that can be used to transform points from world space to clip space in a perspective projection with reversed Z. After transforming a point by this matrix, you will need to perform a perspective divide (i.e., divide the x, y, and z components by the w component) to get the correct screen coordinates. In this reversed Z configuration, the depth values will be mapped such that the near plane corresponds to a depth of 1 and the far plane corresponds to a depth of 0, which can help improve depth buffer precision, especially for scenes with a large depth range.
 */
void matrix_perspective_reversed_z(float fov_deg, float aspect, float near, float far, Matrix* result)
{
    matrix_set_to_zero(result); 
    
    float fov_rad = g_to_radians(fov_deg);
    float tanHalfFovy = tanf(fov_rad / 2.0f);

    result->m[0] = 1.0f / (aspect * tanHalfFovy); 
    result->m[5] = 1.0f / tanHalfFovy;          
    
    // Z-Mapping for Reverse-Z [near, far] -> [1, 0]
    // This formula works for a finite far plane.
    result->m[10] = near / (far - near);
    result->m[14] = (far * near) / (far - near);
    // The W-Divide
    result->m[11] = -1.0f;
}

/**
 * Creates a perspective projection matrix with reversed Z and an infinite far plane (i.e., far plane maps to 0 and near plane maps to 1) based on the given field of view, aspect ratio, and near clipping plane, and stores the result in the provided result matrix.
 * The reversed Z perspective projection matrix with an infinite far plane is a 4x4 matrix that can be used to perform perspective transformations in 3D space with a reversed depth range and an infinite far plane, which can further improve depth buffer precision and eliminate z-fighting issues for scenes with a very large depth range. The matrix is constructed using the field of view (FOV), aspect ratio, and near clipping plane to determine how the 3D scene is projected onto a 2D screen. The resulting matrix will have the perspective divide built into it, which means that after transforming a point by this matrix, you will need to perform a perspective divide (i.e., divide the x, y, and z components by the w component) to get the correct screen coordinates. In this configuration, the depth values will be mapped such that the near plane corresponds to a depth of 1 and the far plane (which is at infinity) corresponds to a depth of 0, which can help improve depth buffer precision and eliminate z-fighting issues for scenes with a very large depth range.
 * @param fov_deg The field of view in degrees (the vertical angle of the camera's view)
 * @param aspect The aspect ratio of the viewport (width / height)
 * @param near The distance to the near clipping plane
 * @param result Pointer to the matrix where the result will be stored
 * Example:
 * Matrix result;
 * matrix_perspective_infinite_reversed_z(45.0f, 1.33f, 0.1f, &result); // result will be a reversed Z perspective projection matrix with an infinite far plane based on the provided parameters
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix. The resulting reversed Z perspective projection matrix with an infinite far plane will be a 4x4 matrix that can be used to transform points from world space to clip space in a perspective projection with reversed Z and an infinite far plane. After transforming a point by this matrix, you will need to perform a perspective divide (i.e., divide the x, y, and z components by the w component) to get the correct screen coordinates. In this configuration, the depth values will be mapped such that the near plane corresponds to a depth of 1 and the far plane (which is at infinity) corresponds to a depth of 0, which can help improve depth buffer precision and eliminate z-fighting issues for scenes with a very large depth range.
 */
void matrix_perspective_infinite_reversed_z(float fov_deg, float aspect, float near, Matrix* result)
{
    matrix_set_to_zero(result); 
    
    float fov_rad = g_to_radians(fov_deg);
    float tanHalfFovy = tanf(fov_rad / 2.0f);
    
    result->m[0] = 1.0f / (aspect * tanHalfFovy);
    result->m[5] = 1.0f / tanHalfFovy;
    
    // In an infinite far-plane matrix, the far plane is pushed to infinity.
    result->m[10] = 0.0f; 
    result->m[14] = near;
    
    result->m[11] = -1.0f;
}

/**
 * Creates an orthographic projection matrix based on the given left, right, bottom, top, near, and far clipping planes, and stores the result in the provided result matrix.
 * The orthographic projection matrix is a 4x4 matrix that can be used to perform orthographic transformations in 3D space, which represent objects without perspective distortion (i.e., objects appear the same size regardless of their distance from the viewer). The matrix is constructed using the left, right, bottom, top, near, and far clipping planes to determine how the 3D scene is projected onto a 2D screen. The resulting matrix will map the specified cuboid defined by the clipping planes to the normalized device coordinates (NDC) space, where x and y are in the range [-1, 1] and z is in the range [-1, 1].
 * @param left The left clipping plane
 * @param right The right clipping plane
 * @param bottom The bottom clipping plane
 * @param top The top clipping plane
 * @param near The distance to the near clipping plane
 * @param far The distance to the far clipping plane
 * @param result Pointer to the matrix where the result will be stored
 * Example:
 * Matrix result;
 * matrix_ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f, &result); // result will be an orthographic projection matrix based on the provided parameters 
 * @warning This function does not check for the dimensions of the input parameters, it assumes the result is a 4x4 matrix. The resulting orthographic projection matrix will be a 4x4 matrix that can be used to transform points from world space to clip space in an orthographic projection. After transforming a point by this matrix, you will get the correct screen coordinates without needing to perform a perspective divide, as there is no perspective distortion in orthographic projections.
 */
void matrix_ortho(float left, float right, float bottom, float top, float near, float far, Matrix* result)
{
    if (g_nearly_equal(right, left) || g_nearly_equal(top, bottom) || g_nearly_equal(far, near)) {
        matrix_identity(result);
        return;
    }

    matrix_set_to_zero(result);

    // Diagonal - Scaling factors
    result->m[0]  = 2.0f / (right - left);
    result->m[5]  = 2.0f / (top - bottom);
    result->m[10] = -2.0f / (far - near);
    result->m[15] = 1.0f;

    // Last Column - Translation factors
    result->m[12] = -(right + left) / (right - left);
    result->m[13] = -(top + bottom) / (top - bottom);
    result->m[14] = -(far + near) / (far - near);
}

/**
 * Extracts the normal matrix from the given model matrix, and stores the result in the provided result matrix.
 * The normal matrix is a 3x3 matrix that is used to transform normal vectors correctly when non-uniform scaling is applied in the model matrix. It is calculated as the inverse transpose of the upper-left 3x3 portion of the model matrix. The function first extracts the upper-left 3x3 portion of the model matrix, then calculates its determinant to check if it is singular. If the determinant is close to zero, it means the matrix is singular and cannot be inverted, so the function will print a warning and set the normal matrix to the identity matrix. If the determinant is not singular, the function proceeds to calculate the inverse transpose of the 3x3 matrix directly into the result matrix, which can be used to transform normal vectors correctly in the presence of non-uniform scaling.
 * @param model Pointer to the model matrix from which the normal matrix will be extracted
 * @param result Pointer to the 3x3 matrix where the normal matrix will be stored
 * Example:
 * Matrix model; // Assume this is already set to the model matrix with potential non-uniform scaling
 * Matrix3x3 normal_matrix;
 * matrix_to_normal_matrix(&model, &normal_matrix); // normal_matrix will now contain the normal matrix extracted from the model matrix
 * @warning This function does not check for the dimensions of the input parameters, it assumes the model is a 4x4 matrix and the result is a 3x3 matrix. If the upper-left 3x3 portion of the model matrix is singular (i.e., it does not have an inverse), the function will print a warning message to the standard error stream and set the normal matrix to the identity matrix, which means that normal vectors will not be transformed correctly under non-uniform scaling, but it will prevent potential issues with rendering due to the singular matrix. The resulting normal matrix will be a 3x3 matrix that can be used to transform normal vectors correctly when non-uniform scaling is applied in the model matrix.
 */
void matrix_to_normal_matrix(const Matrix *model, Matrix3x3 *result)
{
    // Only care about the upper-left 3x3 of the model matrix.
    Matrix3x3 mat3 = {0};
    mat3.a.x = model->m[0]; mat3.a.y = model->m[1]; mat3.a.z = model->m[2];
    mat3.b.x = model->m[4]; mat3.b.y = model->m[5]; mat3.b.z = model->m[6];
    mat3.c.x = model->m[8]; mat3.c.y = model->m[9]; mat3.c.z = model->m[10];

    // Calculate the determinant of the 3x3 part
    float det = matrix3x3_determinant(&mat3);

    if (g_nearly_equal(det, EPSILON) == 1)
    {
        fprintf(stderr, "Warning: The upper-left 3x3 part of the model matrix is singular. The normal matrix will be set to the identity matrix.\n");
        matrix_identity3x3(result);
        return;
    }

    // Compute the Inverse-Transpose directly into the result.
    float inv_det = 1.0f / det;

    // Row 0
    result->a.x = (mat3.b.y * mat3.c.z - mat3.b.z * mat3.c.y) * inv_det;
    result->a.y = (mat3.b.z * mat3.c.x - mat3.b.x * mat3.c.z) * inv_det;
    result->a.z = (mat3.b.x * mat3.c.y - mat3.b.y * mat3.c.x) * inv_det;

    // Row 1
    result->b.x = (mat3.a.z * mat3.c.y - mat3.a.y * mat3.c.z) * inv_det;
    result->b.y = (mat3.a.x * mat3.c.z - mat3.a.z * mat3.c.x) * inv_det;
    result->b.z = (mat3.a.y * mat3.c.x - mat3.a.x * mat3.c.y) * inv_det;

    // Row 2
    result->c.x = (mat3.a.y * mat3.b.z - mat3.a.z * mat3.b.y) * inv_det;
    result->c.y = (mat3.a.z * mat3.b.x - mat3.a.x * mat3.b.z) * inv_det;
    result->c.z = (mat3.a.x * mat3.b.y - mat3.a.y * mat3.b.x) * inv_det;
}

/**
 * Extracts the six planes of the view frustum from the given combined view-projection matrix, and stores the result in the provided planes array.
 * The function calculates the coefficients of the six planes (left, right, bottom, top, near, far) by combining the columns of the view-projection matrix in specific ways. Each plane is represented as a 4D vector (x, y, z, w), where (x, y, z) is the normal vector of the plane and w is the distance from the origin to the plane along the normal. After extracting the planes, the function normalizes each plane equation to ensure that the normal vector has a length of 1, which is important for accurate distance calculations and intersection tests with the planes.
 * @param view_proj Pointer to the combined view-projection matrix from which the frustum planes will be extracted
 * @param planes An array of 6 vectors where the extracted frustum planes will be stored (planes[0] = left, planes[1] = right, planes[2] = bottom, planes[3] = top, planes[4] = near, planes[5] = far)
 * Example:
 * Matrix view_proj; // Assume this is already set to the combined view-projection matrix
 * Vector planes[6];
 * matrix_extract_frustum(&view_proj, planes); // planes will now contain the six frustum planes extracted from the view-projection matrix
 * @warning This function does not check for the dimensions of the input parameters, it assumes the view_proj is a 4x4 matrix and planes is an array of 6 vectors. The resulting planes will be normalized, meaning that the normal vector of each plane will have a length of 1, which is important for accurate distance calculations and intersection tests with the planes.
 */
void matrix_extract_frustum(const Matrix *view_proj, Vector planes[6])
{
    const float *m = view_proj->m;

    // Left Plane: Column 3 + Column 0
    planes[0].x = m[12] + m[0];
    planes[0].y = m[13] + m[1];
    planes[0].z = m[14] + m[2];
    planes[0].w = m[15] + m[3];

    // Right Plane: Column 3 - Column 0
    planes[1].x = m[12] - m[0];
    planes[1].y = m[13] - m[1];
    planes[1].z = m[14] - m[2];
    planes[1].w = m[15] - m[3];

    // Bottom Plane: Column 3 + Column 1
    planes[2].x = m[12] + m[4];
    planes[2].y = m[13] + m[5];
    planes[2].z = m[14] + m[6];
    planes[2].w = m[15] + m[7];

    // Top Plane: Column 3 - Column 1
    planes[3].x = m[12] - m[4];
    planes[3].y = m[13] - m[5];
    planes[3].z = m[14] - m[6];
    planes[3].w = m[15] - m[7];

    // Near Plane: Column 3 + Column 2
    planes[4].x = m[12] + m[8];
    planes[4].y = m[13] + m[9];
    planes[4].z = m[14] + m[10];
    planes[4].w = m[15] + m[11];

    // Far Plane: Column 3 - Column 2
    planes[5].x = m[12] - m[8];
    planes[5].y = m[13] - m[9];
    planes[5].z = m[14] - m[10];
    planes[5].w = m[15] - m[11];

    for (int i = 0; i < 6; i++)
    {
        vector_normalize(&planes[i], &planes[i]);
    }
}

/**
 * Extracts the six planes of the view frustum from the given combined view-projection matrix that uses reversed Z (i.e., near plane maps to Z=W and far plane maps to Z=0), and stores the result in the provided planes array.
 * The function calculates the coefficients of the six planes (left, right, bottom, top, near, far) by combining the columns of the view-projection matrix in specific ways that account for the reversed Z configuration. Each plane is represented as a 4D vector (x, y, z, w), where (x, y, z) is the normal vector of the plane and w is the distance from the origin to the plane along the normal. After extracting the planes, the function normalizes each plane equation to ensure that the normal vector has a length of 1, which is important for accurate distance calculations and intersection tests with the planes.  
 * In the reversed Z configuration, the near plane is represented by Column 2 of the view-projection matrix (since it maps to Z=W), and the far plane is represented by Column 3 minus Column 2 (since it maps to Z=0). The left, right, bottom, and top planes are extracted in the same way as in the standard configuration, using combinations of Column 3 with Columns 0 and 1.
 * @param view_proj Pointer to the combined view-projection matrix with reversed Z from which the frustum planes will be extracted
 * @param planes An array of 6 vectors where the extracted frustum planes will be stored (planes[0] = left, planes[1] = right, planes[2] = bottom, planes[3] = top, planes[4] = near, planes[5] = far)
 * Example:
 * Matrix view_proj; // Assume this is already set to the combined view-projection matrix with reversed Z
 * Vector planes[6];
 * matrix_extract_frustum_rev_z(&view_proj, planes); // planes will now contain the six frustum planes extracted from the view-projection matrix with reversed Z
 * @warning This function does not check for the dimensions of the input parameters, it assumes the view_proj is a 4x4 matrix and planes is an array of 6 vectors. The resulting planes will be normalized, meaning that the normal vector of each plane will have a length of 1, which is important for accurate distance calculations and intersection tests with the planes. In the reversed Z configuration, the near plane is represented by Column 2 of the view-projection matrix (since it maps to Z=W), and the far plane is represented by Column 3 minus Column 2 (since it maps to Z=0). The left, right, bottom, and top planes are extracted in the same way as in the standard configuration, using combinations of Column 3 with Columns 0 and 1.
 */
void matrix_extract_frustum_rev_z(const Matrix *view_proj, Vector planes[6])
{
    const float *m = view_proj->m;

    // Left, Right, Bottom, Top remain the SAME as the standard version
    // Left: Col 3 + Col 0
    planes[0].x = m[12] + m[0]; planes[0].y = m[13] + m[1]; 
    planes[0].z = m[14] + m[2]; planes[0].w = m[15] + m[3];

    // Right: Col 3 - Col 0
    planes[1].x = m[12] - m[0]; planes[1].y = m[13] - m[1]; 
    planes[1].z = m[14] - m[2]; planes[1].w = m[15] - m[3];

    // Bottom: Col 3 + Col 1
    planes[2].x = m[12] + m[4]; planes[2].y = m[13] + m[5]; 
    planes[2].z = m[14] + m[6]; planes[2].w = m[15] + m[7];

    // Top: Col 3 - Col 1
    planes[3].x = m[12] - m[4]; planes[3].y = m[13] - m[5]; 
    planes[3].z = m[14] - m[6]; planes[3].w = m[15] - m[7];

    // --- REVERSE-Z SPECIFIC CHANGES ---

    // Near Plane: mapping to 1.0 (z=w)
    planes[4].x = m[12] - m[8];
    planes[4].y = m[13] - m[9];
    planes[4].z = m[14] - m[10];
    planes[4].w = m[15] - m[11];

    // Far Plane: mapping to 0.0 (z=0)
    planes[5].x = m[8];
    planes[5].y = m[9];
    planes[5].z = m[10];
    planes[5].w = m[11];

    // Normalize all 6 planes
    for (int i = 0; i < 6; i++)
    {
        vector_normalize(&planes[i], &planes[i]);
    }
}

//------------------------ Helpers ----------------------------

/**
 * Compares two 4x4 matrices a and b, and returns 1 if they are equal (i.e., all their components are the same), or 0 otherwise.
 * The function checks each component of the matrices for equality, and returns 1 only if all components are equal. If any component is different, it returns 0.
 * @param a Pointer to the first matrix
 * @param b Pointer to the second matrix
 * @return 1 if the matrices are equal, 0 otherwise
 * Example:
 * Matrix a = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             1, 2, 3, 1};
 * Matrix b = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             1, 2, 3, 1};
 * int result = matrix_compare(&a, &b); // result will be 1, as the matrices are equal
 * Matrix c = {1, 0, 0, 0,
 *             0, 1, 0, 0,
 *             0, 0, 1, 0,
 *             -1, -2, -3, -1};
 * result = matrix_compare(&a, &c); // result will be 0, as the matrices are not equal (the last row is different)
 * @warning This function does not check for the dimensions of the input matrices, it assumes they are both 4x4 matrices.
 */
int matrix_compare (const Matrix *a, const Matrix *b)
{
    for (int i = 0; i < MLENGTH; i++)
    {
        for (int j = 0; j < MLENGTH; j++)
        {
            if (vector_compare((Vector*)&a->m[j*4], (Vector*)&b->m[j*4]) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Converts a 4x4 matrix to a 3x3 matrix by removing the specified row and the column corresponding to the input vector.
 * The function iterates through the elements of the input matrix and copies them to the result matrix, skipping the specified row and the column corresponding to the input vector. The resulting 3x3 matrix is stored in the provided result parameter.
 * @param row_to_remove The index of the row to be removed (0-based index)
 * @param column_to_remove The index of the column to be removed (0-based index)
 * @param m Pointer to the input 4x4 matrix
 * @param result Pointer to the matrix where the resulting 3x3 matrix will be stored
 * Example:
 * Matrix m = {1, 2, 3, 4,
 *             5, 6, 7, 8,
 *             9, 10, 11, 12,
 *             13, 14, 15, 16};
 * Vector v = {0, 1, 0, 0}; // Corresponds to the second column of the matrix
 * Matrix3x3 result;
 * matrix_convert(1, 1, &m, &result); // result will be {1, 3, 4,
 *                                 //                     5, 7, 8,
 *                                 //                     9, 11, 12}
 * @warning This function does not check for the dimensions of the input matrix and vector, it assumes the input matrix is 4x4 and the vector is 4D. The row parameter should be a valid index (0, 1, 2, or 3) corresponding to the row to be removed, and the vector should correspond to one of the columns of the input matrix. If the row index is out of bounds or if the vector does not correspond to a valid column, the behavior of the function is undefined. The resulting 3x3 matrix will contain the elements of the input matrix with the specified row and column removed.   
 */
void matrix_convert (int row_to_remove, int column_to_remove, const Matrix *input, Matrix3x3 *result)
{
    int current_col = 0;
    for (int i = 0; i <MLENGTH; i++)
    {
        // If the current column of the matrix is the same as the input vector, skip it
        if (i == column_to_remove) continue;

        int current_row = 0;
        for (int j = 0; j < MLENGTH; j++)
        {
            // If the current row of the matrix is the same as given, skip it
            if (j == row_to_remove) continue; 

            result->m[current_col*3 + current_row] = input->m[i*4 + j];
            current_row++;
        }
        current_col++;
    }
}

/**
 * Converts a 3x3 matrix to a 4x4 matrix by placing the elements of the 3x3 matrix in the upper-left corner of the 4x4 matrix, and filling the rest of the elements with appropriate values to maintain the properties of a transformation matrix.
 * The function iterates through the elements of the input 3x3 matrix and copies them to the corresponding positions in the result 4x4 matrix. The resulting 4x4 matrix is stored in the provided result parameter, with the upper-left 3x3 portion containing the values from the input matrix, and the rest of the elements set to form a valid transformation matrix (i.e., the last row is set to [0, 0, 0, 1]).
 * @param m Pointer to the input 3x3 matrix
 * @param result Pointer to the matrix where the resulting 4x4 matrix will be stored
 * Example:
 * Matrix3x3 m = {1, 2, 3,
 *                4, 5, 6,
 *                7, 8, 9};
 * Matrix result;
 * matrix3x3_convert(&m, &result); // result will be {1, 2, 3, 0,
 *                                 //              4, 5, 6, 0,
 *                                 //              7, 8, 9, 0,
 *                                 //              0, 0, 0, 1}
 * @warning This function does not check for the dimensions of the input matrix, it assumes it is a 3x3 matrix. The resulting 4x4 matrix will have the upper-left 3x3 portion filled with the values from the input matrix, and the rest of the elements will be set to form a valid transformation matrix (i.e., the last row will be set to [0, 0, 0, 1]).
 */
void matrix3x3_convert (const Matrix3x3 *m, Matrix *result)
{
    matrix_identity(result); // Set default identity (0s and 1 at m[15])
    result->m[0] = m->m[0]; result->m[1] = m->m[1]; result->m[2] = m->m[2]; // Col 0
    result->m[4] = m->m[3]; result->m[5] = m->m[4]; result->m[6] = m->m[5]; // Col 1
    result->m[8] = m->m[6]; result->m[9] = m->m[7]; result->m[10] = m->m[8];// Col 2
}


/**
 * Calculates the cofactor matrix of a 4x4 matrix m, and stores the result in the provided result matrix.
 * The cofactor matrix is calculated by iterating over each element of the input matrix, calculating the corresponding 3x3 minor matrix for each element, and then applying the appropriate sign based on the position of the element in the original matrix. The resulting cofactor matrix is stored in the provided result parameter.
 * @param m Pointer to the input 4x4 matrix
 * @param result Pointer to the matrix where the cofactor matrix will be stored
 * Example:
 * Matrix m = {1, 2, 3, 4,
 *             5, 6, 7, 8,
 *             9, 10, 11, 12,
 *             13, 14, 15, 16};
 * Matrix result;
 * matrix_cofactor(&m, &result); // result will be { -24,  48, -24, 0,
 *                                                   48, -96, 48, 0,
 *                                                  -24, 48, -24, 0,
 *                                                      0, 0, 0, 0}
 * @warning This function does not check for the dimensions of the input matrix, it assumes it is a 4x4 matrix. The resulting cofactor matrix will also be a 4x4 matrix.
 */
void matrix_cofactor(const Matrix *m, Matrix *result)
{
    Matrix3x3 minor;
    for (int i = 0; i < MLENGTH; i++)
    {
        for (int j = 0; j < MLENGTH; j++)
        {
            matrix_convert(i, j, m, &minor);
            float minor_det = matrix3x3_determinant(&minor);
            float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
            result->m[i + j * MLENGTH] = sign * minor_det;
        }
    }
}

/**
 * Sets all elements of the given matrix to zero.
 * The function iterates through all the elements of the input matrix and assigns a value of 0.0f to each element, effectively setting the entire matrix to zero.
 * @param m Pointer to the matrix to be set to zero
 * Example:
 * Matrix m = {1, 2, 3, 4,
 *            5, 6, 7, 8,
 *           9, 10, 11, 12,
 *          13, 14, 15, 16};
 * matrix_set_2_zero(&m); // m will be {0, 0, 0, 0,
 *                         //              0, 0, 0, 0,
 *                         //              0, 0, 0, 0,
 *                         //              0, 0, 0, 0}
 * @warning This function does not check for the dimensions of the input matrix, it assumes it
 */
void matrix_set_to_zero (Matrix *m)
{
    for (int i = 0; i < MLENGTH * MLENGTH; i++)
    {
        m->m[i] = 0.0f;
    }
}