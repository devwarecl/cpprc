
set (target cpprc)

set (sources 
    cpprc.cpp 
    ResourceGenerator.hpp ResourceGenerator.cpp
    SimpleResourceGenerator.hpp SimpleResourceGenerator.cpp
)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)

target_link_libraries(${target} ${Boost_LIBRARIES})

install(TARGETS ${target} DESTINATION bin)
