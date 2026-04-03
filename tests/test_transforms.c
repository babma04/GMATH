#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "gmath.h"

void test_core_ops() {
    Matrix id, a, res;
    matrix_identity(&id);

    // Test 1: Identity Multiplication
    matrix_translate(5.0f, 10.0f, 15.0f, &a);
    matrix_mult(&a, &id, &res);
    assert(matrix_compare(&a, &res) && "Identity multiplication failed!");

    // Test 2: Inversion
    Matrix inv, identity_check;
    matrix_inverse(&a, &inv);
    matrix_mult(&a, &inv, &identity_check);
    // Result should be identity
    assert(g_nearly_equal(identity_check.m[12], 0.0f) && "Inverse translation failed!");
    assert(g_nearly_equal(identity_check.m[15], 1.0f) && "Inverse W-scaling failed!");
    
    printf("Core Ops: PASSED\n");
}

void test_projections() {
    Matrix proj;
    Vector near_pt = {{{0, 0, -0.1f, 1.0f}}}; // Pt at Near Plane (Z is negative in view space)
    Vector result;

    // Test 3: Standard Perspective (Near -> -1.0)
    matrix_perspective(90.0f, 1.0f, 0.1f, 100.0f, &proj);
    matrix_vector_mult(&proj, &near_pt, &result);
    float ndc_z = result.z / result.w;
    assert(g_nearly_equal(ndc_z, -1.0f) && "Standard Perspective Near-Z mapping failed!");

    // Test 4: Reverse-Z (Near -> 1.0)
    matrix_perspective_reversed_z(90.0f, 1.0f, 0.1f, 100.0f, &proj);
    matrix_vector_mult(&proj, &near_pt, &result);
    ndc_z = result.z / result.w;
    assert(g_nearly_equal(ndc_z, 1.0f) && "Reverse-Z Near-Z mapping failed!");
    
    // Test 5: Infinite Reverse-Z (Far -> 0.0)
    Vector far_pt = {{{0, 0, -1000000.0f, 1.0f}}}; // Point very far away
    matrix_perspective_infinite_reversed_z(90.0f, 1.0f, 0.1f, &proj);
    matrix_vector_mult(&proj, &far_pt, &result);
    ndc_z = result.z / result.w;
    assert(g_nearly_equal(ndc_z, 0.0f) && "Infinite Reverse-Z Far-Z mapping failed!");

    printf("Projections: PASSED\n");
}

void test_camera_and_frustum() {
    Matrix view, proj, vp;
    Vector eye = {{{0, 0, 5, 1}}}, target = {{{0, 0, 0, 1}}}, up = {{{0, 1, 0, 0}}};
    Vector planes[6];

    // Test 6: LookAt
    matrix_look_at(&eye, &target, &up, &view);
    Vector test_pt = {{{0, 0, 0, 1}}}; // Target should be at (0,0,-5) in view space
    Vector res_pt;
    matrix_vector_mult(&view, &test_pt, &res_pt);
    assert(g_nearly_equal(res_pt.z, -5.0f) && "LookAt Translation/Orientation failed!");

    // Test 7: Frustum Extraction
    matrix_perspective(90.0f, 1.0f, 0.1f, 100.0f, &proj);
    matrix_mult(&proj, &view, &vp);
    matrix_extract_frustum(&vp, planes);
    
    // Near plane normal should point roughly towards the camera (+Z in view space)
    // After normalization, the magnitude of the normal (x,y,z) must be 1.0
    float mag = sqrtf(planes[0].x*planes[0].x + planes[0].y*planes[0].y + planes[0].z*planes[0].z);
    assert(g_nearly_equal(mag, 1.0f) && "Frustum Plane Normalization failed!");

    printf("Camera & Frustum: PASSED\n");
}

void test_normals() {
    Matrix model;
    Matrix3x3 normal_mat;
    
    // Test 8: Non-uniform scaling (Scale X by 2)
    matrix_scale(2.0f, 1.0f, 1.0f, &model);
    matrix_to_normal_matrix(&model, &normal_mat);
    
    Vector3 n = {{{1.0f, 0.0f, 0.0f}}}; // X-axis normal
    Vector3 res_n;
    matrix3_vector3_mult(&normal_mat, &n, &res_n);
    
    // In a normal matrix (Inverse Transpose), scaling by 2 becomes scaling by 0.5
    assert(g_nearly_equal(res_n.x, 0.5f) && "Normal Matrix non-uniform scale failed!");

    printf("Normal Matrix: PASSED\n");
}

