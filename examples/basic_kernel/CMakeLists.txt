cmake_minimum_required(VERSION 3.0)
project(basic_kernel_example LANGUAGES CUDA)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/main.cu
)
