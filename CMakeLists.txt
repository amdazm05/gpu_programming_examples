cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(learning)
option(BASIC_KERNEL "Basic CUDA example not built " OFF)
option(BASIC_KERNEL_CL "Basic CL example not built " OFF)

if(BASIC_KERNEL)
    add_subdirectory(${PROJECT_SOURCE_DIR}/examples/basic_kernel)
endif(BASIC_KERNEL)

if(BASIC_KERNEL_CL)
    add_subdirectory(${PROJECT_SOURCE_DIR}/examples/basic_kernel_cl)
endif(BASIC_KERNEL_CL)

