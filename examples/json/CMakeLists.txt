
file(GLOB_RECURSE json_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
)

add_executable(json
    ${json_files}
)

set_target_properties(json
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        FOLDER examples
)

target_compile_options(json PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_link_libraries(json PUBLIC k3::tok3n)
