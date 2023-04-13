#pragma once

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

TOK3N_END_NAMESPACE(tests)
