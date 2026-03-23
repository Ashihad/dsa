cmake_minimum_required(VERSION 3.25)

project("DSA" VERSION 0.0.1 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, defaulting to Debug")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Enable ccache if possible
find_program(CCACHE ccache)
if(CCACHE)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

# Script directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Project options
option(WARNINGS_AS_ERRORS "Enable to treat warnings as errors" FALSE)

option(ENABLE_ASAN "Enable address sanitizer" TRUE)
option(ENABLE_UBSAN "Enable undefined sanitizer" FALSE)
option(ENABLE_LSAN "Enable leak sanitizer" FALSE)
option(ENABLE_TSAN "Enable thread sanitizer" FALSE)

option(ENABLE_COVERAGE "Enable coverage reporting" FALSE)

# Global project defaults
add_library(PROJECT_DEFAULTS INTERFACE)
target_compile_features(PROJECT_DEFAULTS INTERFACE cxx_std_20)

include(SetProjectDefaults)
set_project_defaults()

# External libraries
include(AddGitSubmodule)
include(CPM)
cpmaddpackage("gh:google/googletest#v1.14.0")

# Main library
set(LIBRARY_NAME "dsa")
add_subdirectory("src")

# Tests
set(TEST_NAME "dsa_tests")
add_subdirectory("tests")
