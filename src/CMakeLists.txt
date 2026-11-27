# Link defaults to every target under src/
link_libraries(PROJECT_DEFAULTS)

add_library(
  ${LIBRARY_NAME}
  STATIC
  "custom_vector.cpp"
  "custom_string.cpp"
  "misc.cpp"
  "reduction.cpp"
  "searching.cpp"
  "sorting.cpp"
  "transform.cpp"
)
target_include_directories(${LIBRARY_NAME} PUBLIC "../hdr")
