#pragma once
#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS()

namespace samples::basic
{

	using OC1 = OneChar<"abc">;     constexpr OC1 oc1;
	using OC2 = OneChar<"bcd">;     constexpr OC2 oc2;
	using OC3 = OneChar<"xyz">;     constexpr OC3 oc3;
	using NC1 = NotChar<"abc">;     constexpr NC1 nc1;
	using NC2 = NotChar<"bcd">;     constexpr NC2 nc2;
	using NC3 = NotChar<"xyz">;     constexpr NC3 nc3;
	using L1  = Literal<"literal">; constexpr L1  l1;
	using L2  = Literal<"ly">;      constexpr L2  l2;
	using L3  = Literal<"test">;    constexpr L3  l3;

	using OC4 = OneChar<"cd">; constexpr OC4 oc4;
	using NC4 = NotChar<"cd">; constexpr NC4 nc4;
	using NC5 = NotChar<"z">;  constexpr NC5 nc5;
	using L4  = Literal<"ab">; constexpr L4  l4;

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

namespace traits::compound
{

	template <template <Parser...> class CompoundParser>
	struct constructible
	{
		template <class... Ps>
		static constexpr bool from = requires { typename CompoundParser<Ps...>; };
	};

}

namespace samples::all
{

	using namespace basic;

	using Cho1 = Choice<L4, NC4>;      constexpr Cho1 cho1;
	using Cho2 = Choice<NC4, L4>;      constexpr Cho2 cho2;
	using Cho3 = Choice<L4, OC4, NC5>; constexpr Cho3 cho3;
	using Cho4 = Choice<NC5, L4, OC4>; constexpr Cho4 cho4;

	using Seq1 = Sequence<L4, NC4>;      constexpr Seq1 seq1;
	using Seq2 = Sequence<NC4, L4>;      constexpr Seq2 seq2;
	using Seq3 = Sequence<L4, OC4, NC5>; constexpr Seq3 seq3;
	using Seq4 = Sequence<NC5, L4, OC4>; constexpr Seq4 seq4;

}

TOK3N_END_NAMESPACE_TESTS()
