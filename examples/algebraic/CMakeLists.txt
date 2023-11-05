
file(GLOB_RECURSE algebraic_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
)

add_executable(algebraic
    ${algebraic_files}
)

set_target_properties(algebraic
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        FOLDER examples
)

target_compile_options(algebraic PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_link_libraries(algebraic PUBLIC k3::tok3n)
