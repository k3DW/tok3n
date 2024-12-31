# Copyright 2024 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

file(GLOB_RECURSE common_files
     LIST_DIRECTORIES false
     "include/*.h"
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
