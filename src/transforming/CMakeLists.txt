# Sources and Headers
set(TRANSFORMING_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/transforming.cpp")
set(TRANSFORMING_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/transforming.hpp")
set(
  TRANSFORMING_INCLUDES
  "./"
  "${CMAKE_BINARY_DIR}/configured_files/include"
  "${CMAKE_SOURCE_DIR}/src/misc"
)

add_library(${TRANSFORMING_LIBRARY_NAME} STATIC ${TRANSFORMING_SOURCES} ${TRANSFORMING_HEADERS})
target_include_directories(${TRANSFORMING_LIBRARY_NAME} PUBLIC ${TRANSFORMING_INCLUDES})

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${TRANSFORMING_LIBRARY_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        ${TRANSFORMING_LIBRARY_NAME}
        ENABLE
        ON)
endif()
