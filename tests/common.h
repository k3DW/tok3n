#pragma once
#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS()

namespace samples::basic
{

	constexpr auto oc1 = OneChar<"abc">{};
	constexpr auto oc2 = OneChar<"bcd">{};
	constexpr auto oc3 = OneChar<"xyz">{};
	constexpr auto nc1 = NotChar<"abc">{};
	constexpr auto nc2 = NotChar<"bcd">{};
	constexpr auto nc3 = NotChar<"xyz">{};
	constexpr auto l1 = Literal<"literal">{};
	constexpr auto l2 = Literal<"ly">{};
	constexpr auto l3 = Literal<"test">{};

}

namespace traits::basic
{

	template <template <static_string> class BasicParser>
	struct constructible
	{
		template <char c> static constexpr bool from_char = requires { typename BasicParser<c>; };
		
		template <class Seq> static constexpr bool from_all_chars =
			[]<int... Is>(std::integer_sequence<int, Is...>)
			{
				return (... && from_char<(char)Is>);
			}(Seq{});

		template <class Seq> static constexpr bool from_any_char =
			[]<int... Is>(std::integer_sequence<int, Is...>)
			{
				return (... || from_char<(char)Is>);
			}(Seq{});

		template <static_string str> static constexpr bool from = requires { typename BasicParser<str>; };
	};

}

TOK3N_END_NAMESPACE_TESTS()
