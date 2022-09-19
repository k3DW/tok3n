#include "parsers/Literal.h"
#include "utility.h"

namespace LiteralTests
{

	using k3::parser::Literal;

	template <k3::static_string str>
	concept Constructible_From = requires { typename Literal<str>; };

	consteval void basic_parsing()
	{
		using P = Literal<"literal">;

		static_assert(k3::parser::Parser<P>);
		static_assert(k3::parser::IsLiteral<P>);
		static_assert(is_result_of<P, std::string_view>);

		constexpr P p;

		constexpr auto r1 = P::parse("literally");
		constexpr auto r2 = p.parse("literally");
		static_assert(validate(success, r1, "literal", "ly"));
		static_assert(validate(success, r2, "literal", "ly"));

		constexpr auto r3 = P::parse("litera");
		constexpr auto r4 = P::parse(" literal");
		static_assert(validate(failure, r3, "litera"));
		static_assert(validate(failure, r4, " literal"));
	}

	consteval void constructibility()
	{
		static_assert(Constructible_From<"literal">);
		static_assert(not Constructible_From<"lïterål">);
		static_assert(not Constructible_From<"">);
	}

}
