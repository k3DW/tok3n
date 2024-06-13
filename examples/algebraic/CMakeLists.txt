
file(GLOB_RECURSE algebraic_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
)

tok3n_configure_ide("${algebraic_files}")



add_executable(algebraic
    ${algebraic_files}
)

tok3n_configure_target(algebraic PUBLIC)

set_target_properties(algebraic
    PROPERTIES
        FOLDER examples
)

target_link_libraries(algebraic PUBLIC k3::tok3n)
