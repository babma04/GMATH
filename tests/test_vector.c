#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "../include/vector.h"


void test_basic_math() {
    printf("Testing Basic Arithmetic...\n");
    Vector v1 = {{1.0f, 2.0f, 3.0f, 4.0f}};
    Vector v2 = {{5.0f, 6.0f, 7.0f, 8.0f}};
    Vector res;

    vector_sum(&v1, &v2, &res);
    assert(g_nearly_equal(res.x, 6.0f) && g_nearly_equal(res.y, 8.0f) && g_nearly_equal(res.z, 10.0f) && g_nearly_equal(res.w, 12.0f));

    vector_sub(&v2, &v1, &res);
    assert(g_nearly_equal(res.x, 4.0f) && g_nearly_equal(res.y, 4.0f) && g_nearly_equal(res.z, 4.0f) && g_nearly_equal(res.w, 4.0f));

    vector_scalar(&v1, 0.5f, &res);
    assert(g_nearly_equal(res.x, 0.5f) && g_nearly_equal(res.z, 1.5f));
}

void test_geometry_ops() {
    printf("Testing Geometry (Dot/Cross/Mag)...\n");
    Vector i = {{1.0f, 0.0f, 0.0f, 0.0f}};
    Vector j = {{0.0f, 1.0f, 0.0f, 0.0f}};
    Vector k_res;

    // Dot product of orthogonal vectors should be 0
    assert(g_nearly_equal(vector_dot(&i, &j), 0.0f));

    // Cross product: i x j = k (0,0,1)
    vector_cross3D(&i, &j, &k_res);
    assert(g_nearly_equal(k_res.z, 1.0f) && g_nearly_equal(k_res.x, 0.0f) && g_nearly_equal(k_res.y, 0.0f));

    // Magnitude of (3,4,0,0) should be 5
    Vector mag_test = {{3.0f, 4.0f, 0.0f, 0.0f}};
    assert(g_nearly_equal(vector_magnitude(&mag_test), 5.0f));
}

void test_normalization() {
    printf("Testing Normalization (including Zero Vector)...\n");
    Vector v = {10.0f, 0.0f, 0.0f, 0.0f};
    Vector res;

    vector_normalize(&v, &res);
    assert(g_nearly_equal(res.x, 1.0f));

    Vector zero = {{0.0f, 0.0f, 0.0f, 0.0f}};
    vector_normalize(&zero, &res);
    assert(g_nearly_equal(res.x, 0.0f) && g_nearly_equal(res.y, 0.0f) && g_nearly_equal(res.z, 0.0f) && g_nearly_equal(res.w, 0.0f));
}

void test_interpolation() {
    printf("Testing Interpolation (LERP/SLERP)...\n");
    Vector start = {{1.0f, 0.0f, 0.0f, 0.0f}};
    Vector end = {{0.0f, 1.0f, 0.0f, 0.0f}};
    Vector res;

    // LERP 50%
    vector_lerp(&start, &end, 0.5f, &res);
    assert(g_nearly_equal(res.x, 0.5f) && g_nearly_equal(res.y, 0.5f));

    // SLERP 50% (should be at 45 deg on the arc)
    vector_slerp(&start, &end, 0.5f, &res);
    // 0.7071 is cos(45)
    assert(g_nearly_equal(res.x, 0.7071f)); 
    assert(g_nearly_equal(res.y, 0.7071f));
    // Check that SLERP preserved magnitude (LERP would be 0.707 total, not 1.0)
    assert(g_nearly_equal(vector_magnitude(&res), 1.0f));
}

void assert_is_unit(const Vector *v, const char* msg) {
    float mag = vector_magnitude(v);
    if (!g_nearly_equal(mag, 1.0f)) {
        fprintf(stderr, "FAIL: %s (Mag: %f)\n", msg, mag);
        assert(0);
    }
}

