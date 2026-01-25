add_library(${LIBRARY_NAME} STATIC "misc.cpp" "searching.cpp" "sorting.cpp"
                                   "vector.cpp")
target_include_directories(${LIBRARY_NAME} PUBLIC "../hdr")

target_set_warnings(TARGET ${LIBRARY_NAME} ENABLE "YES" AS_ERRORS
                    ${ENABLE_WARNINGS_AS_ERRORS})
