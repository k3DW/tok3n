file(GLOB_RECURSE framework_files
    LIST_DIRECTORIES false
        "*.h"
        "*.cpp"
)

add_library(framework
    ${framework_files}
)

tok3n_configure_source_group(framework)

target_include_directories(framework PUBLIC include)

target_link_libraries(framework PUBLIC tok3n_shared_settings)

target_precompile_headers(framework PUBLIC include/framework.h)

set_target_properties(framework
    PROPERTIES
        FOLDER tests
)

macro(tok3n_discover_tests runner generator assembly_name)

    add_custom_target(${generator} ALL)
    add_dependencies(${generator} ${runner})

    set(generated_file "${CMAKE_CURRENT_BINARY_DIR}/${generator}.add_tests.cmake")

    add_custom_command(
        TARGET ${generator} POST_BUILD
        COMMAND ${runner} list ${generated_file}
        COMMAND ${CMAKE_COMMAND}
            -D "ASSEMBLY_NAME=${assembly_name}"
            -D "TEST_TARGET=${runner}"
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${CMAKE_SOURCE_DIR}/tests/add_tests.cmake"
        BYPRODUCTS ${generated_file}
        VERBATIM
    )

endmacro()
