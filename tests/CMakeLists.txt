add_subdirectory(external/boostorg/preprocessor)

add_subdirectory(framework)
add_subdirectory(common)

macro(tok3n_add_test_executable target assembly_name value_type_pp_definition)

    add_executable("_${target}" ${ARGN})

    target_compile_definitions("_${target}" PRIVATE ${value_type_pp_definition})

    target_include_directories("_${target}" PRIVATE .)
    target_link_libraries("_${target}" PRIVATE common)
    target_precompile_headers("_${target}" PRIVATE samples.h)

    tok3n_configure_target("_${target}" PRIVATE)
    tok3n_configure_ide("_${target}")

    set_target_properties("_${target}"
        PROPERTIES
            FOLDER tests
    )

    tok3n_discover_tests(${target} ${assembly_name})

    set_target_properties(${target}
        PROPERTIES
            FOLDER tests/_generated
    )

endmacro()

macro(tok3n_discover_tests target assembly_name)

    add_custom_target("${target}" ALL)
    add_dependencies("${target}" "_${target}")

    set(generated_file "${CMAKE_CURRENT_BINARY_DIR}/${target}.add_tests.cmake")

    add_custom_command(
        TARGET "${target}" POST_BUILD
        COMMAND "_${target}" list "${generated_file}"
        COMMAND "${CMAKE_COMMAND}"
            -D "ASSEMBLY_NAME=${assembly_name}"
            -D "TEST_TARGET=${target}_"
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${CMAKE_SOURCE_DIR}/tests/add_tests.cmake"
        BYPRODUCTS "${generated_file}"
        VERBATIM
    )

endmacro()

add_subdirectory(char-tests)
add_subdirectory(non-char-tests)
