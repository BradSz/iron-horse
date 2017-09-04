cmake_minimum_required (VERSION 2.6)
project (cscratch CXX)

set (cscratch_VERSION_MAJOR 0)
set (cscratch_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/cscfg.h.in"
  "${PROJECT_BINARY_DIR}/cscfg.h"
  )

# Source root
include_directories("${PROJECT_BINARY_DIR}/../src")
add_executable(../bin/scratch ../src/main.cpp)

# Test root
include_directories("${PROJECT_BINARY_DIR}/../test")
add_executable(../bin/tester  ../test/test.main.cpp)
SET(CMAKE_CXX_FLAGS "-std=c++0x")
