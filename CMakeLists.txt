
project(cpprc)

cmake_minimum_required(VERSION 3.0)

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_PROGRAM_OPTIONS_DYN_LINK)

find_package(Boost COMPONENTS system program_options filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

include_directories(.)

add_subdirectory(src/cpprc)
add_subdirectory(src/libcpprc)
