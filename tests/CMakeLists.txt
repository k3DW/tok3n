# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_subdirectory(external/boostorg/preprocessor)

add_subdirectory(framework)
add_subdirectory(common)

macro(tok3n_add_test_executable target assembly_name value_type_pp_definition)

    add_executable(${target} ${ARGN})

    target_compile_definitions(${target} PRIVATE ${value_type_pp_definition})

    target_include_directories(${target} PRIVATE .)
    target_link_libraries(${target} PRIVATE common)
    target_precompile_headers(${target} PRIVATE samples.hpp)

    tok3n_configure_source_group(${target})

    set_target_properties(${target}
        PROPERTIES
            FOLDER tests
    )

    if(TOK3N_DISCOVER_TESTS)
        tok3n_discover_tests(${target} ${assembly_name})
    endif()

endmacro()

add_subdirectory(char-tests)
add_subdirectory(non-char-tests)
