#pragma once
#include <k3/tok3n/parsers/basic/AllOf.h>
#include <k3/tok3n/parsers/compound/Sequence.h>

namespace k3::tok3n::operators_impl {

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto sequence(AllOf<lhs>, AllOf<rhs>) { return AllOf<lhs + rhs>{}; } // "ab" >> "cd" == "abcd"

template <Parser... P1s, Parser... P2s>
requires ParserCompatibleWith<Sequence<P1s...>, Sequence<P2s...>>
consteval auto sequence(Sequence<P1s...>, Sequence<P2s...>) { return Sequence<P1s..., P2s...>{}; } // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)

template <Parser P2, ParserCompatibleWith<P2>... P1s>
consteval auto sequence(Sequence<P1s...>, P2) { return Sequence<P1s..., P2>{}; } // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)

template <Parser P1, ParserCompatibleWith<P1>... P2s>
consteval auto sequence(P1, Sequence<P2s...>) { return Sequence<P1, P2s...>{}; } // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)

template <Parser P1, ParserCompatibleWith<P1> P2>
consteval auto sequence(P1, P2) { return Sequence<P1, P2>{}; } // default

} // namespace k3::tok3n::operators_impl

namespace k3::tok3n {

template <Parser P1, ParserCompatibleWith<P1> P2>
constexpr auto operator>>(P1, P2)
{
	return operators_impl::sequence(P1{}, P2{});
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator>>;

} // namespace k3::tok3n::operators
