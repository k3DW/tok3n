# Copyright 2024-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

set(non_char_test_files
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/basic.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/epsilon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/not.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/all_of_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/any_of_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/anything_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/epsilon_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/none_of_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/types/result.cpp
)

tok3n_add_test_executable(int_tests int VALUE_TYPE_INT
    ${non_char_test_files}
)
target_sources(int_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/samples.hpp
)

tok3n_add_test_executable(enum_tests enum VALUE_TYPE_ENUM
    ${non_char_test_files}
)
target_sources(enum_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/samples.hpp
)

tok3n_add_test_executable(structural_tests structural VALUE_TYPE_STRUCTURAL
    ${non_char_test_files}
)
target_sources(structural_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/samples.hpp
)

tok3n_add_test_executable(structural_op_equals_tests structural_op_equals VALUE_TYPE_STRUCTURAL_OP_EQUALS
    ${non_char_test_files}
)
target_sources(structural_op_equals_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/samples.hpp
)
