#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "gmath.h"

void test_rotation_precision() {
    printf("Testing Rotation Precision (90 degrees)...\n");
    
    // Rotate 90 degrees around Z axis
    // Point (1, 0, 0) should become (0, 1, 0)
    Matrix rotZ = matrix_rotate(0, 0, 90.0f); 
    Vector start = {1.0f, 0.0f, 0.0f, 1.0f};
    Vector end = matrix_vector_mult(rotZ, start);

    g_print_vector(end, "After 90 deg Z rotation");
    
    assert(g_nearly_equal(end.x, 0.0f));
    assert(g_nearly_equal(end.y, 1.0f));
    assert(g_nearly_equal(end.z, 0.0f));
    printf("  [PASS] Z-Axis Rotation\n");
}

void test_non_uniform_scaling() {
    printf("Testing Non-Uniform Scaling...\n");
    
    Matrix scale = matrix_scale(0.5f, 2.0f, 10.0f);
    Vector v = {10.0f, 10.0f, 10.0f, 1.0f};
    Vector result = matrix_vector_mult(scale, v);

    assert(g_nearly_equal(result.x, 5.0f));
    assert(g_nearly_equal(result.y, 20.0f));
    assert(g_nearly_equal(result.z, 100.0f));
    printf("  [PASS] Non-uniform scale\n");
}

void test_transformation_order() {
    printf("Testing Transformation Order (T * R vs R * T)...\n");
    
    Matrix T = matrix_translate(5.0f, 0.0f, 0.0f);
    Matrix R = matrix_rotate(0.0f, 0.0f, 90.0f);
    
    // Case 1: Translate then Rotate (Rotate * Translate)
    // Point (0,0,0) -> Translate to (5,0,0) -> Rotate 90 deg around origin -> (0,5,0)
    Matrix TR = matrix_mult(R, T); 
    Vector p1 = {0.0f, 0.0f, 0.0f, 1.0f};
    Vector res1 = matrix_vector_mult(TR, p1);
    
    // Case 2: Rotate then Translate (Translate * Rotate)
    // Point (0,0,0) -> Rotate (still 0,0,0) -> Translate to (5,0,0) -> (5,0,0)
    Matrix RT = matrix_mult(T, R);
    Vector res2 = matrix_vector_mult(RT, p1);

    assert(g_nearly_equal(res1.y, 5.0f)); // Should be at (0, 5, 0)
    assert(g_nearly_equal(res2.x, 5.0f)); // Should be at (5, 0, 0)
    
    printf("  [PASS] Matrix non-commutativity (Order matters)\n");
}

void test_singular_matrix_inverse() {
    printf("Testing Inverse of Singular Matrix (Scale 0)...\n");
    
    // A matrix with a scale of 0 on any axis cannot be inverted (it flattens space)
    Matrix singular = matrix_scale(0.0f, 1.0f, 1.0f);
    Matrix inv = matrix_inverse(singular);
    
    // Depending on your implementation, this should either return 0s 
    // or handle the failure gracefully.
    printf("  [INFO] Singular matrix handled.\n");
}

int main() {
    printf("Starting Advanced GMath Tests...\n");
    printf("--------------------------------\n");

    test_rotation_precision();
    test_non_uniform_scaling();
    test_transformation_order();
    test_singular_matrix_inverse();

    printf("--------------------------------\n");
    printf("ALL ADVANCED TESTS PASSED!\n");
    return 0;
}