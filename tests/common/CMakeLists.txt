file(GLOB_RECURSE common_files
     LIST_DIRECTORIES false
     "include/*.h"
     "include/*.ipp"
)



add_library(common INTERFACE
    ${common_files}
)

tok3n_configure_source_group(common)

target_include_directories(common INTERFACE include)

target_link_libraries(common INTERFACE framework)
target_link_libraries(common INTERFACE Boost::preprocessor)

target_precompile_headers(common INTERFACE include/common.h)

set_target_properties(common
    PROPERTIES
        FOLDER tests
)
