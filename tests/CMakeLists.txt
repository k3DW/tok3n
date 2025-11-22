# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_subdirectory(framework)
add_subdirectory(common)

macro(tok3n_add_basic_test_executable target assembly_name)

    add_executable(${target} ${ARGN})
    target_link_libraries(${target} PRIVATE k3::tok3n framework)

    set_target_properties(${target}
        PROPERTIES
            FOLDER tests
    )

    tok3n_discover_tests(${target} ${assembly_name})

endmacro()

macro(tok3n_add_test_executable target assembly_name value_type_pp_definition)

    tok3n_add_basic_test_executable(${target} ${assembly_name} ${ARGN})

    target_compile_definitions(${target} PRIVATE ${value_type_pp_definition})
    target_compile_options(${target} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/bigobj>)

    target_include_directories(${target} PRIVATE .)
    target_link_libraries(${target} PRIVATE common)

endmacro()

add_subdirectory(char-tests)
add_subdirectory(non-char-tests)

add_subdirectory(detail-tests)
