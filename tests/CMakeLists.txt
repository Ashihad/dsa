set(TEST_BINARY_NAME tests_bin)

add_executable(
    ${TEST_BINARY_NAME} 
    "test_sorting.cpp"
    "test_searching.cpp"
)

target_link_libraries(
    ${TEST_BINARY_NAME}
    PUBLIC
    ${MISC_LIBRARY_NAME}
    ${SORTING_LIBRARY_NAME}
    ${SEARCHING_LIBRARY_NAME}
)
target_link_libraries(${TEST_BINARY_NAME} PRIVATE GTest::gtest_main)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${TEST_BINARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

# if(ENABLE_COVERAGE)
#     set(COVERAGE_MAIN "coverage")
#     set(COVERAGE_EXCLUDES
#         "${PROJECT_SOURCE_DIR}/app/*"
#         "${PROJECT_SOURCE_DIR}/cmake/*"
#         "${PROJECT_SOURCE_DIR}/docs/*"
#         "${PROJECT_SOURCE_DIR}/external/*"
#         "${PROJECT_SOURCE_DIR}/tests/*"
#         "${PROJECT_SOURCE_DIR}/build/*"
#         "/usr/include/*")
#     set(COVERAGE_EXTRA_FLAGS)
#     set(COVERAGE_DEPENDENCIES "UnitTestFoo" "UnitTestBar")

#     setup_target_for_coverage_gcovr_html(
#         NAME
#         ${COVERAGE_MAIN}
#         EXECUTABLE
#         ctest
#         DEPENDENCIES
#         ${COVERAGE_DEPENDENCIES}
#         BASE_DIRECTORY
#         ${CMAKE_SOURCE_DIR})
# endif()