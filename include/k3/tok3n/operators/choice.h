#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>
#include <k3/tok3n/parsers/compound/Choice.h>

namespace k3::tok3n::operators_impl {

template <const auto& op, StaticArray str1, StaticArray str2>
requires LikeStaticArrays<str1, str2>
consteval auto merged_with()
{
	constexpr auto size = []
	{
		std::vector<typename decltype(str1)::value_type> s;
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
consteval auto choice(NoneOf<arr>, NoneOf<arr>) // (P | P) == P
{
	return NoneOf<arr>{};
}

template <StaticArray arr>
consteval auto choice(AnyOf<arr>, NoneOf<arr>) // Anything
{
	return NoneOf<arr.create_empty_with_size<0>>{};
}

template <StaticArray arr>
consteval auto choice(NoneOf<arr>, AnyOf<arr>) // Anything
{
	return NoneOf<arr.create_empty_with_size<0>>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(AnyOf<lhs>, AnyOf<rhs>) //  "ab" |  "bc" == "abc"    <- set_union
{
	return AnyOf<merged_with<std::ranges::set_union, lhs, rhs>()>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(NoneOf<lhs>, NoneOf<rhs>) // !"ab" | !"bc" == "b"      <- set_intersection
{
	return NoneOf<merged_with<std::ranges::set_intersection, lhs, rhs>()>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(AnyOf<lhs>, NoneOf<rhs>) //  "ab" | !"bc" == "c"      <- set_difference
{
	return NoneOf<merged_with<std::ranges::set_difference, rhs, lhs>()>{};
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
consteval auto choice(NoneOf<lhs>, AnyOf<rhs>) // !"ab" |  "bc" == "a"      <- set_difference
{
	return NoneOf<merged_with<std::ranges::set_difference, lhs, rhs>()>{};
}

template <Parser... P1s, Parser... P2s>
requires ParserCompatibleWith<Choice<P1s...>, Choice<P2s...>>
consteval auto choice(Choice<P1s...>, Choice<P2s...>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
{
	return Choice<P1s..., P2s...>{};
}

template <Parser... Ps>
consteval auto choice(Choice<Ps...>, Choice<Ps...>) // (P | P) == P
{
	return Choice<Ps...>{};
}

template <Parser P2, ParserCompatibleWith<P2>... P1s>
consteval auto choice(Choice<P1s...>, P2) // (P1 | P2) | P3 == (P1 | P2 | P3)
{
	return Choice<P1s..., P2>{};
}

template <Parser P1, ParserCompatibleWith<P1>... P2s>
consteval auto choice(P1, Choice<P2s...>) // P1 | (P2 | P3) == (P1 | P2 | P3)
{
	return Choice<P1, P2s...>{};
}

template <Parser P1, ParserCompatibleWith<P1> P2>
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

template <Parser P1, ParserCompatibleWith<P1> P2>
requires std::same_as<typename P1::result_type, typename P2::result_type>
consteval auto operator|(P1, P2)
{
	return operators_impl::choice(P1{}, P2{});
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator|;

} // namespace k3::tok3n::operators