void test_slerp_specifics() {
    printf("Testing SLERP Edge Cases...\n");
    Vector v1 = {{1.0f, 0.0f, 0.0f, 0.0f}};
    Vector v2 = {{0.9999f, 0.0141f, 0.0f, 0.0f}}; // ~0.8 degrees apart
    Vector res;

    // Test 1: Very small angle (Should not produce NaN or crash)
    vector_slerp(&v1, &v2, 0.5f, &res);
    assert(!isnan(res.x) && "SLERP produced NaN on small angle!");
    
    // Test 2: Exact 180 degree flip (The "Undefined" case)
    // Note: Standard SLERP is undefined for 180 deg. 
    // Your code uses Angle == 0 check, but watch for 180!
    Vector v3 = {{-1.0f, 0.0f, 0.0f, 0.0f}};
    vector_slerp(&v1, &v3, 0.5f, &res);
    printf("  180-deg SLERP result: [%.2f, %.2f]\n", res.x, res.y);

    printf("✓ SLERP Edge Cases Passed\n");
}

void test_normalization_stability() {
    printf("Testing Normalization Precision...\n");
    
    // Test 3: Very small magnitude (Sub-epsilon)
    Vector tiny = {{1e-20f, 1e-20f, 1e-20f, 0.0f}};
    Vector res;
    vector_normalize(&tiny, &res);
    // Should be zero vector per your logic
    assert(g_nearly_equal(res.x, 0.0f) && "Small mag normalization failed to zero out!");

    // Test 4: Very large magnitude
    Vector huge = {{1e20f, 0.0f, 0.0f, 0.0f}};
    vector_normalize(&huge, &res);
    assert(g_nearly_equal(res.x, 1.0f) && "Huge mag normalization precision loss!");

    printf("✓ Normalization Stability Passed\n");
}

void test_orthogonality_and_cross() {
    printf("Testing 3D Orthogonality...\n");
    
    // Test 5: Cross product property (A x B is perp to both A and B)
    Vector a = {{1.2f, -3.4f, 5.6f, 0.0f}};
    Vector b = {{0.1f, 9.8f, -2.3f, 0.0f}};
    Vector cp;
    vector_cross3D(&a, &b, &cp);

    float dot_a = vector_dot(&a, &cp);
    float dot_b = vector_dot(&b, &cp);

    // Dot product of perpendicular vectors must be 0
    assert(g_nearly_equal(dot_a, EPSILON) && "Cross product not perp to A!");
    assert(g_nearly_equal(dot_b, EPSILON) && "Cross product not perp to B!");

    printf("✓ Orthogonality Passed\n");
}

void test_aliasing() {
    printf("Testing Pointer Aliasing (v == result)...\n");
    
    // Test 6: In-place Sum
    Vector v = {{1.0f, 1.0f, 1.0f, 1.0f}};
    vector_sum(&v, &v, &v); 
    assert(g_nearly_equal(v.x, 2.0f) && "In-place sum failed!");

    // Test 7: In-place Normalization
    // If you use the mag as you go, the second coordinate might be wrong
    Vector n = {{2.0f, 2.0f, 0.0f, 0.0f}};
    vector_normalize(&n, &n);
    assert_is_unit(&n, "In-place normalization failed!");

    printf("✓ Aliasing Safety Passed\n");
}

void test_fpu_precision() {
    printf("Testing FPU Suffixes...\n");
    Vector v = {{1.0f, 1.0f, 1.0f, 1.0f}};
    float mag = vector_magnitude(&v); // Should be 2.0
    assert(g_nearly_equal(mag, 2.0f));
    
    // Testing the 1.0/sqrt(mag_sq) trick in your vector3_normalize
    Vector3 v3 = {{1.0f, 1.0f, 1.0f}};
    Vector3 res3;
    vector3_normalize(&v3, &res3);
    // 1/sqrt(3) ≈ 0.577350269
    assert(g_nearly_equal(res3.x, 0.577350269f) && "FPU precision issue in vector3_normalize!");
    
    printf("✓ FPU Precision Passed\n");
}

int main() {
    printf("Starting GMath transforms Tests...\n");
    printf("--------------------------------\n");

    test_basic_math();
    test_geometry_ops();
    test_normalization();
    test_interpolation();
    assert_is_unit(&(Vector){{1, 0, 0, 0}}, "Unit vector check failed!");
    test_slerp_specifics();
    test_normalization_stability();
    test_orthogonality_and_cross();
    test_aliasing();
    test_fpu_precision();

    printf("--------------------------------\n");
    printf("\n--- ALL TESTS PASSED SUCCESSFULLY ---\n");
    return 0;
}