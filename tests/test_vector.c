#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "gmath.h"

void test_vector_basics() {
    printf("Testing Vector Basics (Sum, Sub, Scalar)...\n");
    Vector v = {1.0f, 2.0f, 3.0f, 1.0f};
    Vector u = {4.0f, 5.0f, 6.0f, 1.0f};

    // Test Sum
    Vector sum = vector_sum(v, u);
    assert(g_nearly_equal(sum.x, 5.0f));
    assert(g_nearly_equal(sum.y, 7.0f));
    assert(g_nearly_equal(sum.z, 9.0f));

    // Test Subtraction
    Vector diff = vector_sub(u, v);
    assert(g_nearly_equal(diff.x, 3.0f));
    assert(g_nearly_equal(diff.y, 3.0f));
    assert(g_nearly_equal(diff.z, 3.0f));

    // Test Scalar
    Vector scaled = vecto_scalar(v, 2.0f);
    assert(g_nearly_equal(scaled.x, 2.0f));
    assert(g_nearly_equal(scaled.y, 4.0f));
    assert(g_nearly_equal(scaled.z, 6.0f));
    
    printf("  [PASS] Arithmetic operations\n");
}

void test_vector_geometry() {
    printf("Testing Vector Geometry (Dot, Cross, Mag)...\n");
    
    // 3-4-5 Triangle test for Magnitude
    Vector v = {3.0f, 0.0f, 4.0f, 0.0f}; 
    assert(g_nearly_equal(vector_magnitude(v), 5.0f));
    
    // Test Normalization
    Vector norm = vector_normalize(v);
    assert(g_nearly_equal(vector_magnitude(norm), 1.0f));
    assert(g_nearly_equal(norm.x, 0.6f)); // 3/5

    // Test Dot Product (Perpendicular vectors should be 0)
    Vector right = {1.0f, 0.0f, 0.0f, 0.0f};
    Vector up    = {0.0f, 1.0f, 0.0f, 0.0f};
    assert(g_nearly_equal(vector_dot(right, up), 0.0f));

    // Test Cross Product (Right x Up = Forward)
    // In a right-handed system, X cross Y = Z
    Vector forward = vector_cross(right, up);
    assert(g_nearly_equal(forward.x, 0.0f));
    assert(g_nearly_equal(forward.y, 0.0f));
    assert(g_nearly_equal(forward.z, 1.0f));

    printf("  [PASS] Geometric operations\n");
}

void test_vector_advanced() {
    printf("Testing Advanced Vector Logic (Lerp, Zero Cases)...\n");

    // Test Linear Interpolation (Lerp)
    Vector start = {0.0f, 0.0f, 0.0f, 0.0f};
    Vector end   = {10.0f, 10.0f, 10.0f, 0.0f};
    
    // 50% between start and end
    Vector mid = vector_lerp(start, end, 0.5f);
    assert(g_nearly_equal(mid.x, 5.0f));
    assert(g_nearly_equal(mid.y, 5.0f));
    assert(g_nearly_equal(mid.z, 5.0f));

    // Edge Case: Normalizing a Zero Vector
    // Your implementation should handle this without crashing (returning 0,0,0)
    Vector zero = {0.0f, 0.0f, 0.0f, 0.0f};
    Vector norm_zero = vector_normalize(zero);
    assert(g_nearly_equal(norm_zero.x, 0.0f));

    printf("  [PASS] Advanced logic and edge cases\n");
}

int main() {
    printf("Starting GMath Vector Suite...\n");
    printf("--------------------------------\n");

    test_vector_basics();
    test_vector_geometry();
    test_vector_advanced();

    printf("--------------------------------\n");
    printf("ALL VECTOR TESTS PASSED!\n");
    return 0;
}