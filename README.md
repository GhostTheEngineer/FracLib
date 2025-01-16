
# FracLib

## Overview

`FracLib` is a fraction library which provides an efficient and user-friendly way to work with fractions in C++. It includes various constructors, operators, and methods for basic arithmetic, comparisons, and simplifications of fractions, along with utilities for converting fractions to strings, double and floating-point representations.

---

## Features

- **Fraction Creation**: 
  - Supports fraction creation from integers, strings, and decimals.
  - Handles mixed fractions and improper formats gracefully with error messages.

- **Arithmetic Operations**:
  - Addition, subtraction, multiplication, and division for fractions and integers.
  - Compound assignments (e.g., `+=`, `-=`) with fractions and integers.
  
- **Comparison Operators**:
  - Equality, inequality, and relational operators (`==`, `!=`, `>=`, `<=`, `>`, `<`) for easy comparison.

- **Simplification**:
  - Automatically simplifies fractions using the Greatest Common Divisor (GCD) for readability.

- **Stream Support**:
  - Overloads `<<` and `>>` operators for output/input streams, making it easy to print and read fractions.

- **Static Methods**:
  - `Simplify`, `toString`, `toFloat`, and `toDouble` for easy conversions and utility functions.

See [Features](/docs/Features.md) for full feature list and planned features.

---

## Installation

### Prerequisites
- [CMake](https://cmake.org/download/) (for building)
- [Ninja](https://ninja-build.org/) (for efficient builds)

### Steps

1. **Clone or Download** the repository.

2. **Build and Install** the project by running the following commands (in the main directory):

#### Windows
```sh
./build.bat Release
```

#### MacOS/Linux
```sh
./build.sh Release
```

3. **Use in Your Projects**: Link your application to the `FracLib` library installed in the directory, `out/FracLib`.

---

## Build Output
The build process generates a folder named `FracLib` within the out directory. This folder contains the necessary files to use the Fraction library as a static library in your projects.

### Steps
These steps assume you ran the `build.bat` (or `build.sh` for MacOS/Linux) file in the main directory.

1. **Locate the FracLib Folder:** The `FracLib` folder will be created in the `out` directory. This folder includes the compiled static library (libFrac.a or Frac.lib depending on your operating system) and any necessary headers in an Include directory.

2. **Using FracLib in Your Projects:** In this repo an example project can be found in the `example` directory. This example uses CMake to include the library in the build process of some project. Please refer to that project to see how it works. If using Visual Studio or other build process please refer to online tutorials for how to include static libraries. Either way, the installed library directory which can be found in the `out` directory can be copied or moved to your desired directory and you may:
    - Include Path: Add the FracLib folder as an include path in your project's build settings.
    - Link Library: Link the static library file found in the FracLib folder to your project.

---

## Usage

After installation, you can include `frac.h` in your project and start using the library for fraction-based calculations.

### Example
```cpp
#include "frac.h"

int main() {
    FracLib::Frac a(3, 4); // 3/4
    FracLib::Frac b("1/2"); // 1/2
    FracLib::Frac result = a + b;
    std::cout << "Result: " << result << std::endl; // 5/4

    FracLib::Frac c(1.5); // 1 1/2
    std::cout << "Result: " << result * c << std::endl; // 5/8

    return 0;
}
```
---

## License
This library is released under the [`MIT License`](./LICENSE).
