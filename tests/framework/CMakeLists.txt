file(GLOB_RECURSE framework_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
)

tok3n_configure_ide("${framework_files}")



add_library(framework
    ${framework_files}
)

tok3n_configure_target(framework PUBLIC)

target_include_directories(framework PUBLIC include)

target_link_libraries(framework PUBLIC k3::tok3n)

target_precompile_headers(framework PUBLIC include/framework.h)

set_target_properties(framework
    PROPERTIES
        FOLDER tests
)
