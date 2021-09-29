cmake_minimum_required(VERSION 3.10)

project(hllvm C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(HLLVM_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(HLLVM_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -O3 -march=native")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2")

add_subdirectory(uvideomem)
add_subdirectory(upt)