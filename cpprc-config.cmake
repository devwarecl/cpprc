
# library component
add_library(libcpprc IMPORTED)

find_library(CPPRC_LIBRARY libcpprc HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")

set(CPPRC_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../include")

set_target_properties(libcpprc PROPERTIES IMPORTED_LOCATION "${CPPRC_LIBRARY}")

# TODO: Add the required 
set (CPPRC_BIN "${CMAKE_CURRENT_LIST_DIR}/../../../bin")
