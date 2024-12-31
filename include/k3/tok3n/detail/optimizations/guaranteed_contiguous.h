// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parsers/all_of.h>
#include <k3/tok3n/detail/parsers/any_of.h>
#include <k3/tok3n/detail/parsers/anything.h>
#include <k3/tok3n/detail/parsers/choice.h>
#include <k3/tok3n/detail/parsers/complete.h>
#include <k3/tok3n/detail/parsers/custom.h>
#include <k3/tok3n/detail/parsers/delimit.h>
#include <k3/tok3n/detail/parsers/epsilon.h>
#include <k3/tok3n/detail/parsers/exactly.h>
#include <k3/tok3n/detail/parsers/filter.h>
#include <k3/tok3n/detail/parsers/ignore.h>
#include <k3/tok3n/detail/parsers/join.h>
#include <k3/tok3n/detail/parsers/map.h>
#include <k3/tok3n/detail/parsers/maybe.h>
#include <k3/tok3n/detail/parsers/named.h>
#include <k3/tok3n/detail/parsers/none_of.h>
#include <k3/tok3n/detail/parsers/one_or_more.h>
#include <k3/tok3n/detail/parsers/sequence.h>
#include <k3/tok3n/detail/parsers/zero_or_more.h>

namespace k3::tok3n::detail {

template <parser P>
inline constexpr bool is_guaranteed_contiguous_v = false;

template <static_array arr>
inline constexpr bool is_guaranteed_contiguous_v<all_of_parser<arr>> = true;
template <static_array arr>
inline constexpr bool is_guaranteed_contiguous_v<any_of_parser<arr>> = true;
template <static_array arr>
inline constexpr bool is_guaranteed_contiguous_v<none_of_parser<arr>> = true;

template <class ValueType>
inline constexpr bool is_guaranteed_contiguous_v<anything_parser<ValueType>> = true;
template <class ValueType>
inline constexpr bool is_guaranteed_contiguous_v<epsilon_parser<ValueType>> = true;

template <parser P>
inline constexpr bool is_guaranteed_contiguous_v<ignore_parser<P>> = false;
template <parser P, is_integral_constant FunctionValue>
inline constexpr bool is_guaranteed_contiguous_v<filter_parser<P, FunctionValue>> = false;
template <parser P, is_integral_constant FunctionValue>
inline constexpr bool is_guaranteed_contiguous_v<map_parser<P, FunctionValue>> = false;

template <parser P, parser_compatible_with<P>... Ps>
inline constexpr bool is_guaranteed_contiguous_v<choice_parser<P, Ps...>> = (is_guaranteed_contiguous_v<P> and ... and is_guaranteed_contiguous_v<Ps>);
template <parser P, parser_compatible_with<P>... Ps>
inline constexpr bool is_guaranteed_contiguous_v<sequence_parser<P, Ps...>> = (is_guaranteed_contiguous_v<P> and ... and is_guaranteed_contiguous_v<Ps>);

template <parser P>
inline constexpr bool is_guaranteed_contiguous_v<join_parser<P>> = is_guaranteed_contiguous_v<P>;
template <parser P>
inline constexpr bool is_guaranteed_contiguous_v<complete_parser<P>> = is_guaranteed_contiguous_v<P>;
template <parser P, static_array str>
inline constexpr bool is_guaranteed_contiguous_v<named_parser<P, str>> = is_guaranteed_contiguous_v<P>;

template <parser P, parser_compatible_with<P> D>
inline constexpr bool is_guaranteed_contiguous_v<delimit_parser<P, D>> = is_guaranteed_contiguous_v<P> and is_guaranteed_contiguous_v<D>;
template <parser P, integral_constant_of<std::size_t> N>
inline constexpr bool is_guaranteed_contiguous_v<exactly_parser<P, N>> = is_guaranteed_contiguous_v<P>;
template <parser P>
inline constexpr bool is_guaranteed_contiguous_v<maybe_parser<P>> = is_guaranteed_contiguous_v<P>;
template <parser P>
inline constexpr bool is_guaranteed_contiguous_v<one_or_more_parser<P>> = is_guaranteed_contiguous_v<P>;
template <parser P>
inline constexpr bool is_guaranteed_contiguous_v<zero_or_more_parser<P>> = is_guaranteed_contiguous_v<P>;

template <class CRTP, class ValueType>
inline constexpr bool is_guaranteed_contiguous_v<custom_parser<CRTP, ValueType>> = is_guaranteed_contiguous_v<decltype(CRTP::get_parser())>;

template <class P>
concept guaranteed_contiguous = parser<P> and is_guaranteed_contiguous_v<P>;

} // namespace k3::tok3n::detail
