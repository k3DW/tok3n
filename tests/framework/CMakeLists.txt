# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(framework STATIC
    src/framework/Error.cpp
    src/framework/fixture.cpp
    src/framework/runner.cpp
    src/framework/test.cpp
    src/framework/TestResult.cpp
)
target_sources(framework PUBLIC FILE_SET headers TYPE HEADERS FILES
    include/framework.hpp
    include/framework/Assert.hpp
    include/framework/Error.hpp
    include/framework/fixture.hpp
    include/framework/Hash.hpp
    include/framework/runner.hpp
    include/framework/test.hpp
    include/framework/TestResult.hpp
)

target_include_directories(framework PUBLIC include)

target_link_libraries(framework PUBLIC k3::tok3n)

target_precompile_headers(framework PUBLIC include/framework.hpp)

set_target_properties(framework
    PROPERTIES
        FOLDER tests
)

set(_tok3n_test_framework_list_dir "${CMAKE_CURRENT_LIST_DIR}")

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
