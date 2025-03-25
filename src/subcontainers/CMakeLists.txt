# Sources and Headers
set(SUBCONTAINERS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/subcontainers.cpp")
set(SUBCONTAINERS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/subcontainers.hpp")
set(SUBCONTAINERS_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(${SUBCONTAINERS_LIBRARY_NAME} STATIC ${SUBCONTAINERS_SOURCES} ${SUBCONTAINERS_HEADERS})
target_include_directories(${SUBCONTAINERS_LIBRARY_NAME} PUBLIC ${SUBCONTAINERS_INCLUDES})

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
