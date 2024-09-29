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
    target_precompile_headers(${target_name} PRIVATE samples.h)

    tok3n_configure_source_group(${target_name})

    set_target_properties(${target_name}
        PROPERTIES
            FOLDER tests
    )

    if(TOK3N_DISCOVER_TESTS)
        tok3n_discover_tests(${target} ${assembly_name})
        set_target_properties(${target}
            PROPERTIES
                FOLDER tests/_generated
        )
    endif()

endmacro()

macro(tok3n_discover_tests target assembly_name)

    add_custom_target("${target}" ALL)
    add_dependencies("${target}" "${target}_")

    set(generated_file "${CMAKE_CURRENT_BINARY_DIR}/${target}.add_tests.cmake")

    add_custom_command(
        TARGET "${target}" POST_BUILD
        COMMAND "${target}_" list "${generated_file}"
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
