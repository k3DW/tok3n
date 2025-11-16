# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(framework STATIC
    src/framework/error.cpp
    src/framework/fixture.cpp
    src/framework/result.cpp
    src/framework/runner.cpp
    src/framework/test.cpp
)
target_sources(framework PUBLIC FILE_SET headers TYPE HEADERS FILES
    include/framework.hpp
    include/framework/assert.hpp
    include/framework/error.hpp
    include/framework/fixture.hpp
    include/framework/hash.hpp
    include/framework/result.hpp
    include/framework/runner.hpp
    include/framework/test.hpp
)

target_include_directories(framework PUBLIC include)

set_target_properties(framework
    PROPERTIES
        FOLDER tests
)

macro(tok3n_discover_tests target assembly_name)

    set(generated_file "${CMAKE_CURRENT_BINARY_DIR}/${target}.list_of_tests.cmake")

    # Must grab it like this because we're inside macro
    get_property(_current_dir TARGET framework PROPERTY SOURCE_DIR)

    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${target} list ${generated_file}
        COMMAND ${CMAKE_COMMAND}
            -D "ASSEMBLY_NAME=${assembly_name}"
            -D "TEST_TARGET=${target}"
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${_current_dir}/cmake/discover_tests.cmake"
        BYPRODUCTS ${generated_file}
        VERBATIM
    )

    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${_current_dir}/cmake/include_tests.cmake"
        VERBATIM
    )

endmacro()
