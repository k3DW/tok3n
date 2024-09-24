file(GLOB_RECURSE non_char_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)



add_executable(int_tests
    ${non_char_test_files}
)

tok3n_configure_ide(int_tests)
tok3n_configure_test_target(int_tests VALUE_TYPE_INT)



add_executable(enum_tests
    ${non_char_test_files}
)

tok3n_configure_ide(enum_tests)
tok3n_configure_test_target(enum_tests VALUE_TYPE_ENUM)



add_executable(structural_tests
    ${non_char_test_files}
)

tok3n_configure_ide(structural_tests)
tok3n_configure_test_target(structural_tests VALUE_TYPE_STRUCTURAL)



add_executable(structural_op_equals_tests
    ${non_char_test_files}
)

tok3n_configure_ide(structural_op_equals_tests)
tok3n_configure_test_target(structural_op_equals_tests VALUE_TYPE_STRUCTURAL_OP_EQUALS)
