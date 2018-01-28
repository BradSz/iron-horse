cmake_minimum_required (VERSION 2.6)
project (ironhorse CXX)
enable_testing()

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

set (ironhorse_VERSION_MAJOR 0)
set (ironhorse_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/cscfg.h.in"
  "${PROJECT_BINARY_DIR}/cscfg.h"
)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost 1.54 COMPONENTS program_options thread system chrono log REQUIRED)

# Source root
include_directories(src)
add_executable(scratch   src/main.cpp)
add_executable(primecalc src/iron/math/PrimeCalculator.cpp)

# Linker settings
target_link_libraries(scratch   LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(primecalc LINK_PUBLIC ${Boost_LIBRARIES})

# Test root
include_directories(test)

# All .cpp source files in test/ are built into unit tests
file(GLOB_RECURSE TESTCPPS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
foreach(testcpp ${TESTCPPS})
  get_filename_component(testname ${testcpp} NAME_WE)
  add_executable(${testname} ${testcpp})
  target_link_libraries(${testname} ${Boost_LIBRARIES})
  add_test(
    NAME              ${testname}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMAND           ${CMAKE_BINARY_DIR}/bin/${testname}
  )
endforeach(testcpp)
