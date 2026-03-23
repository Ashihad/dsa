macro(set_sanitizers)
  if(ENABLE_ASAN OR ENABLE_UBSAN OR ENABLE_LSAN OR ENABLE_TSAN)
    target_compile_options(PROJECT_DEFAULTS INTERFACE -fno-omit-frame-pointer)
    target_link_libraries(PROJECT_DEFAULTS INTERFACE -fno-omit-frame-pointer)
  endif()

  if(ENABLE_ASAN)
    target_compile_options(PROJECT_DEFAULTS INTERFACE -fsanitize=address)
    target_link_libraries(PROJECT_DEFAULTS INTERFACE -fsanitize=address)
  endif()

  if(ENABLE_UBSAN)
    target_compile_options(PROJECT_DEFAULTS INTERFACE -fsanitize=undefined)
    target_link_libraries(PROJECT_DEFAULTS INTERFACE -fsanitize=undefined)
  endif()

  if(ENABLE_LSAN)
    target_compile_options(PROJECT_DEFAULTS INTERFACE -fsanitize=leak)
    target_link_libraries(PROJECT_DEFAULTS INTERFACE -fsanitize=leak)
  endif()

  if(ENABLE_TSAN)
    if(ENABLE_ASAN OR ENABLE_LSAN)
      message(
        WARNING
        "TSan does not work with ASAN or LSAN, consider choosing one over the other"
      )
    endif()
    target_compile_options(PROJECT_DEFAULTS INTERFACE -fsanitize=thread)
    target_link_libraries(PROJECT_DEFAULTS INTERFACE -fsanitize=thread)
  endif()
endmacro()
