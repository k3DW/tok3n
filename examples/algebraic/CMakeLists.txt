# Copyright 2023-2024 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

file(GLOB_RECURSE algebraic_files
     LIST_DIRECTORIES false
     "*.hpp"
     "*.cpp"
)



add_executable(algebraic
    ${algebraic_files}
)

tok3n_configure_source_group(algebraic)

set_target_properties(algebraic
    PROPERTIES
        FOLDER examples
)

target_link_libraries(algebraic tok3n_shared_settings)
