
project(cpprc)

cmake_minimum_required(VERSION 3.0)

option (CPPRC_ENABLE_COMPILER OFF "Enable the compiler build")

include_directories(.)

add_subdirectory(src/cpprc)
add_subdirectory(src/libcpprc)
