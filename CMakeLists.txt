cmake_minimum_required (VERSION 2.6)
project (cscratch)

set (cscratch_VERSION_MAJOR 0)
set (cscratch_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/cscfg.h.in"
  "${PROJECT_BINARY_DIR}/cscfg.h"
  )

include_directories("${PROJECT_BINARY_DIR}")
add_executable(../bin/scratch ../src/main.cpp)
