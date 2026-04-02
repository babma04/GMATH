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
    Vector near_pt = {0, 0, -0.1f, 1.0f}; // Pt at Near Plane (Z is negative in view space)
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
    Vector far_pt = {0, 0, -1000000.0f, 1.0f}; // Point very far away
    matrix_perspective_infinite_reversed_z(90.0f, 1.0f, 0.1f, &proj);
    matrix_vector_mult(&proj, &far_pt, &result);
    ndc_z = result.z / result.w;
    assert(g_nearly_equal(ndc_z, 0.0f) && "Infinite Reverse-Z Far-Z mapping failed!");

    printf("Projections: PASSED\n");
}

void test_camera_and_frustum() {
    Matrix view, proj, vp;
    Vector eye = {0, 0, 5}, target = {0, 0, 0}, up = {0, 1, 0};
    Vector planes[6];

    // Test 6: LookAt
    matrix_look_at(&eye, &target, &up, &view);
    Vector test_pt = {0, 0, 0, 1}; // Target should be at (0,0,-5) in view space
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
    
    Vector3 n = {1.0f, 0.0f, 0.0f}; // X-axis normal
    Vector3 res_n;
    matrix3_vector3_mult(&normal_mat, &n, &res_n);
    
    // In a normal matrix (Inverse Transpose), scaling by 2 becomes scaling by 0.5
    assert(g_nearly_equal(res_n.x, 0.5f) && "Normal Matrix non-uniform scale failed!");

    printf("Normal Matrix: PASSED\n");
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