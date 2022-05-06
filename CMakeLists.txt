cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug) # 为了能够调试，相当于-g选项
# set(CMAKE_BUILD_TYPE Release)

project(unix_course_design)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(multi_processes_sv src/multi_processes_sv.c
                                  src/inet_stream_sockets.c src/util.c)

add_executable(multi_threads_sv src/multi_threads_sv.c
                                src/inet_stream_sockets.c src/util.c)
set_target_properties(multi_threads_sv PROPERTIES COMPILE_FLAGS "-pthread"
                                                  LINK_FLAGS "-pthread")

add_executable(multi_io_sv src/multi_io_sv.c src/inet_stream_sockets.c
                           src/util.c)

add_executable(single_client src/single_client.c src/inet_stream_sockets.c
                             src/util.c)

add_executable(test_client src/test_client.c src/inet_stream_sockets.c
                           src/util.c)
set_target_properties(test_client PROPERTIES COMPILE_FLAGS "-pthread"
                                             LINK_FLAGS "-pthread")
