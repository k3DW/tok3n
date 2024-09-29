
file(GLOB_RECURSE algebraic_files
     LIST_DIRECTORIES false
     "*.h"
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
