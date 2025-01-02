# Copyright 2024 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

file(GLOB_RECURSE non_char_test_files
     LIST_DIRECTORIES false
     "./*.hpp"
     "./*.cpp"
)

tok3n_add_test_executable(int_tests int VALUE_TYPE_INT
    ${non_char_test_files}
)

tok3n_add_test_executable(enum_tests enum VALUE_TYPE_ENUM
    ${non_char_test_files}
)

tok3n_add_test_executable(structural_tests structural VALUE_TYPE_STRUCTURAL
    ${non_char_test_files}
)

tok3n_add_test_executable(structural_op_equals_tests structural_op_equals VALUE_TYPE_STRUCTURAL_OP_EQUALS
    ${non_char_test_files}
)
