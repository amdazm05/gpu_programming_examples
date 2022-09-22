cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(learning)
option(BASIC_KERNEL "Basic example not built " OFF)

if(BASIC_KERNEL)
    add_subdirectory(${PROJECT_SOURCE_DIR}/examples/basic_kernel)
endif(BASIC_KERNEL)

