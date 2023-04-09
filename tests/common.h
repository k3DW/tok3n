#pragma once
#include "samples/adaptor.h"
#include "samples/basic.h"
#include "samples/classes.h"
#include "samples/compound.h"
#include "samples/functions.h"
#include "samples/repeat.h"

TOK3N_BEGIN_NAMESPACE(tests)

namespace traits::basic
{

	template <template <StaticString> class BasicParser>
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

		template <StaticString str> static constexpr bool from = requires { typename BasicParser<str>; };
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

namespace traits::operators
{

	template <Parser auto parser>
	concept valid_bang = requires { { !parser } -> Parser; };

	template <Parser auto parser, Modifier auto modifier>
	concept valid_modulo = requires { { parser % modifier } -> Parser; };

	template <Modifier auto modifier, Parser auto... parsers>
	concept valid_function_call = requires { { modifier(parsers...) } -> Parser; };

}

namespace samples::all
{

	using namespace basic;

	using Joi1 = Join<_21>; constexpr Joi1 joi1;
	using Joi2 = Join<_22>; constexpr Joi2 joi2;
	using Joi3 = Join<_23>; constexpr Joi3 joi3;
	using Joi4 = Join<_24>; constexpr Joi4 joi4;
	using Joi5 = Join<_25>; constexpr Joi5 joi5;

	using namespace functions;

	using Tra1 = Transform<_22, func1>;    constexpr Tra1 tra1;
	using Tra2 = Transform<_23, func2>;    constexpr Tra2 tra2;
	using Tra3 = Transform<_24, func3>;    constexpr Tra3 tra3;
	using Tra4 = Transform<_25, func4(3)>; constexpr Tra4 tra4;

	using Apt1 = ApplyTransform<_24, func3_apply>;    constexpr Apt1 apt1;
	using Apt2 = ApplyTransform<_25, func4_apply(3)>; constexpr Apt2 apt2;

	using namespace classes;

	using Int1 = Into<SpaceDot, Class1>;                              constexpr Int1 int1;
	using Int2 = Into<Sequence<ABC, SpaceDot>, Class2>;               constexpr Int2 int2;
	using Int3 = Into<Into<Sequence<ABC, SpaceDot>, Class4>, Class2>; constexpr Int3 int3;

	using Api1 = ApplyInto<Sequence<ABC, SpaceDot>, Class2>; constexpr Api1 api1;
	using Api2 = ApplyInto<Sequence<SpaceDot, ABC>, Class5>; constexpr Api2 api2;

	using Con1 = Constant<_22, 1>;       constexpr Con1 con1;
	using Con2 = Constant<_23, 't'>;     constexpr Con2 con2;
	using Con3 = Constant<_24, true>;    constexpr Con3 con3;
	using Con4 = Constant<_25, nullptr>; constexpr Con4 con4;
	
	using Def1 = Defaulted<_22, int>;    constexpr Def1 def1;
	using Def2 = Defaulted<_23, Class3>; constexpr Def2 def2;

}

TOK3N_END_NAMESPACE(tests)
