#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "gmath.h"

void test_clamping_logic() {
    printf("Testing Clamping & Min/Max...\n");

    // Standard clamping
    assert(g_nearly_equal(g_clamp(50.0f, 0.0f, 1.0f), 1.0f));
    assert(g_nearly_equal(g_clamp(-10.0f, 0.0f, 1.0f), 0.0f));
    assert(g_nearly_equal(g_clamp(0.5f, 0.0f, 1.0f), 0.5f));

    // Edge case: clamp where value is exactly the boundary
    assert(g_nearly_equal(g_clamp(1.0f, 0.0f, 1.0f), 1.0f));
    assert(g_nearly_equal(g_clamp(0.0f, 0.0f, 1.0f), 0.0f));

    // Min/Max
    assert(g_nearly_equal(g_min(10.0f, 20.0f), 10.0f));
    assert(g_nearly_equal(g_max(10.0f, 20.0f), 20.0f));
    assert(g_nearly_equal(g_min(-5.0f, -10.0f), -10.0f));

    printf("  [PASS] Clamping and Min/Max verified.\n");
}

void test_trigonometry_conversions() {
    printf("Testing Angle Conversions...\n");

    // Test Degrees to Radians
    // 180 degrees should be exactly PI
    assert(g_nearly_equal(g_to_radians(180.0f), PI));
    assert(g_nearly_equal(g_to_radians(90.0f), PI / 2.0f));
    assert(g_nearly_equal(g_to_radians(0.0f), 0.0f));

    // Test Radians to Degrees
    assert(g_nearly_equal(g_to_degrees(PI), 180.0f));
    assert(g_nearly_equal(g_to_degrees(PI / 4.0f), 45.0f));

    printf("  [PASS] Deg/Rad conversions verified.\n");
}

void test_precision_logic() {
    printf("Testing Float Precision (Epsilon)...\n");

    // Test Nearly Equal (Precision check)
    // These are within the standard EPSILON (usually 1e-6)
    assert(g_nearly_equal(1.0000001f, 1.0000002f)); 
    
    // These are definitely NOT equal
    assert(!g_nearly_equal(1.0f, 1.1f));
    assert(!g_nearly_equal(0.001f, 0.0f));

    // Test very small differences
    float a = 0.1f + 0.2f;
    float b = 0.3f;
    // Standard floats fail a == b, but g_nearly_equal should pass
    assert(g_nearly_equal(a, b));

    printf("  [PASS] Precision logic verified.\n");
}

void test_visualizers() {
    printf("Testing Visualizers (Manual Inspection Required)...\n");
    
    Vector v = {1.234f, 5.678f, -9.012f, 1.0f};
    Matrix m = matrix_identity();
    
    // We don't assert these, we just ensure they don't crash 
    // and look correct in the terminal.
    g_print_vector(v, "Test Vector Output");
    g_print_matrix(m, "Test Identity Matrix Output");

    printf("  [PASS] Visualizers executed without crash.\n");
}

int main() {
    printf("Starting GMath Utility Suite...\n");
    printf("--------------------------------\n");

    test_clamping_logic();
    test_trigonometry_conversions();
    test_precision_logic();
    test_visualizers();

    printf("--------------------------------\n");
    printf("ALL UTILITY TESTS PASSED!\n");
    
    return 0;
}