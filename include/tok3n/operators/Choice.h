#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE()

// OneChar
namespace detail::choice
{

	template <static_string lhs, static_string rhs>
	consteval auto onechar_onechar(OneChar<lhs>, OneChar<rhs>)
	{
		constexpr std::size_t count = []() consteval -> std::size_t
		{
			std::string str;
			std::ranges::set_union(rhs, lhs, std::back_inserter(str));
			return str.size();
		}();

		constexpr static_string<count> get_merged = []() consteval -> static_string<count>
		{
			static_string<count> str;
			std::ranges::set_union(rhs, lhs, str.begin());
			return str;
		}();

		return OneChar<get_merged>{};
	}

}

// NotChar
namespace detail::choice
{

	template <static_string lhs, static_string rhs>
	consteval auto notchar_notchar(NotChar<lhs>, NotChar<rhs>)
	{
		if constexpr (lhs == rhs)
			return NotChar<lhs>{};
		else
		{
			constexpr std::size_t count = []() consteval -> std::size_t
			{
				std::string str;
				std::ranges::set_intersection(rhs, lhs, std::back_inserter(str));
				return str.size();
			}();
			
			if constexpr (count == 0)
				return OneChar<every_char>{};

			else
			{
				constexpr static_string<count> get_merged = []() consteval -> static_string<count>
				{
					static_string<count> str;
					std::ranges::set_intersection(rhs, lhs, str.begin());
					return str;
				}();

				return NotChar<get_merged>{};
			}
		}
	}

	template <static_string lhs, static_string rhs>
	consteval auto onechar_notchar(OneChar<lhs>, NotChar<rhs>)
	{
		if constexpr (lhs == rhs)
			return OneChar<every_char>{};

		else
		{

			constexpr std::size_t count = []() consteval -> std::size_t
			{
				std::string str;
				std::ranges::set_difference(rhs, lhs, std::back_inserter(str));
				return str.size();
			}();

			constexpr static_string<count> get_merged = []() consteval -> static_string<count>
			{
				static_string<count> str;
				std::ranges::set_difference(rhs, lhs, str.begin());
				return str;
			}();

			return NotChar<get_merged>{};

		}
	}

}

// Choice
namespace detail::choice
{

	template <Parser... Ps, Parser... Qs>
	consteval auto choice_choice(Choice<Ps...>, Choice<Qs...>)
	{
		return Choice<Ps..., Qs...>{};
	}

	template <Parser... Ps, Parser P>
	consteval auto choice_parser(Choice<Ps...>, P)
	{
		return Choice<Ps..., P>{};
	}

	template <Parser P, Parser... Ps>
	consteval auto parser_choice(P, Choice<Ps...>)
	{
		return Choice<P, Ps...>{};
	}

}

template <Parser P1, Parser P2>
requires std::same_as<typename P1::result_type, typename P2::result_type>
constexpr auto operator|(P1, P2)
{
	using namespace detail::choice;

	if constexpr (std::same_as<std::remove_cvref_t<P1>, std::remove_cvref_t<P2>>) // (P | P) == P
		return P1{};

	else if constexpr (IsOneChar<P1> && IsOneChar<P2>) // "ab" | "bc" == "abc"    <- set_union
		return onechar_onechar(P1{}, P2{});

	else if constexpr (IsNotChar<P1> && IsNotChar<P2>) // !"ab" | !"bc" == "b"    <- set_intersection
		return notchar_notchar(P1{}, P2{});
	else if constexpr (IsOneChar<P1> && IsNotChar<P2>)
		return onechar_notchar(P1{}, P2{});
	else if constexpr (IsNotChar<P1> && IsOneChar<P2>)
		return onechar_notchar(P2{}, P1{});

	else if constexpr (IsChoice<P1> && IsChoice<P2>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
		return choice_choice(P1{}, P2{});
	else if constexpr (IsChoice<P1>)                 // (P1 | P2) | P3 == (P1 | P2 | P3)
		return choice_parser(P1{}, P2{});
	else if constexpr (IsChoice<P2>)                 // P1 | (P2 | P3) == (P1 | P2 | P3)
		return parser_choice(P1{}, P2{});

	else
		return Choice<P1, P2>{};
}

TOK3N_END_NAMESPACE()
