cmake_minimum_required(VERSION 3.21)

project(
  "C++DSA"
  VERSION 1.0.0
  LANGUAGES CXX)

# Global settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable ccache early
find_program(CCACHE ccache)
if(CCACHE)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

# Global compile/link options
option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

# Debug build options
option(ENABLE_SANITIZE_ADDR "Enable address sanitizer." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitizer." ON)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitizer." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitizer." OFF)

option(ENABLE_TESTING "Enable a Unit Testing build." ON)

# Project/Library Names
set(MISC_LIBRARY_NAME "misc")
set(SORTING_LIBRARY_NAME "sorting")
set(SEARCHING_LIBRARY_NAME "searching")
set(TRANSFORMING_LIBRARY_NAME "transforming")
set(VECTOR_LIBRARY_NAME "vector")

set(UNIT_TEST_NAME "unit_tests")
set(EXECUTABLE_NAME "main")

# Source helper functions
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
include(AddGitSubmodule)

if(ENABLE_WARNINGS)
  include(Warnings)
endif()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
  include(Sanitizer)
  add_sanitizer_flags()
endif()

# External dependencies
include(CPM)
if(ENABLE_TESTING)
  cpmaddpackage("gh:google/googletest#v1.14.0")
endif()

# SUB DIRECTORIES
add_subdirectory(3rd)
add_subdirectory(src)
add_subdirectory(app)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# Install targets
install(
  TARGETS ${EXECUTABLE_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(
  TARGETS ${LIBRARY_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
