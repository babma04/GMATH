#include <stdio.h>
#include <assert.h>
#include "gmath.h"

void test_matrix_transforms() {
    printf("Testing Matrix Transforms...\n");

    // Test Identity
    Matrix id = matrix_identity();
    assert(g_nearly_equal(id.a.x, 1.0f));
    assert(g_nearly_equal(id.b.y, 1.0f));
    assert(g_nearly_equal(id.c.z, 1.0f));
    assert(g_nearly_equal(id.d.w, 1.0f));

    // Test Translation
    Matrix trans = matrix_translate(10.0f, 20.0f, 30.0f);
    Vector point = {0.0f, 0.0f, 0.0f, 1.0f};
    Vector moved = matrix_vector_mult(trans, point);
    
    assert(g_nearly_equal(moved.x, 10.0f));
    assert(g_nearly_equal(moved.y, 20.0f));
    assert(g_nearly_equal(moved.z, 30.0f));

    // Test Scale
    Matrix scale = matrix_scale(2.0f, 2.0f, 2.0f);
    Vector big_moved = matrix_vector_mult(scale, moved);
    assert(g_nearly_equal(big_moved.x, 20.0f));

    printf("[PASS] Matrix tests complete.\n");
}

int main() {
    test_matrix_transforms();
    return 0;
}