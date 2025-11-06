cmake_minimum_required(VERSION 3.21)

project(vb4onboarding
    VERSION 0.1.0
    DESCRIPTION "Simple C++ project using Conan 2 for dependencies"
    LANGUAGES CXX)

# Use modern C++ standard across the project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable folders for IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Main executable
add_executable(vb4onboarding)
target_sources(vb4onboarding
    PRIVATE
        src/main.cpp
)

# Find and link dependencies provided by Conan (via CMakeDeps)
find_package(fmt REQUIRED CONFIG)
target_link_libraries(vb4onboarding PRIVATE fmt::fmt)

# Recommended compile features and warnings
target_compile_features(vb4onboarding PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(vb4onboarding PRIVATE /W4 /permissive-)
else()
    target_compile_options(vb4onboarding PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Installation rules (optional)
include(GNUInstallDirs)
install(TARGETS vb4onboarding RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


