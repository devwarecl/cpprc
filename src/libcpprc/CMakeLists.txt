
set (target libcpprc)

set (hpp 
	cpprc/Resource.hpp 
	cpprc/ResourceManager.hpp 
)

set (cpp
	cpprc/Resource.cpp 
	cpprc/ResourceManager.cpp
)

set (sources ${hpp} ${cpp})

add_library(${target} ${sources})

set_target_properties (
	${target}
	PROPERTIES 
		DEBUG_OUTPUT_NAME ${target}d
		RELEASE_OUTPUT_NAME ${target}
)

source_group(\\ FILES ${sources})

install (
	TARGETS ${target}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)

install (FILES ${hpp} DESTINATION "include/cpprc")
