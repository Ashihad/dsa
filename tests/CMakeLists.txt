set(TEST_BINARY_NAME tests_bin)

add_executable(
  ${TEST_BINARY_NAME} "test_sorting.cpp" "test_searching.cpp"
                      "test_transforming.cpp" "test_vector.cpp" "test_misc.cpp")

target_link_libraries(
  ${TEST_BINARY_NAME}
  PUBLIC ${MISC_LIBRARY_NAME} ${SORTING_LIBRARY_NAME} ${SEARCHING_LIBRARY_NAME}
         ${TRANSFORMING_LIBRARY_NAME} ${VECTOR_LIBRARY_NAME})
target_link_libraries(${TEST_BINARY_NAME} PRIVATE GTest::gtest_main)

if(${ENABLE_WARNINGS})
  target_set_warnings(TARGET ${TEST_BINARY_NAME} ENABLE ${ENABLE_WARNINGS}
                      AS_ERRORS ${ENABLE_WARNINGS_AS_ERRORS})
endif()

