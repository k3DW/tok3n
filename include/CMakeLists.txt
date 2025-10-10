# Copyright 2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(k3_tok3n INTERFACE)
add_library(k3::tok3n ALIAS k3_tok3n)

target_sources(k3_tok3n INTERFACE FILE_SET headers TYPE HEADERS FILES
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/basic.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/modifiers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/operators.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/parsers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/apply_invoke.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/call.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/compound.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/cpo.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/filter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/function_objects.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifier.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/result.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/set_operations.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/span.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/static_array.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/substitution.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/type_traits.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/aliases/apply_filter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/aliases/apply_into.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/aliases/apply_map.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/aliases/constant.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/aliases/defaulted.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/aliases/into.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/apply_filter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/apply_into.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/apply.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/complete.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/constant.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/defaulted.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/delimit_keep.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/delimit.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/exactly.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/filter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/ignore.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/into.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/join.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/map.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/multi.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/name.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/modifiers/sub.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/choice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/epsilon.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/maybe.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/modifier.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/not.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/one_or_more.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/sequence.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/operators/zero_or_more.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_basic.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_choice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_complete.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_custom.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_delimit.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_epsilon.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_exactly.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_maybe.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_named.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_one_or_more.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_sequence.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/optimizations/join_zero_or_more.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/all_of.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/any_of.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/anything.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/basic_base.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/choice.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/complete.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/custom.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/delimit.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/epsilon.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/exactly.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/filter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/ignore.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/join.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/map.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/maybe.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/named.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/none_of.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/one_or_more.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/sequence.hpp
    ${CMAKE_CURRENT_LIST_DIR}/k3/tok3n/detail/parsers/zero_or_more.hpp
)

target_include_directories(k3_tok3n INTERFACE .)

tok3n_configure_source_group(k3_tok3n)
