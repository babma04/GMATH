# GMath
## Author: João Carrilho Louro 

A performance-oriented 3D mathematics library for C11. **GMath** is built with a column-major memory layout, ensuring native compatibility with OpenGL and modern graphics pipelines.

## 🚀 Key Features

* **Zero-Overhead Types:** Utilizes C unions to allow access to matrices as both raw 1D arrays and named column vectors.
* **Column-Major:** Optimized for 3D graphics (OpenGL style).
* **Right-Handed Coordinate System:** +Y is Up, +X is Right, and -Z is Forward (into the screen).
* **Robust Numerical Stability**: Handles extreme magnitudes (1020+) and floating-point "noise" through careful normalization and epsilon-based comparisons.
* **Radiant-Based Trig:** Internal calculations use Radians, while public APIs provide Degree-to-Radian conversion helpers.
* **Modular Architecture:** Separate headers for vectors, transforms, and utilities to ensure a clean and scalable codebase.
* **Built-in Verification:** Includes a comprehensive suite of mathematical tests using C assertions.
* **Modern Projection Suite**:

    * **Reversed-Z Persistence**: Leverages floating-point density near zero to provide superior depth precision, virtually eliminating Z-fighting on distant geometry.

    * **Infinite Far-Plane**: Supports astronomical draw distances via specialized projection matrices that remove the far-clip constraint.

## 🔧 Implementation Details

### Type Safety via Unions
We use C `unions` and anonymous structs in `types.h` to provide multiple ways to access the same memory without performance loss:
* Access a **Matrix** as a flat array `m.m[16]` for loops.
* Access a **Matrix** as four named column vectors `a, b, c, d` for readable transformation logic.
The same logic is applied to vector accesses of the type **Vector**.

### Performance
* **Single Precision:** All calculations use `float` (32-bit) to ensure compatibility with GPU vertex buffers and to minimize memory bandwidth.
* **Numerical Hardening**: Functions like `vector_normalize` use scaling techniques to prevent intermediate overflow when squaring large components.

* **Interpolation Safety**: Includes both standard and "Safe" variants of LERP and SLERP with factor clamping and monotonic precision.

## 📁 Project Structure

```text
GMath/
├── include/           # Header files (.h)
│   ├── gmath.h        # Master include
│   ├── types.h        # Vector and Matrix definitions
│   ├── vector.h       # Vector algebra
│   ├── transforms.h   # Matrix transformations
│   ├── utils.h        # Math helpers & visualizers
│   └── constants.h    # Mathematical constants
├── src/               # Implementation files (.c)
│   ├── vector.c
│   ├── transforms.c
│   ├── utils.c
├── tests/             # Unit test suite
│   ├── test_vector.c
│   ├── test_transforms.c
│   ├── test_utils.c
├── obj/               # Compiled object files (Git ignored)
├── bin/               # Compiled binaries (Git ignored)
└── Makefile           # Build system
```

--- 

## 🛠️ Build & Install

### Prerequisites
Developed and tested on Arch Linux. Requires the base-devel package group.
```bash
sudo pacman -S base-devel
```

### Compilation
To build the static library (libgmath.a):
```bash
make
```

### Linking to Your Project
To use GMath in an external project, point your compiler to the include directory and link the binary:
```bash
gcc main.c -I./include -L./bin -lgmath -lm -o my_program
```

### Testing
The build system automatically detects all .c files in the tests/ directory and creates individual binaries in bin/. To build and run them:
```bash
# Build all test binaries
make test

# Run specific suites
./bin/test_vector
./bin/test_matrix_advanced
./bin/test_utils
```

---

## 💻 Code Example

```c
#include "gmath.h"

int main() {
    // 1. Initialize with triple-brace nesting for strict C11 compliance
    Vector start = {{{1.0f, 0.0f, 0.0f, 0.0f}}};
    Vector end   = {{{0.0f, 1.0f, 0.0f, 0.0f}}};
    Vector res;

    // 2. Perform Spherical Linear Interpolation (50%)
    vector_slerp(&start, &end, 0.5f, &res);

    // 3. Result will be ~0.7071 on X and Y (45 degrees on arc)
    g_print_vector(res, "SLERP Midpoint");

    return 0;
}
```

