macro(enable_coverage)
  if(ENABLE_COVERAGE)
    target_compile_options(
      PROJECT_DEFAULTS
      INTERFACE
        --coverage
        -O0
        -ggdb3
    )
    target_link_libraries(PROJECT_DEFAULTS INTERFACE --coverage)
  endif()
endmacro()