void test_rotation_precision() {
    printf("Testing Rotation Precision (360-degree loop)...\n");
    Matrix rot, total;
    Vector axis = {{{0, 1, 0, 0}}}; // Rotate around Y
    float step = g_to_radians(10.0f); // 10 degree steps
    
    matrix_identity(&total);
    
    // Rotate 36 degrees * 10 times = 360 degrees
    for(int i = 0; i < 36; i++) {
        matrix_rotate(&axis, step, &rot);
        Matrix temp;
        matrix_mult(&rot, &total, &temp); // total = rot * total
        total = temp;
    }
    
    // After 360 degrees, it should be the identity matrix again
    assert(g_nearly_equal(total.m[0], 1.0f) && "X-axis drift after 360 rotation!");
    assert(g_nearly_equal(total.m[5], 1.0f) && "Y-axis drift after 360 rotation!");
    assert(fabsf(total.m[1]) < 0.001f && "Off-axis skew in rotation loop!");
    
    printf("✓ Rotation Precision: PASSED\n");
}

void test_non_uniform_scaling() {
    printf("Testing Non-Uniform Scaling...\n");
    Matrix scale;
    Vector v = {{{1, 1, 1, 1}}};
    Vector res;
    
    matrix_scale(2.0f, 0.5f, 10.0f, &scale);
    matrix_vector_mult(&scale, &v, &res);
    
    assert(res.x == 2.0f);
    assert(res.y == 0.5f);
    assert(res.z == 10.0f);
    printf("✓ Non-Uniform Scaling: PASSED\n");
}

void test_transformation_order() {
    printf("Testing Transformation Order (TRS vs SRT)...\n");
    Matrix T, R, S, TR, TRS;
    Vector axis = {{{0, 0, 1, 0}}}; // Z-axis
    Vector p = {{{1, 0, 0, 1}}};    // Point at (1,0,0)
    Vector res;

    // Standard OpenGL order: Result = T * R * S * Position
    matrix_translate(5, 0, 0, &T);
    matrix_rotate(&axis, g_to_radians(90.0f), &R); // (1,0) -> (0,1)
    matrix_scale(2, 2, 2, &S);

    // Step 1: Scale (2,0)
    // Step 2: Rotate (0,2)
    // Step 3: Translate (5,2)
    matrix_mult(&T, &R, &TR);
    matrix_mult(&TR, &S, &TRS);
    
    matrix_vector_mult(&TRS, &p, &res);

    assert(g_nearly_equal(res.x, 5.0f));
    assert(g_nearly_equal(res.y, 2.0f));
    printf("✓ Transformation Order (TRS): PASSED\n");
}

void test_singular_matrix_inverse() {
    printf("Testing Singular Matrix Handling...\n");
    Matrix singular, res;
    matrix_set_to_zero(&singular); // Determinant is 0
    
    // Should print warning and return identity per your matrix_inverse logic
    matrix_inverse(&singular, &res);
    
    assert(res.m[0] == 1.0f && res.m[15] == 1.0f);
    printf("✓ Singular Matrix Safety: PASSED\n");
}

void test_look_at_orientation() {
    Vector eye = {{{0, 0, 0, 1}}};
    Vector target = {{{0, 0, -1, 1}}}; // Looking "forward" in OpenGL
    Vector up = {{{0, 1, 0, 0}}};
    Matrix res;

    matrix_look_at(&eye, &target, &up, &res);

    // This should result in an Identity Matrix
    assert(g_nearly_equal(res.m[0], 1.0f));  // Right.x
    assert(g_nearly_equal(res.m[5], 1.0f));  // Up.y
    assert(g_nearly_equal(res.m[10], 1.0f)); // Forward.z
    printf("✓ LookAt Orientation Passed\n");
}

void test_camera_translation() {
    Vector eye = {{{0, 0, 10, 1}}};   // Camera is 10 units back
    Vector target = {{{0, 0, 0, 1}}};  // Looking at origin
    Vector up = {{{0, 1, 0, 0}}};
    Matrix res;

    matrix_look_at(&eye, &target, &up, &res);

    // An object at (0,0,0) should now be at (0,0,-10) in camera space
    // result->m[14] is the Z-translation in Column-Major
    assert(g_nearly_equal(res.m[14], -10.0f)); 
    printf("✓ Camera Translation Passed\n");
}

void test_vertical_look() {
    Vector eye = {{{0, 0, 0, 1}}};
    Vector target = {{{0, 1, 0, 1}}}; // Looking straight UP
    Vector up = {{{0, 1, 0, 0}}};    // Up is also UP
    Matrix res;

    // This should NOT crash or produce NaNs
    matrix_look_at(&eye, &target, &up, &res);
    
    assert(!isnan(res.m[0]));
    printf("✓ Vertical Look (Gimbal) Passed\n");
}

int main() {
    printf("Starting GMath transforms Tests...\n");
    printf("--------------------------------\n");

        test_rotation_precision();
        test_non_uniform_scaling();
        test_transformation_order();
        test_singular_matrix_inverse();
        test_rotation_precision();
        test_non_uniform_scaling();
        test_transformation_order();
        test_singular_matrix_inverse();
        test_look_at_orientation();
        test_camera_translation();
        test_vertical_look();

    printf("--------------------------------\n");
    printf("ALL TESTS PASSED!\n");
    return 0;
}