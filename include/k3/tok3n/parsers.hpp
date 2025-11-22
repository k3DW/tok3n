// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_PARSERS_HPP
#define K3_TOK3N_PARSERS_HPP

#include <k3/tok3n/detail/aliases/apply_filter.hpp>
#include <k3/tok3n/detail/aliases/apply_into.hpp>
#include <k3/tok3n/detail/aliases/apply_map.hpp>
#include <k3/tok3n/detail/aliases/constant.hpp>
#include <k3/tok3n/detail/aliases/defaulted.hpp>
#include <k3/tok3n/detail/aliases/into.hpp>

#include <k3/tok3n/detail/optimizations/join_basic.hpp>
#include <k3/tok3n/detail/optimizations/join_choice.hpp>
#include <k3/tok3n/detail/optimizations/join_complete.hpp>
#include <k3/tok3n/detail/optimizations/join_custom.hpp>
#include <k3/tok3n/detail/optimizations/join_delimit.hpp>
#include <k3/tok3n/detail/optimizations/join_epsilon.hpp>
#include <k3/tok3n/detail/optimizations/join_exactly.hpp>
#include <k3/tok3n/detail/optimizations/join_maybe.hpp>
#include <k3/tok3n/detail/optimizations/join_named.hpp>
#include <k3/tok3n/detail/optimizations/join_one_or_more.hpp>
#include <k3/tok3n/detail/optimizations/join_sequence.hpp>
#include <k3/tok3n/detail/optimizations/join_zero_or_more.hpp>

#include <k3/tok3n/detail/parsers/all_of.hpp>
#include <k3/tok3n/detail/parsers/any_of.hpp>
#include <k3/tok3n/detail/parsers/anything.hpp>
#include <k3/tok3n/detail/parsers/choice.hpp>
#include <k3/tok3n/detail/parsers/complete.hpp>
#include <k3/tok3n/detail/parsers/custom.hpp>
#include <k3/tok3n/detail/parsers/delimit.hpp>
#include <k3/tok3n/detail/parsers/epsilon.hpp>
#include <k3/tok3n/detail/parsers/exactly.hpp>
#include <k3/tok3n/detail/parsers/filter.hpp>
#include <k3/tok3n/detail/parsers/ignore.hpp>
#include <k3/tok3n/detail/parsers/join.hpp>
#include <k3/tok3n/detail/parsers/map.hpp>
#include <k3/tok3n/detail/parsers/maybe.hpp>
#include <k3/tok3n/detail/parsers/named.hpp>
#include <k3/tok3n/detail/parsers/none_of.hpp>
#include <k3/tok3n/detail/parsers/one_or_more.hpp>
#include <k3/tok3n/detail/parsers/sequence.hpp>
#include <k3/tok3n/detail/parsers/zero_or_more.hpp>

namespace k3::tok3n {

using ::k3::tok3n::detail::custom_parser;

} // namespace k3::tok3n

#endif // K3_TOK3N_PARSERS_HPP
