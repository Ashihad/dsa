cmake_minimum_required(VERSION 3.21)

project(
  "DSA"
  VERSION 0.0.1
  LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." ON)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." ON)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize." OFF)

# Script directory
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
  include(Sanitizer)
  add_sanitizer_flags()
endif()

include(Warnings)

# QoL
include(ConfigSafeGuards)
include(AddGitSubmodule)

# External libraries
include(CPM)
cpmaddpackage("gh:google/googletest#v1.14.0")

# Main library
set(LIBRARY_NAME "dsa")
add_subdirectory("src")

# Tests
set(TEST_NAME "dsa_tests")
add_subdirectory("tests")
