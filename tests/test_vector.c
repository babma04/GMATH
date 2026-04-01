#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "gmath.h"

void test_vector_basics() {
    printf("Testing Vector Basics...\n");
    Vector v = {1.0f, 2.0f, 3.0f, 1.0f};
    Vector u = {4.0f, 5.0f, 6.0f, 1.0f};

    // Test Sum
    Vector sum = vector_sum(v, u);
    assert(g_nearly_equal(sum.x, 5.0f));
    assert(g_nearly_equal(sum.y, 7.0f));
    assert(g_nearly_equal(sum.z, 9.0f));

    // Test Scalar
    Vector scaled = vecto_scalar(v, 2.0f);
    assert(g_nearly_equal(scaled.x, 2.0f));
    assert(g_nearly_equal(scaled.y, 4.0f));
    
    // Test Magnitude & Normalize
    Vector unit_v = {3.0f, 0.0f, 4.0f, 0.0f}; // 3-4-5 triangle
    assert(g_nearly_equal(vector_magnitude(unit_v), 5.0f));
    
    Vector norm = vector_normalize(unit_v);
    assert(g_nearly_equal(vector_magnitude(norm), 1.0f));

    // Test Dot Product (3*4 + 0*5 + 4*6) = 12 + 0 + 24 = 36
    float dot = vector_dot(unit_v, u);
    assert(g_nearly_equal(dot, 36.0f));

    printf("[PASS] Vector tests complete.\n");
}

int main() {
    test_vector_basics();
    return 0;
}