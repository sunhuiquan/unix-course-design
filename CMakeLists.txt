cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE Debug) # 为了能够调试，相当于-g选项
# set(CMAKE_BUILD_TYPE Release)
project(unix_course_design)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(multiple_processes_server)
add_executable(multiple_threads_server)
add_executable(io_multiplexing_server)
add_executable(test_client)
