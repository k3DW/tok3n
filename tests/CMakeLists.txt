# Copyright 2023-2024 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_subdirectory(external/boostorg/preprocessor)

add_subdirectory(framework)
add_subdirectory(common)

macro(tok3n_add_test_executable target assembly_name value_type_pp_definition)

    if(TOK3N_DISCOVER_TESTS)
        set(target_name "${target}_")
    else()
        set(target_name "${target}")
    endif()

    add_executable(${target_name} ${ARGN})

    target_compile_definitions(${target_name} PRIVATE ${value_type_pp_definition})

    target_include_directories(${target_name} PRIVATE .)
    target_link_libraries(${target_name} PRIVATE common)
    target_precompile_headers(${target_name} PRIVATE samples.hpp)

    tok3n_configure_source_group(${target_name})

    set_target_properties(${target_name}
        PROPERTIES
            FOLDER tests
    )

    if(TOK3N_DISCOVER_TESTS)
        tok3n_discover_tests(${target_name} ${target} ${assembly_name})
        set_target_properties(${target}
            PROPERTIES
                FOLDER tests/_generated
        )
    endif()

endmacro()

add_subdirectory(char-tests)
add_subdirectory(non-char-tests)
