macro(set_default_warnings)
  # Handle warnings
  set(
    BASE_WARNINGS
    # Baseline
    -Wall
    -Wextra # reasonable and standard
    -Wshadow # if a variable declaration shadows one from a parent context
    -Wpedantic # warn if non-standard C++ is used
    # C and C++ Warnings
    -Wunused # warn on anything being unused
    -Wformat=2 # warn on security issues around functions that format output
    -Wcast-align # warn for potential performance problem casts
    -Wconversion # warn on type conversions that may lose data
    -Wsign-conversion # warn on sign conversions
    -Wnull-dereference # warn if a null dereference is detected
    -Wdouble-promotion # warn if float is implicit promoted to double
    # C++ Warnings
    -Wnon-virtual-dtor # if a class with virtual func has a non-virtual dest
    -Wold-style-cast # warn for c-style casts
    -Woverloaded-virtual # if you overload (not override) a virtual function
    -Weffc++ # violations from Scott Meyers’ Effective C++
  )

  set(CLANG_WARNINGS ${BASE_WARNINGS})

  set(
    GCC_WARNINGS
    ${BASE_WARNINGS}
    -Wduplicated-cond # warn if if / else chain has duplicated conditions
    -Wduplicated-branches # warn if if / else branches have duplicated code
    -Wlogical-op # warn about logical operations being used where bitwise were
    -Wmisleading-indentation # warn if indentation suggests something other than code itself
    -Wuseless-cast # warn on casting to the same type
  )

  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(WARNINGS ${CLANG_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS ${GCC_WARNINGS})
  endif()

  if(${WARNINGS_AS_ERRORS})
    list(APPEND WARNINGS -Werror)
  endif()

  target_compile_options(PROJECT_DEFAULTS INTERFACE ${WARNINGS})
endmacro()
