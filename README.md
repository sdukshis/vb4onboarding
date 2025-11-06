# vb4onboarding — C++ + Conan 2 + CMake

A minimal C++ project using Conan 2 for dependency management and CMake for builds. The sample uses `fmt` for formatted output.

## Prerequisites

- CMake 3.21+
- A modern C++ compiler (Clang, GCC, or MSVC)
- Conan 2.x

On macOS (fish shell):

```bash
# Install Conan 2
brew install conan

# Detect a default profile
conan profile detect --force
```

## Dependencies (managed by Conan)

Dependencies are declared in `conanfile.txt`:

- `fmt` with a version range: `fmt/[>=10 <12]`
- Generators: `CMakeDeps`, `CMakeToolchain`
- Layout: `cmake_layout`

## Configure and Build

Out-of-source build is recommended. Conan will generate the toolchain and dependency files used by CMake.

```bash
# From the project root
set -l build_dir build

# Install dependencies and generate toolchain/Find packages
conan install . \
  --output-folder $build_dir \
  --build=missing \
  -s build_type=Release

# Configure with CMake using Conan's toolchain
cmake -S . -B $build_dir \
  -DCMAKE_TOOLCHAIN_FILE=$build_dir/conan_toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build $build_dir --config Release
```

If you prefer Debug builds, change `-s build_type=Debug` and `-DCMAKE_BUILD_TYPE=Debug` accordingly.

## Run

```bash
# Default greeting
$ build/vb4onboarding
Hello, World!

# With a name argument
$ build/vb4onboarding Alice
Hello, Alice!
```

## Project Structure

```
.
├── CMakeLists.txt
├── conanfile.txt
├── src
│   └── main.cpp
└── README.md
```

## Notes

- Always pass the Conan-generated `conan_toolchain.cmake` when configuring CMake.
- `find_package(fmt REQUIRED CONFIG)` is resolved via Conan's `CMakeDeps` generator.
- Use `--build=missing` during `conan install` to automatically build packages that don’t exist in your cache.


