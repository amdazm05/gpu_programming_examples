cmake_minimum_required(VERSION 3.0)
project(gpu)

set(OCL_ROOT "C:/Program Files (x86)/OCL_SDK_Light")
message(STATUS ${OCL_ROOT})

add_executable(main main.cc)
target_include_directories(main PUBLIC ${OCL_ROOT}/include)

target_link_libraries(main PUBLIC ${OCL_ROOT}/lib/x86_64/opencl.lib)
