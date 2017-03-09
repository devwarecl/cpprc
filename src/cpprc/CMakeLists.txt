
set (target cpprc)

set (sources 
    cpprc.cpp 
    ResourceGenerator.hpp 
	ResourceGenerator.cpp
    SimpleResourceGenerator.hpp 
	SimpleResourceGenerator.cpp
	MainResourceGenerator.hpp 
	MainResourceGenerator.cpp
)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)

target_link_libraries(${target} ${Boost_LIBRARIES})

install(TARGETS ${target} DESTINATION bin)

set (CPPRC_BINARY ${CMAKE_CURRENT_BINARY_DIR}/${target})
set (CPPRC_BINARY "${CPPRC_BINARY}" CACHE INTERNAL "CPPRC_BINARY")

message (${CPPRC_BINARY})
