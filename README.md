# DataStructs

**Author**: Sofyane Bentaleb  
**Institution**: Faculté des Sciences Appliquées - Ait Melloul  
**Field of Study**: Systèmes Embarqués  

## Overview

**DataStructs** is a C++ project aimed at providing a collection of data structures implemented using modern C++ standards (C++23). The project includes various generic and optimized data structures designed for performance and ease of use. This project can serve as a learning tool or a starting point for more advanced systems that require efficient data manipulation.

## Features

- Generic `List<T>` class with support for custom types.
- Unit testing with Catch2.
- AddressSanitizer integration for detecting memory issues.
- CMake support for easy configuration and building.
- NSIS-based packaging for Windows.
- `clang-format` configuration for consistent code style.

## Prerequisites

- C++23 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.25 or higher
- Catch2 for unit testing
- AddressSanitizer (optional for debugging)

## Setup Instructions

### Build

1. Clone the repository:
   ```bash
   git clone https://github.com/sefyan0hack/DataStructs.git
   cd DataStructs
   cmake --build build
