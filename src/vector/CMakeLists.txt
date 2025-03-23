# Sources and Headers
set(VECTOR_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/vector.cpp")
set(VECTOR_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/vector.hpp")
set(
  VECTOR_INCLUDES
  "./"
  "${CMAKE_BINARY_DIR}/configured_files/include"
  "${CMAKE_SOURCE_DIR}/src/misc/"
)

add_library(${VECTOR_LIBRARY_NAME} STATIC ${VECTOR_SOURCES} ${VECTOR_HEADERS})
target_include_directories(${VECTOR_LIBRARY_NAME} PUBLIC ${VECTOR_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${VECTOR_LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${LIBRARY_NAME}
        ENABLE
        ON)
endif()
