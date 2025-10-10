# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(framework STATIC
    ${CMAKE_CURRENT_LIST_DIR}/src/Error.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Fixture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Runner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/TestResult.cpp
)
target_sources(framework PUBLIC FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/include/framework.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/framework/Assert.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/framework/Error.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/framework/Fixture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/framework/Hash.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/framework/Runner.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/framework/Test.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/framework/TestResult.hpp
)

tok3n_configure_source_group(framework)

target_include_directories(framework PUBLIC include)

target_link_libraries(framework PUBLIC tok3n_shared_settings)

target_precompile_headers(framework PUBLIC include/framework.hpp)

set_target_properties(framework
    PROPERTIES
        FOLDER tests
)

macro(tok3n_discover_tests target assembly_name)

    set(generated_file "${CMAKE_CURRENT_BINARY_DIR}/${target}.list_of_tests.cmake")

    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${target} list ${generated_file}
        COMMAND ${CMAKE_COMMAND}
            -D "ASSEMBLY_NAME=${assembly_name}"
            -D "TEST_TARGET=${target}"
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${CMAKE_SOURCE_DIR}/tests/discover_tests.cmake"
        BYPRODUCTS ${generated_file}
        VERBATIM
    )

    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${CMAKE_SOURCE_DIR}/tests/include_tests.cmake"
        VERBATIM
    )

endmacro()
