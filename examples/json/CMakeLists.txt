
file(GLOB_RECURSE json_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
)

tok3n_configure_ide("${json_files}")



add_executable(json
    ${json_files}
)

tok3n_configure_target(json PUBLIC)

set_target_properties(json
    PROPERTIES
        FOLDER examples
)

target_link_libraries(json PUBLIC k3::tok3n)
