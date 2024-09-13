#pragma once
#include <k3/tok3n/detail/set_operations.h>
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>
#include <k3/tok3n/parsers/compound/Choice.h>

namespace k3::tok3n::detail {

namespace impl {

template <static_array arr>
consteval auto choice_operator(AnyOf<arr>, AnyOf<arr>)   // (P | P) == P
{
	return AnyOf<arr>{};
}

template <static_array arr>
consteval auto choice_operator(NoneOf<arr>, NoneOf<arr>) // (P | P) == P
{
	return NoneOf<arr>{};
}

template <static_array arr>
consteval auto choice_operator(AnyOf<arr>, NoneOf<arr>) // Anything
{
	return NoneOf<arr.template create_empty_with_size<0>()>{};
}

template <static_array arr>
consteval auto choice_operator(NoneOf<arr>, AnyOf<arr>) // Anything
{
	return NoneOf<arr.template create_empty_with_size<0>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(AnyOf<lhs>, AnyOf<rhs>)   //  "ab" |  "bc" == "abc"    <- set_union
{
	return AnyOf<set_union<lhs, rhs>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(NoneOf<lhs>, NoneOf<rhs>) // !"ab" | !"bc" == "b"      <- set_intersection
{
	return NoneOf<set_intersection<lhs, rhs>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(AnyOf<lhs>, NoneOf<rhs>)  //  "ab" | !"bc" == "c"      <- set_difference
{
	return NoneOf<set_difference_right<lhs, rhs>()>{};
}

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto choice_operator(NoneOf<lhs>, AnyOf<rhs>)  // !"ab" |  "bc" == "a"      <- set_difference
{
	return NoneOf<set_difference_left<lhs, rhs>()>{};
}

template <parser... P1s, parser... P2s>
requires parser_compatible_with<Choice<P1s...>, Choice<P2s...>>
consteval auto choice_operator(Choice<P1s...>, Choice<P2s...>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
{
	return Choice<P1s..., P2s...>{};
}

template <parser... Ps>
consteval auto choice_operator(Choice<Ps...>, Choice<Ps...>) // (P | P) == P
{
	return Choice<Ps...>{};
}

template <parser P2, parser_compatible_with<P2>... P1s>
consteval auto choice_operator(Choice<P1s...>, P2) // (P1 | P2) | P3 == (P1 | P2 | P3)
{
	return Choice<P1s..., P2>{};
}

template <parser P1, parser_compatible_with<P1>... P2s>
consteval auto choice_operator(P1, Choice<P2s...>) // P1 | (P2 | P3) == (P1 | P2 | P3)
{
	return Choice<P1, P2s...>{};
}

template <parser P1, parser_compatible_with<P1> P2>
consteval auto choice_operator(P1, P2) // default
{
	return Choice<P1, P2>{};
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
