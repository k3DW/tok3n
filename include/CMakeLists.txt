# Copyright 2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(k3_tok3n INTERFACE)
add_library(k3::tok3n ALIAS k3_tok3n)

target_sources(k3_tok3n INTERFACE FILE_SET headers TYPE HEADERS FILES
    k3/tok3n.hpp
    k3/tok3n/basic.hpp
    k3/tok3n/modifiers.hpp
    k3/tok3n/operators.hpp
    k3/tok3n/parsers.hpp
    k3/tok3n/detail/apply_invoke.hpp
    k3/tok3n/detail/call.hpp
    k3/tok3n/detail/compound.hpp
    k3/tok3n/detail/cpo.hpp
    k3/tok3n/detail/filter.hpp
    k3/tok3n/detail/function_objects.hpp
    k3/tok3n/detail/modifier.hpp
    k3/tok3n/detail/parser.hpp
    k3/tok3n/detail/result.hpp
    k3/tok3n/detail/set_operations.hpp
    k3/tok3n/detail/span.hpp
    k3/tok3n/detail/static_array.hpp
    k3/tok3n/detail/substitution.hpp
    k3/tok3n/detail/type_traits.hpp
    k3/tok3n/detail/aliases/apply_filter.hpp
    k3/tok3n/detail/aliases/apply_into.hpp
    k3/tok3n/detail/aliases/apply_map.hpp
    k3/tok3n/detail/aliases/constant.hpp
    k3/tok3n/detail/aliases/defaulted.hpp
    k3/tok3n/detail/aliases/into.hpp
    k3/tok3n/detail/modifiers/apply_filter.hpp
    k3/tok3n/detail/modifiers/apply_into.hpp
    k3/tok3n/detail/modifiers/apply.hpp
    k3/tok3n/detail/modifiers/complete.hpp
    k3/tok3n/detail/modifiers/constant.hpp
    k3/tok3n/detail/modifiers/defaulted.hpp
    k3/tok3n/detail/modifiers/delimit_keep.hpp
    k3/tok3n/detail/modifiers/delimit.hpp
    k3/tok3n/detail/modifiers/exactly.hpp
    k3/tok3n/detail/modifiers/filter.hpp
    k3/tok3n/detail/modifiers/ignore.hpp
    k3/tok3n/detail/modifiers/into.hpp
    k3/tok3n/detail/modifiers/join.hpp
    k3/tok3n/detail/modifiers/map.hpp
    k3/tok3n/detail/modifiers/multi.hpp
    k3/tok3n/detail/modifiers/name.hpp
    k3/tok3n/detail/modifiers/sub.hpp
    k3/tok3n/detail/operators/choice.hpp
    k3/tok3n/detail/operators/epsilon.hpp
    k3/tok3n/detail/operators/maybe.hpp
    k3/tok3n/detail/operators/modifier.hpp
    k3/tok3n/detail/operators/not.hpp
    k3/tok3n/detail/operators/one_or_more.hpp
    k3/tok3n/detail/operators/sequence.hpp
    k3/tok3n/detail/operators/zero_or_more.hpp
    k3/tok3n/detail/optimizations/guaranteed_contiguous.hpp
    k3/tok3n/detail/optimizations/join_basic.hpp
    k3/tok3n/detail/optimizations/join_choice.hpp
    k3/tok3n/detail/optimizations/join_complete.hpp
    k3/tok3n/detail/optimizations/join_custom.hpp
    k3/tok3n/detail/optimizations/join_delimit.hpp
    k3/tok3n/detail/optimizations/join_epsilon.hpp
    k3/tok3n/detail/optimizations/join_exactly.hpp
    k3/tok3n/detail/optimizations/join_maybe.hpp
    k3/tok3n/detail/optimizations/join_named.hpp
    k3/tok3n/detail/optimizations/join_one_or_more.hpp
    k3/tok3n/detail/optimizations/join_sequence.hpp
    k3/tok3n/detail/optimizations/join_zero_or_more.hpp
    k3/tok3n/detail/parsers/all_of.hpp
    k3/tok3n/detail/parsers/any_of.hpp
    k3/tok3n/detail/parsers/anything.hpp
    k3/tok3n/detail/parsers/basic_base.hpp
    k3/tok3n/detail/parsers/choice.hpp
    k3/tok3n/detail/parsers/complete.hpp
    k3/tok3n/detail/parsers/custom.hpp
    k3/tok3n/detail/parsers/delimit.hpp
    k3/tok3n/detail/parsers/epsilon.hpp
    k3/tok3n/detail/parsers/exactly.hpp
    k3/tok3n/detail/parsers/filter.hpp
    k3/tok3n/detail/parsers/ignore.hpp
    k3/tok3n/detail/parsers/join.hpp
    k3/tok3n/detail/parsers/map.hpp
    k3/tok3n/detail/parsers/maybe.hpp
    k3/tok3n/detail/parsers/named.hpp
    k3/tok3n/detail/parsers/none_of.hpp
    k3/tok3n/detail/parsers/one_or_more.hpp
    k3/tok3n/detail/parsers/sequence.hpp
    k3/tok3n/detail/parsers/zero_or_more.hpp
)

target_include_directories(k3_tok3n INTERFACE .)
