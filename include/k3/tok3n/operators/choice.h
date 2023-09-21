#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NotChar.h>
#include <k3/tok3n/parsers/compound/Choice.h>

namespace k3::tok3n::operators_impl {

template <const auto& op, StaticArray str1, StaticArray str2>
requires LikeStaticArrays<str1, str2>
consteval auto merged_with()
{
	constexpr auto size = []
	{
		std::string s;
		s.reserve(str1.size() + str2.size());
		op(str1, str2, std::back_inserter(s));
		return s.size();
	};

	auto str = str1.create_empty_with_size<size()>;
	op(str1, str2, str.begin());
	return str;
}

template <StaticArray arr>
consteval auto choice(AnyOf<arr>, AnyOf<arr>) // (P | P) == P
{
	return AnyOf<arr>{};
}

template <StaticArray arr>
consteval auto choice(NotChar<arr>, NotChar<arr>) // (P | P) == P
{
	return NotChar<arr>{};
}

template <StaticArray arr>
consteval auto choice(AnyOf<arr>, NotChar<arr>) // Anything
{
	return NotChar<arr.create_empty_with_size<0>>{};
}

template <StaticArray arr>
consteval auto choice(NotChar<arr>, AnyOf<arr>) // Anything
{
	return NotChar<arr.create_empty_with_size<0>>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(AnyOf<lhs>, AnyOf<rhs>) //  "ab" |  "bc" == "abc"    <- set_union
{
	return AnyOf<merged_with<std::ranges::set_union, lhs, rhs>()>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(NotChar<lhs>, NotChar<rhs>) // !"ab" | !"bc" == "b"      <- set_intersection
{
	return NotChar<merged_with<std::ranges::set_intersection, lhs, rhs>()>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(AnyOf<lhs>, NotChar<rhs>) //  "ab" | !"bc" == "c"      <- set_difference
{
	return NotChar<merged_with<std::ranges::set_difference, rhs, lhs>()>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(NotChar<lhs>, AnyOf<rhs>) // !"ab" |  "bc" == "a"      <- set_difference
{
	return NotChar<merged_with<std::ranges::set_difference, lhs, rhs>()>{};
}

template <Parser... P1s, Parser... P2s>
consteval auto choice(Choice<P1s...>, Choice<P2s...>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
{
	return Choice<P1s..., P2s...>{};
}

template <Parser... Ps>
consteval auto choice(Choice<Ps...>, Choice<Ps...>) // (P | P) == P
{
	return Choice<Ps...>{};
}

template <Parser... P1s, Parser P2>
consteval auto choice(Choice<P1s...>, P2) // (P1 | P2) | P3 == (P1 | P2 | P3)
{
	return Choice<P1s..., P2>{};
}

template <Parser P1, Parser... P2s>
consteval auto choice(P1, Choice<P2s...>) // P1 | (P2 | P3) == (P1 | P2 | P3)
{
	return Choice<P1, P2s...>{};
}

template <Parser P1, Parser P2>
consteval auto choice(P1, P2) // default
{
	return Choice<P1, P2>{};
}

template <Parser P>
consteval auto choice(P, P) // (P | P) == P
{
	return P{};
}

} // namespace k3::tok3n::operators_impl

namespace k3::tok3n {

template <Parser P1, Parser P2>
requires std::same_as<typename P1::result_type, typename P2::result_type>
consteval auto operator|(P1, P2)
{
	return operators_impl::choice(P1{}, P2{});
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator|;

} // namespace k3::tok3n::operators