---

## 🧪 API Overview

- `vector.h` - Vector Algebra
```c 
// Basic Vector Arithmetic
void vector_sum (const Vector *v, const Vector *u, Vector* result);
void vector_sub (const Vector *v, const Vector *u, Vector* result);
void vector_scalar (const Vector *v, float scalar, Vector* result);

// Angular Vector Operations
float vectors_angle (const Vector *v, const Vector *u);

// Main Vector Operations
float vector_dot (const Vector *v, const Vector *u);
void vector_cross3D (const Vector *v, const Vector *u, Vector* result);
void vector_cross4D (const Vector *v, const Vector *u, Vector* result);
float vector_magnitude (const Vector *v);
void vector_normalize (const Vector *v, Vector* result);
void vector3_normalize(const Vector3 *v, Vector3* result);

// Interpolation
void vector_lerp (const Vector *v, const Vector *u, float t, Vector* result);
void vector_safeLerp (const Vector *v, const Vector *u, float t, Vector* result);
void vector_slerp (const Vector *v, const Vector *u, float t, Vector* result);
void vector_safeSlerp (const Vector *v, const Vector *u, float t, Vector* result);

// Helpers
void vector3_to_4 (const Vector3 *v, Vector* result);
void vector4_to_3 (const Vector *v, Vector3* result);
int vector_compare (const Vector *v, const Vector *u);
```

- `transforms.h` - Matrix Transformations
```c
// Core Matrix Operations
void matrix_identity (Matrix *result);
void matrix_identity3x3 (Matrix3x3 *result);
void matrix_mult (const Matrix *a, const Matrix *b, Matrix* result);
void matrix_vector_mult (const Matrix *a, const Vector *v, Vector* result);
void matrix3_vector3_mult (const Matrix3x3 *m, const Vector3 *v, Vector3* result);
void matrix_transpose (const Matrix *m, Matrix* result);
float matrix_determinant (const Matrix *m);
float matrix3x3_determinant (const Matrix3x3 *m);
void matrix_inverse(const Matrix *m, Matrix* result);

// Main Transformations
void matrix_translate (float x, float y, float z, Matrix* result);
void matrix_scale (float x, float y, float z, Matrix* result);
void matrix_rotate (Vector *axis, float angle_radians, Matrix* result);

// Camera and Viewing
void matrix_look_at (const Vector *eye, const Vector *target, const Vector *up, Matrix* result);
void matrix_perspective (float fov_deg, float aspect, float near, float far, Matrix* result);
void matrix_perspective_reversed_z(float fov_deg, float aspect, float near, float far, Matrix* result);
void matrix_perspective_infinite_reversed_z(float fov_deg, float aspect, float near, Matrix* result);
void matrix_ortho(float left, float right, float bottom, float top, float near, float far, Matrix* result);
void matrix_to_normal_matrix(const Matrix *model, Matrix3x3 *result);
void matrix_extract_frustum(const Matrix *view_proj, Vector planes[6]);
void matrix_extract_frustum_rev_z(const Matrix *view_proj, Vector planes[6]);

// Helpers
int matrix_compare (const Matrix *a, const Matrix *b);
void matrix_convert (int row_to_remove, int column_to_remove, const Matrix *input, Matrix3x3 *result);
void matrix3x3_convert (const Matrix3x3 *m, Matrix *result);
void matrix_cofactor(const Matrix *m, Matrix *result);
void matrix_set_to_zero (Matrix *m);
```

- `utils.h` - Math and Debug Helpers
```c
// Value constraints
float g_clamp (float value, float min, float max);
float g_min (float a, float b);
float g_max (float a, float b);
float g_safe_divide (float numerator, float denominator);
float g_lerp (float a, float b, float t);

// Angle conversions
static inline float g_to_radians (float degrees);
static inline float g_to_degrees (float radians);

// Float comparison 
int g_nearly_equal (float a, float b);
int g_math_cmp(float a, float b);

// Math visualizer utils
void g_print_vector (const Vector *v, const char *label);
void g_print_matrix (const Matrix *m, const char *label);
```

---

## 📄 License
Educational Open Source - Developed for Computer Science Graphics Foundations.

