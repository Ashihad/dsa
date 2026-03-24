# Link defaults to every target under src/
link_libraries(PROJECT_DEFAULTS)

add_library(
  ${LIBRARY_NAME}
  STATIC
  "vector.cpp"
  "misc.cpp"
  "searching.cpp"
  "sorting.cpp"
)
target_include_directories(${LIBRARY_NAME} PUBLIC "../hdr")
