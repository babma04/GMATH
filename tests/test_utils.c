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
    Matrix m;
    matrix_identity(&m);
    
    // We don't assert these, we just ensure they don't crash 
    // and look correct in the terminal.
    g_print_vector(&v, "Test Vector Output");
    g_print_matrix(&m, "Test Identity Matrix Output");

    printf("  [PASS] Visualizers executed without crash.\n");
}

void test_safe_divide() {
    printf("Testing Safe Divide...\n");

    // Normal division
    assert(g_nearly_equal(g_safe_divide(10.0f, 2.0f), 5.0f));

    // Division by zero should return 0 (or some defined safe value)
    assert(g_nearly_equal(g_safe_divide(10.0f, 0.0f), 0.0f));
    assert(g_nearly_equal(g_safe_divide(-5.0f, 0.0f), 0.0f));

    printf("  [PASS] Safe Divide verified.\n");
}

void test_lerp() {
    printf("Testing Linear Interpolation (Lerp)...\n");

    // Standard interpolation
    assert(g_nearly_equal(g_lerp(0.0f, 10.0f, 0.5f), 5.0f));
    assert(g_nearly_equal(g_lerp(10.0f, 20.0f, 0.25f), 12.5f));
    assert(g_nearly_equal(g_lerp(-10.0f, 10.0f, 0.75f), 5.0f));

    // Edge cases
    assert(g_nearly_equal(g_lerp(10.0f, 20.0f, 0.0f), 10.0f)); // t=0 should return a
    assert(g_nearly_equal(g_lerp(10.0f, 20.0f, 1.0f), 20.0f)); // t=1 should return b

    printf("  [PASS] Lerp verified.\n");
}

int main() {
    printf("Starting GMath Utility Suite...\n");
    printf("--------------------------------\n");

    test_clamping_logic();
    test_trigonometry_conversions();
    test_precision_logic();
    test_visualizers();
    test_safe_divide();
    test_lerp();

    printf("--------------------------------\n");
    printf("ALL UTILITY TESTS PASSED!\n");
    
    return 0;
}