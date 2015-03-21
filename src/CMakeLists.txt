
set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

add_definitions(-DBOOST_ALL_NO_LIB)
add_definitions(-DBOOST_PROGRAM_OPTIONS_DYN_LINK)

find_package(Boost COMPONENTS system program_options filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(file2cpp File2Cpp.cpp)

target_link_libraries(file2cpp ${Boost_LIBRARIES})

install(TARGETS file2cpp DESTINATION bin)
