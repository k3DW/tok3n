# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

set(char_test_files
    main.cpp
    aliases/apply_filter.cpp
    aliases/apply_into.cpp
    aliases/apply_map.cpp
    aliases/constant.cpp
    aliases/defaulted.cpp
    aliases/into.cpp
    modifiers/apply_filter.cpp
    modifiers/apply_into.cpp
    modifiers/apply.cpp
    modifiers/complete.cpp
    modifiers/constant.cpp
    modifiers/defaulted.cpp
    modifiers/delimit_keep.cpp
    modifiers/delimit.cpp
    modifiers/exactly.cpp
    modifiers/filter.cpp
    modifiers/ignore.cpp
    modifiers/into.cpp
    modifiers/join.cpp
    modifiers/map.cpp
    modifiers/multi.cpp
    modifiers/name.cpp
    modifiers/sub.cpp
    operators/basic.cpp
    operators/choice.cpp
    operators/epsilon.cpp
    operators/maybe.cpp
    operators/not.cpp
    operators/one_or_more.cpp
    operators/sequence.cpp
    operators/zero_or_more.cpp
    optimizations/join_exactly_basic_optimization.cpp
    optimizations/join_maybe_basic_optimization.cpp
    optimizations/join_one_or_more_basic_optimization.cpp
    optimizations/join_zero_or_more_basic_optimization.cpp
    parsers/all_of_parser.cpp
    parsers/any_of_parser.cpp
    parsers/anything_parser.cpp
    parsers/choice_parser.cpp
    parsers/complete_parser.cpp
    parsers/custom_parser.cpp
    parsers/delimit_parser.cpp
    parsers/epsilon_parser.cpp
    parsers/exactly_parser.cpp
    parsers/filter_parser.cpp
    parsers/ignore_parser.cpp
    parsers/join_parser.cpp
    parsers/map_parser.cpp
    parsers/maybe_parser.cpp
    parsers/named_parser.cpp
    parsers/none_of_parser.cpp
    parsers/one_or_more_parser.cpp
    parsers/sequence_parser.cpp
    parsers/zero_or_more_parser.cpp
    types/result.cpp
)

tok3n_add_test_executable(char_tests char VALUE_TYPE_CHAR
    ${char_test_files}
)
target_sources(char_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    samples.hpp
)

tok3n_add_test_executable(wchar_t_tests wchar_t VALUE_TYPE_WCHAR_T
    ${char_test_files}
)
target_sources(wchar_t_tests PRIVATE FILE_SET headers TYPE HEADERS FILES
    samples.hpp
)
