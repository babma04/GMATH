#include <stdio.h>
#include <assert.h>
#include "gmath.h"

void test_utilities() {
    printf("Testing Utility Functions...\n");

    // Test Clamp
    assert(g_nearly_equal(g_clamp(50.0f, 0.0f, 1.0f), 1.0f));
    assert(g_nearly_equal(g_clamp(-10.0f, 0.0f, 1.0f), 0.0f));
    assert(g_nearly_equal(g_clamp(0.5f, 0.0f, 1.0f), 0.5f));

    // Test Min/Max
    assert(g_nearly_equal(g_min(10.0f, 20.0f), 10.0f));
    assert(g_nearly_equal(g_max(10.0f, 20.0f), 20.0f));

    // Test Nearly Equal (Precision check)
    assert(g_nearly_equal(1.0000001f, 1.0000002f)); 
    assert(!g_nearly_equal(1.0f, 1.1f));

    printf("[PASS] Utility tests complete.\n");
}

int main() {
    test_utilities();
    return 0;
}