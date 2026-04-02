# GMath
## Author: João Carrilho Louro 

A performance-oriented 3D mathematics library for C11. **GMath** is built with a column-major memory layout, ensuring native compatibility with OpenGL and modern graphics pipelines.

## 🚀 Key Features

* **Zero-Overhead Types:** Utilizes C unions to allow access to matrices as both raw 1D arrays and named column vectors.
* **Column-Major:** Optimized for 3D graphics (OpenGL style).
* **Right-Handed Coordinate System:** +Y is Up, +X is Right, and -Z is Forward (into the screen).
* **Radiant-Based Trig:** Internal calculations use Radians, while public APIs provide Degree-to-Radian conversion helpers.
* **Modular Architecture:** Separate headers for vectors, transforms, and utilities to ensure a clean and scalable codebase.
* **Built-in Verification:** Includes a comprehensive suite of mathematical tests using C assertions.

## 🔧 Implementation Details

### Type Safety via Unions
We use C `unions` in `types.h` to provide multiple ways to access the same memory without performance loss:
* Access a **Matrix** as a flat array `m[16]` for loops.
* Access a **Matrix** as four named column vectors `a, b, c, d` for readable transformation logic.
The same looic is applied to vector accesses of the type **Vector**.

### Performance
* **Single Precision:** All calculations use `float` (32-bit) to ensure compatibility with GPU vertex buffers and to minimize memory bandwidth.
* **Inline Helpers:** Critical conversion functions are marked `static inline` to reduce function call overhead.

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
#include <stdio.h>

int main() {
    // 1. Initialize an identity matrix
    Matrix model = matrix_identity();

    // 2. Create a translation (Move 5 units on X, 10 on Z)
    Matrix translation = matrix_translate(5.0f, 0.0f, 10.0f);

    // 3. Combine transformations (Multiplication)
    model = matrix_mult(model, translation);

    // 4. Transform a point
    Vector point = {0.0f, 0.0f, 0.0f, 1.0f};
    Vector result = matrix_vector_mult(model, point);

    // 5. Visualize result using built-in utils
    g_print_vector(result, "Transformed Point");

    return 0;
}
```

---

## 🧪 API Overview

- `vector.h`
    - **vector_sum(v, u, result)**: Component-wise addition.
    - **vector_sub(v, u, result)**: Component-wise subtraction.
    - **vector_scallar(v, scalar, result)**: Component-wise scalar multiplication.
    - **vectors_angle(v, u)**: Calculates the angle between two vectors.
    - **vector_dot(v, u)**: Scalar product for lighting and angle calculations.
    - **vector_cross3D(v, u, result)**: Generates a perpendicular surface normal.
    - **vector_cross4D(v, u, result)**: Generates a perpendicular surface normal plane.
    - **vector_normalize(v, result)**: Scales a vector to a unit length of 1.0.
    - **vector_lerp(v, u, t, result)**: Linear interpolation between two points.
    - **vector_safeLerp(v, u, t, result)**: Linear interpolation between two points. Verifies the value of the interpolation factor and clamps it if it is outside the valid range.
    - **vector_slerp(v, u, t, result)**: Angular interpolation between two points.
    - **vector_safeSlerp(v, u, t, result)**: Angular interpolation between two points. Verifies the value of the interpolation factor and clamps it if it is outside the valid range. 

- `transforms.h`
    - **matrix_identity()**: Generates a 4x4 identity matrix.
    - **matrix_mult(A, B)**: High-performance matrix-matrix multiplication.
    - **matrix_vector_mult(M, V)**: Transforms a vector by a matrix.
    - **matrix_translate(x, y, z)**: Creates a translation matrix.
    - **matrix_rotate(x, y, z)**: Generates rotation matrices using Euler angles.
    - **matrix_perspective(fov, aspect, near, far)**: Generates a perspective projection matrix.
    - **Matrix Inversion:** Gaussian elimination for calculating inverse matrices.

- `utils.h`
    - **g_clamp(val, min, max)**: Constrains a value within a specific range.
    - **g_min(a, b)** / **g_max(a, b)**: Standard comparison helpers.
    - **g_nearly_equal(a, b)**: Float-safe comparison using an epsilon threshold.
    - **g_to_radians(deg)** / **g_to_degrees(rad)**: Inline angle conversion functions.
    - **g_print_vector(v, label)**: Formatted terminal output for 4D vectors.
    - **g_print_matrix(m, label)**: Clean, grid-aligned terminal output for 4x4 matrices.

---

## 📄 License
Educational Open Source - Developed for Computer Science Graphics Foundations.

