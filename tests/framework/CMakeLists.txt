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

    string(REGEX REPLACE "[\\\\\\/:]" "_" discovery "_discovery_${CMAKE_CURRENT_BINARY_DIR}")
    if(NOT TARGET ${discovery})
        add_custom_target(${discovery} ALL)
        set_target_properties(${discovery}
            PROPERTIES
                FOLDER tests/_generated
        )
    endif()

    add_custom_target(${generator} ALL)
    add_dependencies(${generator} ${runner})
    add_dependencies(${discovery} ${generator})

    set(generated_file "${CMAKE_CURRENT_BINARY_DIR}/${generator}.list_of_tests.cmake")

    add_custom_command(
        TARGET ${generator} POST_BUILD
        COMMAND ${runner} list ${generated_file}
        COMMAND ${CMAKE_COMMAND}
            -D "ASSEMBLY_NAME=${assembly_name}"
            -D "TEST_TARGET=${runner}"
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${CMAKE_SOURCE_DIR}/tests/discover_tests.cmake"
        BYPRODUCTS ${generated_file}
        VERBATIM
    )

    add_custom_command(
        TARGET ${discovery} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -D "TEST_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}"
            -D "LIST_OF_TESTS_FILE=${generated_file}"
            -P "${CMAKE_SOURCE_DIR}/tests/include_tests.cmake"
        VERBATIM
    )

endmacro()
