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

	using QQ       = Literal<"??">;  constexpr QQ       qq;
	using ABC      = Literal<"abc">; constexpr ABC      abc;
	using Comma    = OneChar<",">;   constexpr Comma    comma;
	using SpaceDot = OneChar<" .">;  constexpr SpaceDot spacedot;

	static_assert(parser_equality_operator::validate(
		oc1, oc2, oc3, nc1, nc2, nc3, l1, l2, l3, oc4, nc4, nc5, l4,
		qq, abc, comma, spacedot
	), "operator==() and operator!=() are not implemented properly on Parser types");

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

namespace traits::repeat
{

	namespace Exactly
	{
		using k3::tok3n::Exactly;
		struct constructible
		{
			template <Parser P, std::size_t N>
			static constexpr bool from = requires { typename Exactly<P, N>; };
		};
	}

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

	namespace Sub1
	{
		using _1 = L1;
		using _2 = OC1;
		using _3 = Choice<L1, OC1>;
		using _4 = Sequence<L1, OC1>;
	}

	using May1 = Maybe<Sub1::_1>; constexpr May1 may1;
	using May2 = Maybe<Sub1::_2>; constexpr May2 may2;
	using May3 = Maybe<Sub1::_3>; constexpr May3 may3;
	using May4 = Maybe<Sub1::_4>; constexpr May4 may4;

	using Exa1 = Exactly<Sub1::_1, 3>; constexpr Exa1 exa1;
	using Exa2 = Exactly<Sub1::_2, 5>; constexpr Exa2 exa2;
	using Exa3 = Exactly<Sub1::_3, 4>; constexpr Exa3 exa3;
	using Exa4 = Exactly<Sub1::_4, 2>; constexpr Exa4 exa4;

	using Oom1 = OneOrMore<Sub1::_1>; constexpr Oom1 oom1;
	using Oom2 = OneOrMore<Sub1::_2>; constexpr Oom2 oom2;
	using Oom3 = OneOrMore<Sub1::_3>; constexpr Oom3 oom3;
	using Oom4 = OneOrMore<Sub1::_4>; constexpr Oom4 oom4;

	using Zom1 = ZeroOrMore<Sub1::_1>; constexpr Zom1 zom1;
	using Zom2 = ZeroOrMore<Sub1::_2>; constexpr Zom2 zom2;
	using Zom3 = ZeroOrMore<Sub1::_3>; constexpr Zom3 zom3;
	using Zom4 = ZeroOrMore<Sub1::_4>; constexpr Zom4 zom4;

	namespace Sub2
	{
		using _1 = ABC;
		using _2 = OneOrMore<ABC>;
		using _3 = Maybe<Choice<ABC, QQ>>;
		using _4 = Sequence<ABC, ZeroOrMore<QQ>>;
		using _5 = Sequence<OneOrMore<ABC>, Maybe<Choice<ABC, QQ>>>;
	}

	using Ign1 = Ignore<Sub2::_1>; constexpr Ign1 ign1;
	using Ign2 = Ignore<Sub2::_2>; constexpr Ign2 ign2;
	using Ign3 = Ignore<Sub2::_3>; constexpr Ign3 ign3;
	using Ign4 = Ignore<Sub2::_4>; constexpr Ign4 ign4;
	using Ign5 = Ignore<Sub2::_5>; constexpr Ign5 ign5;

	using Del1 = Delimit<ABC, Comma>;    constexpr Del1 del1;
	using Del2 = Delimit<ABC, SpaceDot>; constexpr Del2 del2;
	using Del3 = Delimit<QQ, Comma>;     constexpr Del3 del3;
	using Del4 = Delimit<QQ, SpaceDot>;  constexpr Del4 del4;
	using Del5 = Delimit<Comma, ABC>;    constexpr Del5 del5;
	using Del6 = Delimit<SpaceDot, ABC>; constexpr Del6 del6;
	using Del7 = Delimit<Comma, QQ>;     constexpr Del7 del7;
	using Del8 = Delimit<SpaceDot, QQ>;  constexpr Del8 del8;

	using Com1 = Complete<Sub1::_1>;             constexpr Com1 com1;
	using Com2 = Complete<Sub1::_2>;             constexpr Com2 com2;
	using Com3 = Complete<Sub1::_3>;             constexpr Com3 com3;
	using Com4 = Complete<Sub1::_4>;             constexpr Com4 com4;
	using Com5 = Complete<Maybe<Sub1::_4>>;      constexpr Com5 com5;
	using Com6 = Complete<OneOrMore<Sub1::_4>>;  constexpr Com6 com6;
	using Com7 = Complete<ZeroOrMore<Sub1::_4>>; constexpr Com7 com7;

	using Joi1 = Join<Sub2::_1>; constexpr Joi1 joi1;
	using Joi2 = Join<Sub2::_2>; constexpr Joi2 joi2;
	using Joi3 = Join<Sub2::_3>; constexpr Joi3 joi3;
	using Joi4 = Join<Sub2::_4>; constexpr Joi4 joi4;
	using Joi5 = Join<Sub2::_5>; constexpr Joi5 joi5;

	static_assert(parser_equality_operator::validate(
		oc1, oc2, oc3, nc1, nc2, nc3, l1, l2, l3, oc4, nc4, nc5, l4,
		qq, abc, comma, spacedot,
		cho1, cho2, cho3, cho4, seq1, seq2, seq3, seq4,
		Sub1::_1{}, Sub1::_2{}, Sub1::_3{}, Sub1::_4{},
		may1, may2, may3, may4, exa1, exa2, exa3, exa4,
		oom1, oom2, oom3, oom4, zom1, zom2, zom3, zom4,
		Sub2::_1{}, Sub2::_2{}, Sub2::_3{}, Sub2::_4{}, Sub2::_5{},
		ign1, ign2, ign3, ign4, ign5,
		del1, del2, del3, del4, del5, del6, del7, del8,
		com1, com2, com3, com4, com5, com6, com7
	), "operator==() and operator!=() are not implemented properly on Parser types");

}

TOK3N_END_NAMESPACE_TESTS()
