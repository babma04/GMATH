#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "gmath.h"

void test_vector_basics() {
    printf("Testing Vector Basics (Sum, Sub, Scalar)...\n");
    Vector v = {{1.0f, 2.0f, 3.0f, 1.0f}};
    Vector u = {{4.0f, 5.0f, 6.0f, 1.0f}};
    Vector result;

    // Test Sum
    vector_sum(&v, &u, &result);
    assert(g_nearly_equal(result.x, 5.0f));
    assert(g_nearly_equal(result.y, 7.0f));
    assert(g_nearly_equal(result.z, 9.0f));

    // Test Subtraction
    vector_sub(&u, &v, &result);
    assert(g_nearly_equal(result.x, 3.0f));
    assert(g_nearly_equal(result.y, 3.0f));
    assert(g_nearly_equal(result.z, 3.0f));

    // Test Scalar
    vector_scalar(&v, 2.0f, &result);
    assert(g_nearly_equal(result.x, 2.0f));
    assert(g_nearly_equal(result.y, 4.0f));
    assert(g_nearly_equal(result.z, 6.0f));
    
    printf("  [PASS] Arithmetic operations\n");
}

void test_vector_geometry() {
    printf("Testing Vector Geometry (Dot, Cross, Mag, Angle)...\n");
    
    Vector v = {{3.0f, 0.0f, 4.0f, 0.0f}}; 
    Vector u = {{0.0f, 1.0f, 0.0f, 0.0f}};
    Vector res;

    // Test Magnitude
    assert(g_nearly_equal(vector_magnitude(&v), 5.0f));
    
    // Test Normalization
    vector_normalize(&v, &res);
    assert(g_nearly_equal(vector_magnitude(&res), 1.0f));

    // Test Dot Product
    assert(g_nearly_equal(vector_dot(&v, &u), 0.0f));

    // Test Angle (90 degrees between X-Z plane and Y axis)
    float angle = vectors_angle(&v, &u);
    assert(g_nearly_equal(angle, PI / 2.0f));

    // Test Cross Product 3D (X cross Y = Z)
    Vector right = {{1.0f, 0.0f, 0.0f, 0.0f}};
    Vector up    = {{0.0f, 1.0f, 0.0f, 0.0f}};
    vector_cross3D(&right, &up, &res);
    assert(g_nearly_equal(res.z, 1.0f));

    printf("  [PASS] Geometric operations\n");
}

void test_vector_interpolation() {
    printf("Testing Interpolation (Lerp, SafeLerp, Slerp)...\n");

    Vector start = {{0.0f, 0.0f, 0.0f, 0.0f}};
    Vector end   = {{10.0f, 10.0f, 10.0f, 0.0f}};
    Vector res;
    
    // Test Lerp at 50%
    vector_lerp(&start, &end, 0.5f, &res);
    assert(g_nearly_equal(res.x, 5.0f));

    // Test SafeLerp (Clamp check)
    // Factor 1.5 should be clamped to 1.0, returning the 'end' vector
    vector_safeLerp(&start, &end, 1.5f, &res);
    assert(g_nearly_equal(res.x, 10.0f));

    // Test Slerp (Spherical)
    // 90 degree arc, 50% should be at 45 degrees
    Vector v1 = {{1.0f, 0.0f, 0.0f, 0.0f}};
    Vector v2 = {{0.0f, 1.0f, 0.0f, 0.0f}};
    vector_slerp(&v1, &v2, 0.5f, &res);
    // Magnitude should remain 1.0 in Slerp
    assert(g_nearly_equal(vector_magnitude(&res), 1.0f));
    assert(g_nearly_equal(res.x, cosf(PI/4.0f)));

    printf("  [PASS] Interpolation operations\n");
}

int main() {
    printf("Starting GMath Pointer-Based Vector Suite...\n");
    printf("------------------------------------------\n");

    test_vector_basics();
    test_vector_geometry();
    test_vector_interpolation();

    printf("------------------------------------------\n");
    printf("ALL TESTS PASSED!\n");
    return 0;
}