
file(GLOB_RECURSE k3_tok3n_tests_files
     LIST_DIRECTORIES false
     "*.h"
     "*.cpp"
)

add_executable(k3_tok3n_tests
    ${k3_tok3n_tests_files}
)

set_target_properties(k3_tok3n_tests
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_options(k3_tok3n_tests PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:
        /permissive- /volatile:iso /Zc:preprocessor
        /WX /W4
    >
)

target_precompile_headers(k3_tok3n_tests PRIVATE pch.h)

target_include_directories(k3_tok3n_tests PUBLIC .)
target_include_directories(k3_tok3n_tests PUBLIC ../include)
target_include_directories(k3_tok3n_tests PUBLIC ../external/boostorg/preprocessor/include)
