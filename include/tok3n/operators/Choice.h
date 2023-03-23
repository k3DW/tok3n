#pragma once
#include <tok3n/parsers/basic/OneChar.h>
#include <tok3n/parsers/basic/NotChar.h>
#include <tok3n/parsers/compound/Choice.h>

TOK3N_BEGIN_NAMESPACE()

namespace detail::Choice_operator
{

	template <static_string lhs, static_string rhs>
	consteval auto OneChar_and_OneChar(OneChar<lhs>, OneChar<rhs>)
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

	template <static_string lhs, static_string rhs>
	consteval auto NotChar_and_NotChar(NotChar<lhs>, NotChar<rhs>)
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
	consteval auto OneChar_and_NotChar(OneChar<lhs>, NotChar<rhs>)
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

	template <Parser... Ps, Parser... Qs>
	consteval auto Choice_and_Choice(Choice<Ps...>, Choice<Qs...>)
	{
		return Choice<Ps..., Qs...>{};
	}

	template <Parser... Ps, Parser P>
	consteval auto Choice_and_anything(Choice<Ps...>, P)
	{
		return Choice<Ps..., P>{};
	}

	template <Parser P, Parser... Ps>
	consteval auto anything_and_Choice(P, Choice<Ps...>)
	{
		return Choice<P, Ps...>{};
	}

}

inline namespace operators
{

template <Parser P1, Parser P2>
requires std::same_as<typename P1::result_type, typename P2::result_type>
constexpr auto operator|(P1, P2)
{
	using namespace detail::Choice_operator;

	if constexpr (std::same_as<std::remove_cvref_t<P1>, std::remove_cvref_t<P2>>) // (P | P) == P
		return P1{};

	else if constexpr (IsOneChar<P1> && IsOneChar<P2>) //  "ab" |  "bc" == "abc"    <- set_union
		return OneChar_and_OneChar(P1{}, P2{});
	else if constexpr (IsNotChar<P1> && IsNotChar<P2>) // !"ab" | !"bc" == "b"      <- set_intersection
		return NotChar_and_NotChar(P1{}, P2{});
	else if constexpr (IsOneChar<P1> && IsNotChar<P2>) //  "ab" | !"bc" == "c"      <- set_difference
		return OneChar_and_NotChar(P1{}, P2{});
	else if constexpr (IsNotChar<P1> && IsOneChar<P2>) // !"ab" |  "bc" == "a"      <- set_difference
		return OneChar_and_NotChar(P2{}, P1{});

	else if constexpr (IsChoice<P1> && IsChoice<P2>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
		return Choice_and_Choice(P1{}, P2{});
	else if constexpr (IsChoice<P1>)                 // (P1 | P2) | P3 == (P1 | P2 | P3)
		return Choice_and_anything(P1{}, P2{});
	else if constexpr (IsChoice<P2>)                 // P1 | (P2 | P3) == (P1 | P2 | P3)
		return anything_and_Choice(P1{}, P2{});

	else
		return Choice<P1, P2>{};
}

}

TOK3N_END_NAMESPACE()
