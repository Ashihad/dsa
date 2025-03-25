# Sources and Headers
set(SEARCHING_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/searching.cpp")
set(SEARCHING_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/searching.hpp")
set(
  SEARCHING_INCLUDES
  "./"
  "${CMAKE_BINARY_DIR}/configured_files/include"
  "${CMAKE_SOURCE_DIR}/src/misc"
  "${CMAKE_SOURCE_DIR}/src/vector"
)

add_library(${SEARCHING_LIBRARY_NAME} STATIC ${SEARCHING_SOURCES} ${SEARCHING_HEADERS})
target_include_directories(${SEARCHING_LIBRARY_NAME} PUBLIC ${SEARCHING_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${SEARCHING_LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${SEARCHING_LIBRARY_NAME}
        ENABLE
        ON)
endif()

