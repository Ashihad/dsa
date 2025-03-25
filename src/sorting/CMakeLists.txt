# Sources and Headers
set(SORTING_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sorting.cpp")
set(SORTING_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/sorting.hpp")
set(SORTING_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(${SORTING_LIBRARY_NAME} STATIC ${SORTING_SOURCES} ${SORTING_HEADERS})
target_include_directories(${SORTING_LIBRARY_NAME} PUBLIC ${SORTING_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${SORTING_LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${SORTING_LIBRARY_NAME}
        ENABLE
        ON)
endif()
