add_subdirectory(external/boostorg/preprocessor)

add_subdirectory(framework)
add_subdirectory(common)

macro(tok3n_configure_test_target target value_type_pp_definition)

    target_compile_definitions(${target} PRIVATE ${value_type_pp_definition})
    tok3n_configure_target(${target} PUBLIC)
    target_include_directories(${target} PUBLIC .)
    target_link_libraries(${target} PUBLIC common)
    target_precompile_headers(${target} PRIVATE samples.h)

    set_target_properties(${target}
        PROPERTIES
            FOLDER tests
    )

    tok3n_discover_tests(${target})

endmacro()

macro(tok3n_discover_tests target)

    set(generated_file "${CMAKE_CURRENT_BINARY_DIR}/${target}_add_tests.cmake")

    add_custom_target("${target}_add_tests" ALL)
    add_dependencies("${target}_add_tests" "${target}")

    add_custom_command(
        TARGET "${target}_add_tests" POST_BUILD
        COMMAND ${target} list "${generated_file}"
        COMMAND "${CMAKE_COMMAND}"
            -D "TEST_TARGET=${target}"
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${CMAKE_SOURCE_DIR}/tests/add_tests.cmake"
        BYPRODUCTS "${generated_file}"
        VERBATIM
    )

endmacro()

add_subdirectory(char-tests)
add_subdirectory(non-char-tests)
