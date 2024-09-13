#pragma once
#include <k3/tok3n/parsers/basic/AllOf.h>
#include <k3/tok3n/parsers/compound/Sequence.h>

namespace k3::tok3n::detail {

namespace impl {

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
consteval auto sequence_operator(AllOf<lhs>, AllOf<rhs>) // "ab" >> "cd" == "abcd"
{
	return AllOf<lhs + rhs>{};
}

template <parser... P1s, parser... P2s>
requires parser_compatible_with<Sequence<P1s...>, Sequence<P2s...>>
consteval auto sequence_operator(Sequence<P1s...>, Sequence<P2s...>) // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)
{
	return Sequence<P1s..., P2s...>{};
}

template <parser P2, parser_compatible_with<P2>... P1s>
consteval auto sequence_operator(Sequence<P1s...>, P2) // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)
{
	return Sequence<P1s..., P2>{};
}

template <parser P1, parser_compatible_with<P1>... P2s>
consteval auto sequence_operator(P1, Sequence<P2s...>) // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)
{
	return Sequence<P1, P2s...>{};
}

template <parser P1, parser_compatible_with<P1> P2>
consteval auto sequence_operator(P1, P2) // default
{
	return Sequence<P1, P2>{};
}

} // namespace impl

template <parser P1, parser_compatible_with<P1> P2>
constexpr auto operator>>(P1, P2)
{
	return impl::sequence_operator(P1{}, P2{});
}

} // namespace k3::tok3n::detail
