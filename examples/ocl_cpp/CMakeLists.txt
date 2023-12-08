cmake_minimum_required(VERSION 3.7)
find_package(OpenCL REQUIRED)
add_executable(main ./main.cc)
target_link_libraries(main PUBLIC OpenCL::OpenCL)