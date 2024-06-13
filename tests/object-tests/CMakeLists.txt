file(GLOB_RECURSE object_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)

tok3n_configure_ide("${object_test_files}")



add_executable(structural_tests
    ${object_test_files}
)

tok3n_configure_test_target(structural_tests VALUE_TYPE_STRUCTURAL)



add_executable(structural_op_equals_tests
    ${object_test_files}
)

tok3n_configure_test_target(structural_op_equals_tests VALUE_TYPE_STRUCTURAL_OP_EQUALS)
