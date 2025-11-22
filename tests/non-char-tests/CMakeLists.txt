# Copyright 2024-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

set(non_char_test_files
    main.cpp
    operators/basic.cpp
    operators/epsilon.cpp
    operators/not.cpp
    parsers/all_of_parser.cpp
    parsers/any_of_parser.cpp
    parsers/anything_parser.cpp
    parsers/epsilon_parser.cpp
    parsers/none_of_parser.cpp
    types/result.cpp
)

tok3n_add_test_executable(int_tests int VALUE_TYPE_INT
    ${non_char_test_files}
)
target_sources(int_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    samples.hpp
)

tok3n_add_test_executable(enum_tests enum VALUE_TYPE_ENUM
    ${non_char_test_files}
)
target_sources(enum_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    samples.hpp
)

tok3n_add_test_executable(structural_tests structural VALUE_TYPE_STRUCTURAL
    ${non_char_test_files}
)
target_sources(structural_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    samples.hpp
)

tok3n_add_test_executable(structural_op_equals_tests structural_op_equals VALUE_TYPE_STRUCTURAL_OP_EQUALS
    ${non_char_test_files}
)
target_sources(structural_op_equals_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    samples.hpp
)
