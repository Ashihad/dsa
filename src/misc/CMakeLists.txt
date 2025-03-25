# Sources and Headers
set(MISC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/misc.cpp")
set(MISC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/misc.hpp")
set(MISC_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include" "${CMAKE_SOURCE_DIR}/src/vector")

add_library(${MISC_LIBRARY_NAME} STATIC ${MISC_SOURCES} ${MISC_HEADERS})
target_include_directories(${MISC_LIBRARY_NAME} PUBLIC ${MISC_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${MISC_LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${MISC_LIBRARY_NAME}
        ENABLE
        ON)
endif()
