
set (target libcpprc)

set (sources 
	cpprc/Resource.hpp 
	cpprc/Resource.cpp
	cpprc/ResourceManager.hpp 
	cpprc/ResourceManager.cpp
)

add_library(${target} ${sources})

source_group(\\ FILES ${sources})
