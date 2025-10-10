# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

set(char_test_files
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/aliases/apply_filter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/aliases/apply_into.cpp
    ${CMAKE_CURRENT_LIST_DIR}/aliases/apply_map.cpp
    ${CMAKE_CURRENT_LIST_DIR}/aliases/constant.cpp
    ${CMAKE_CURRENT_LIST_DIR}/aliases/defaulted.cpp
    ${CMAKE_CURRENT_LIST_DIR}/aliases/into.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/apply_filter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/apply_into.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/apply.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/complete.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/constant.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/defaulted.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/delimit_keep.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/delimit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/exactly.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/filter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/ignore.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/into.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/join.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/map.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/multi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/name.cpp
    ${CMAKE_CURRENT_LIST_DIR}/modifiers/sub.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/basic.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/choice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/epsilon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/maybe.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/not.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/one_or_more.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/sequence.cpp
    ${CMAKE_CURRENT_LIST_DIR}/operators/zero_or_more.cpp
    ${CMAKE_CURRENT_LIST_DIR}/optimizations/join_exactly_basic_optimization.cpp
    ${CMAKE_CURRENT_LIST_DIR}/optimizations/join_maybe_basic_optimization.cpp
    ${CMAKE_CURRENT_LIST_DIR}/optimizations/join_one_or_more_basic_optimization.cpp
    ${CMAKE_CURRENT_LIST_DIR}/optimizations/join_zero_or_more_basic_optimization.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/all_of_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/any_of_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/anything_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/choice_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/complete_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/custom_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/delimit_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/epsilon_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/exactly_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/filter_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/ignore_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/join_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/map_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/maybe_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/named_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/none_of_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/one_or_more_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/sequence_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parsers/zero_or_more_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/types/result.cpp
)

tok3n_add_test_executable(char_tests char VALUE_TYPE_CHAR
    ${char_test_files}
)
target_sources(char_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/samples.hpp
)

tok3n_add_test_executable(wchar_t_tests wchar_t VALUE_TYPE_WCHAR_T
    ${char_test_files}
)
target_sources(wchar_t_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/samples.hpp
)
