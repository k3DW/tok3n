#pragma once
#include <k3/tok3n/parsers/basic/OneChar.h>
#include <k3/tok3n/parsers/basic/NotChar.h>
#include <k3/tok3n/parsers/compound/Choice.h>

TOK3N_BEGIN_NAMESPACE(detail::operators)

template <const auto& op, StaticString str1, StaticString str2>
consteval auto merged_with()
{
	constexpr auto size = []
	{
		std::string s;
		s.reserve(str1.size() + str2.size());
		op(str1, str2, std::back_inserter(s));
		return s.size();
	};

	StaticString<size()> str;
	op(str1, str2, str.begin());
	return str;
}

template <StaticString str>
consteval auto choice(OneChar<str>, OneChar<str>) // (P | P) == P
{
	return OneChar<str>{};
}

template <StaticString str>
consteval auto choice(NotChar<str>, NotChar<str>) // (P | P) == P
{
	return NotChar<str>{};
}

template <StaticString str>
consteval auto choice(OneChar<str>, NotChar<str>) // Every char
{
	return NotChar<"">{};
}

template <StaticString str>
consteval auto choice(NotChar<str>, OneChar<str>) // Every char
{
	return NotChar<"">{};
}

template <StaticString lhs, StaticString rhs>
consteval auto choice(OneChar<lhs>, OneChar<rhs>) //  "ab" |  "bc" == "abc"    <- set_union
{
	return OneChar<merged_with<std::ranges::set_union, lhs, rhs>()>{};
}

template <StaticString lhs, StaticString rhs>
consteval auto choice(NotChar<lhs>, NotChar<rhs>) // !"ab" | !"bc" == "b"      <- set_intersection
{
	return NotChar<merged_with<std::ranges::set_intersection, lhs, rhs>()>{};
}

template <StaticString lhs, StaticString rhs>
consteval auto choice(OneChar<lhs>, NotChar<rhs>) //  "ab" | !"bc" == "c"      <- set_difference
{
	return NotChar<merged_with<std::ranges::set_difference, rhs, lhs>()>{};
}

template <StaticString lhs, StaticString rhs>
consteval auto choice(NotChar<lhs>, OneChar<rhs>) // !"ab" |  "bc" == "a"      <- set_difference
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

TOK3N_END_NAMESPACE(detail::operators)

TOK3N_BEGIN_NAMESPACE(inline operators)

template <Parser P1, Parser P2>
requires std::same_as<typename P1::result_type, typename P2::result_type>
consteval auto operator|(P1, P2)
{
	return detail::operators::choice(P1{}, P2{});
}

TOK3N_END_NAMESPACE(inline operators)
