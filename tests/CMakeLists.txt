# Link defaults to every target under src/
link_libraries(PROJECT_DEFAULTS)

add_executable(
  ${TEST_NAME}
  "test_sorting.cpp"
  "test_searching.cpp"
  "test_vector.cpp"
)

target_include_directories(
  ${TEST_NAME}
  PUBLIC
    "../hdr"
    "./"
)

target_link_libraries(${TEST_NAME} PUBLIC ${LIBRARY_NAME})
target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main)
