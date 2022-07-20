cmake_minimum_required(VERSION 3.22)
project(hasha)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/fmt)

add_executable(hasha main.cpp)

target_link_libraries(hasha fmt::fmt)
