#pragma once
#include <k3/tok3n/parsers/basic/AllOf.h>
#include <k3/tok3n/parsers/compound/Sequence.h>

namespace k3::tok3n::operators_impl {

template <k3::tok3n::detail::static_array lhs, k3::tok3n::detail::static_array rhs>
requires decltype(detail::like_static_arrays(lhs, rhs))::value
consteval auto sequence(AllOf<lhs>, AllOf<rhs>) { return AllOf<lhs + rhs>{}; } // "ab" >> "cd" == "abcd"

template <k3::tok3n::detail::parser... P1s, k3::tok3n::detail::parser... P2s>
requires k3::tok3n::detail::parser_compatible_with<Sequence<P1s...>, Sequence<P2s...>>
consteval auto sequence(Sequence<P1s...>, Sequence<P2s...>) { return Sequence<P1s..., P2s...>{}; } // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)

template <k3::tok3n::detail::parser P2, k3::tok3n::detail::parser_compatible_with<P2>... P1s>
consteval auto sequence(Sequence<P1s...>, P2) { return Sequence<P1s..., P2>{}; } // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)

template <k3::tok3n::detail::parser P1, k3::tok3n::detail::parser_compatible_with<P1>... P2s>
consteval auto sequence(P1, Sequence<P2s...>) { return Sequence<P1, P2s...>{}; } // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)

template <k3::tok3n::detail::parser P1, k3::tok3n::detail::parser_compatible_with<P1> P2>
consteval auto sequence(P1, P2) { return Sequence<P1, P2>{}; } // default

} // namespace k3::tok3n::operators_impl

namespace k3::tok3n {

template <k3::tok3n::detail::parser P1, k3::tok3n::detail::parser_compatible_with<P1> P2>
constexpr auto operator>>(P1, P2)
{
	return operators_impl::sequence(P1{}, P2{});
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator>>;

} // namespace k3::tok3n::operators
