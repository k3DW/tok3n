file(GLOB_RECURSE object_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)

tok3n_configure_ide("${object_test_files}")



add_executable(structural_tests
    ${object_test_files}
)

target_compile_definitions(structural_tests PRIVATE VALUE_TYPE_STRUCTURAL)

tok3n_configure_target(structural_tests PUBLIC)

target_include_directories(structural_tests PUBLIC ..)

target_link_libraries(structural_tests PUBLIC k3::tok3n)
target_link_libraries(structural_tests PUBLIC framework)
target_link_libraries(structural_tests PUBLIC Boost::preprocessor)

target_precompile_headers(structural_tests PRIVATE samples.h)



add_executable(structural_op_equals_tests
    ${object_test_files}
)

target_compile_definitions(structural_op_equals_tests PRIVATE VALUE_TYPE_STRUCTURAL_OP_EQUALS)

tok3n_configure_target(structural_op_equals_tests PUBLIC)

target_include_directories(structural_op_equals_tests PUBLIC ..)

target_link_libraries(structural_op_equals_tests PUBLIC k3::tok3n)
target_link_libraries(structural_op_equals_tests PUBLIC framework)
target_link_libraries(structural_op_equals_tests PUBLIC Boost::preprocessor)

target_precompile_headers(structural_op_equals_tests PRIVATE samples.h)



set_target_properties(structural_tests
    PROPERTIES
        FOLDER tests
)

set_target_properties(structural_op_equals_tests
    PROPERTIES
        FOLDER tests
)
