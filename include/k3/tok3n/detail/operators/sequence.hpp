// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_OPERATORS_SEQUENCE_HPP
#define K3_TOK3N_DETAIL_OPERATORS_SEQUENCE_HPP

#include <k3/tok3n/detail/parsers/all_of.hpp>
#include <k3/tok3n/detail/parsers/sequence.hpp>

namespace k3::tok3n::detail {

namespace impl {

template <static_array lhs, static_array rhs>
requires (decltype(like_static_arrays(lhs, rhs))::value)
consteval auto sequence_operator(all_of_parser<lhs>, all_of_parser<rhs>) // "ab" >> "cd" == "abcd"
{
	return all_of_parser<lhs + rhs>{};
}

template <parser... P1s, parser... P2s>
requires parser_compatible_with<sequence_parser<P1s...>, sequence_parser<P2s...>>
consteval auto sequence_operator(sequence_parser<P1s...>, sequence_parser<P2s...>) // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)
{
	return sequence_parser<P1s..., P2s...>{};
}

template <parser P2, parser_compatible_with<P2>... P1s>
consteval auto sequence_operator(sequence_parser<P1s...>, P2) // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)
{
	return sequence_parser<P1s..., P2>{};
}

template <parser P1, parser_compatible_with<P1>... P2s>
consteval auto sequence_operator(P1, sequence_parser<P2s...>) // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)
{
	return sequence_parser<P1, P2s...>{};
}

template <parser P1, parser_compatible_with<P1> P2>
consteval auto sequence_operator(P1, P2) // default
{
	return sequence_parser<P1, P2>{};
}

} // namespace impl

template <parser P1, parser_compatible_with<P1> P2>
constexpr auto operator>>(P1, P2)
{
	return impl::sequence_operator(P1{}, P2{});
}

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_OPERATORS_SEQUENCE_HPP
