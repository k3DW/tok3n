file(GLOB_RECURSE framework_files
    LIST_DIRECTORIES false
        "*.h"
        "*.cpp"
)

add_library(framework
    ${framework_files}
)

tok3n_configure_source_group(framework)

target_include_directories(framework PUBLIC include)

target_link_libraries(framework PUBLIC tok3n_shared_settings)

target_precompile_headers(framework PUBLIC include/framework.h)

set_target_properties(framework
    PROPERTIES
        FOLDER tests
)
