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

endmacro()

add_subdirectory(char-tests)
add_subdirectory(non-char-tests)
