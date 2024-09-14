#pragma once
#include <k3/tok3n/detail/set_operations.h>
#include <k3/tok3n/detail/parsers/any_of.h>
#include <k3/tok3n/detail/parsers/none_of.h>
#include <k3/tok3n/detail/parsers/choice.h>

namespace k3::tok3n::detail {

namespace impl {

template <static_array arr>
consteval auto choice_operator(any_of_parser<arr>, any_of_parser<arr>)   // (P | P) == P
{
	return any_of_parser<arr>{};
}

template <static_array arr>
consteval auto choice_operator(none_of_parser<arr>, none_of_parser<arr>) // (P | P) == P
{
	return none_of_parser<arr>{};
}

template <static_array arr>
consteval auto choice_operator(any_of_parser<arr>, none_of_parser<arr>) // Anything
{
	return none_of_parser<arr.template create_empty_with_size<0>()>{};
}

template <static_array arr>
consteval auto choice_operator(none_of_parser<arr>, any_of_parser<arr>) // Anything
{
	return none_of_parser<arr.template create_empty_with_size<0>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(any_of_parser<lhs>, any_of_parser<rhs>)   //  "ab" |  "bc" == "abc"    <- set_union
{
	return any_of_parser<set_union<lhs, rhs>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(none_of_parser<lhs>, none_of_parser<rhs>) // !"ab" | !"bc" == "b"      <- set_intersection
{
	return none_of_parser<set_intersection<lhs, rhs>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(any_of_parser<lhs>, none_of_parser<rhs>)  //  "ab" | !"bc" == "c"      <- set_difference
{
	return none_of_parser<set_difference_right<lhs, rhs>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(none_of_parser<lhs>, any_of_parser<rhs>)  // !"ab" |  "bc" == "a"      <- set_difference
{
	return none_of_parser<set_difference_left<lhs, rhs>()>{};
}

template <parser... P1s, parser... P2s>
requires parser_compatible_with<choice_parser<P1s...>, choice_parser<P2s...>>
consteval auto choice_operator(choice_parser<P1s...>, choice_parser<P2s...>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
{
	return choice_parser<P1s..., P2s...>{};
}

template <parser... Ps>
consteval auto choice_operator(choice_parser<Ps...>, choice_parser<Ps...>) // (P | P) == P
{
	return choice_parser<Ps...>{};
}

template <parser P2, parser_compatible_with<P2>... P1s>
consteval auto choice_operator(choice_parser<P1s...>, P2) // (P1 | P2) | P3 == (P1 | P2 | P3)
{
	return choice_parser<P1s..., P2>{};
}

template <parser P1, parser_compatible_with<P1>... P2s>
consteval auto choice_operator(P1, choice_parser<P2s...>) // P1 | (P2 | P3) == (P1 | P2 | P3)
{
	return choice_parser<P1, P2s...>{};
}

template <parser P1, parser_compatible_with<P1> P2>
consteval auto choice_operator(P1, P2) // default
{
	return choice_parser<P1, P2>{};
}

template <parser P>
consteval auto choice_operator(P, P) // (P | P) == P
{
	return P{};
}

} // namespace impl

template <parser P1, parser_compatible_with<P1> P2>
constexpr auto operator|(P1, P2)
{
	return impl::choice_operator(P1{}, P2{});
}

} // namespace k3::tok3n::detail
