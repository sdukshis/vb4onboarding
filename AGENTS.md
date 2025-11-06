## C++ Development Rules

You are a senior C++ developer with expertise in modern C++ (C++17/20), STL, and system-level programming.

- **Always** use Conan for third‑party C++ libraries.
- **Prefer** adding dependencies via `conanfile.txt` unless custom options/recipes are needed.
- **Never** commit generated files under `build/**/generators/`.

### Project assumptions
- Root contains `CMakeLists.txt` and `conanfile.txt`.
- Out-of-source builds live in `build/Release` and `build/Debug` (one folder per config).
- Toolchain from Conan: `build/<type>/generators/conan_toolchain.cmake`.

### One-time setup (per machine)

```bash
conan profile detect --force
```

macOS/Apple Silicon is supported by defaults; avoid hardcoding `arch` unless required.

### Add a new dependency (example: fmt)

1) Edit `conanfile.txt`:

```ini
[requires]
fmt/11.0.2

[generators]
CMakeDeps
CMakeToolchain

[layout]
cmake_layout
```

2) Install dependencies

Release:

```bash
conan install . -s build_type=Release -of build/Release --build=missing
```

Debug:

```bash
conan install . -s build_type=Debug -of build/Debug --build=missing
```

3) Configure CMake with the Conan toolchain

Release:

```bash
cmake -S . -B build/Release \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$(pwd)/build/Release/generators/conan_toolchain.cmake"
```

Debug:

```bash
cmake -S . -B build/Debug \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_TOOLCHAIN_FILE="$(pwd)/build/Debug/generators/conan_toolchain.cmake"
```

4) Build

```bash
cmake --build build/Release -j
# or
cmake --build build/Debug -j
```

5) Wire in CMake

Add to `CMakeLists.txt` (example for `fmt`):

```cmake
find_package(fmt REQUIRED)
target_link_libraries(vb4onboarding PRIVATE fmt::fmt)
```

Ensure the target name matches your executable/library target.

### Updating or changing dependencies
- Modify `[requires]` in `conanfile.txt`.
- Re-run `conan install` for each build-type output folder you use.
- Reconfigure CMake if the toolchain path changes (e.g., different `-of` output folder).

### Common commands (non-interactive)

Clean configure Release:

```bash
rm -rf build/Release && \
conan install . -s build_type=Release -of build/Release --build=missing && \
cmake -S . -B build/Release -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="$(pwd)/build/Release/generators/conan_toolchain.cmake"
```

Build + run:

```bash
cmake --build build/Release -j && ./build/Release/vb4onboarding
```

### Troubleshooting
- If `find_package(Name)` fails:
  - Ensure `Name` matches Conan’s CMake package name (check `build/<type>/generators/*Targets.cmake`).
  - Re-run `conan install` after changing `[generators]` or `[requires]`.
- If Apple Silicon arch issues occur:
  - Verify profile: `conan profile path default` then `conan profile show default`.
  - Avoid mixing Debug/Release outputs; use separate `-of` folders.

### Conventions
- Always pass `--build=missing` for reproducible CI/dev installs.
- Do not commit `build/` outputs; keep them local.
- Prefer `CMakeDeps` + `CMakeToolchain`; avoid hand-editing `CMAKE_PREFIX_PATH`.


