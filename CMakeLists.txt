cmake_minimum_required (VERSION 2.6)
project (cscratch CXX)

set (cscratch_VERSION_MAJOR 0)
set (cscratch_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/cscfg.h.in"
  "${PROJECT_BINARY_DIR}/cscfg.h"
  )

set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Source root
include_directories(src)
add_executable(scratch src/main.cpp)

# Test root
include_directories(test)
add_executable(tester  test/test.main.cpp)
