#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Ignore)

using L1 = Literal<"abc">;
using L2 = Literal<"??">;

using I1 = Ignore<L1>;
constexpr I1 i1;
using I2 = Ignore<OneOrMore<L1>>;
constexpr I2 i2;
using I3 = Ignore<Maybe<Choice<L1, L2>>>;
constexpr I3 i3;
using I4 = Ignore<Sequence<L1, ZeroOrMore<L2>>>;
constexpr I4 i4;
using I5 = Ignore<Sequence<OneOrMore<L1>, Maybe<Choice<L1, L2>>>>;
constexpr I5 i5;

void requirements()
{
	assert
		, is_parser<I1>
		, parser_type_of<I1>.is_Ignore
		, result_of<I1>.is<void>
		, I1::parse == i1.parse
		, I1::lookahead == i1.lookahead

		, is_parser<I2>
		, parser_type_of<I2>.is_Ignore
		, result_of<I2>.is<void>
		, I2::parse == i2.parse
		, I2::lookahead == i2.lookahead

		, is_parser<I3>
		, parser_type_of<I3>.is_Ignore
		, result_of<I3>.is<void>
		, I3::parse == i3.parse
		, I3::lookahead == i3.lookahead

		, is_parser<I4>
		, parser_type_of<I4>.is_Ignore
		, result_of<I4>.is<void>
		, I4::parse == i4.parse
		, I4::lookahead == i4.lookahead

		, is_parser<I5>
		, parser_type_of<I5>.is_Ignore
		, result_of<I5>.is<void>
		, I5::parse == i5.parse
		, I5::lookahead == i5.lookahead
		;
}

void parse_Ignore()
{
	assert
		, parse<I1>("abcabc").success("abc")
		, parse<I1>("Abcabc").failure()
		, parse<I1>(" abcabc").failure()
		
		, parse<I2>("abcabcabcab").success("ab")
		, parse<I2>("").failure()
		, parse<I2>("ab").failure()
		, parse<I2>("abc").success("")
		
		, parse<I3>("abcabc").success("abc")
		, parse<I3>("a??bcabc").success("a??bcabc")
		, parse<I3>("").success("")
		, parse<I3>("??abcabc").success("abcabc")
		, parse<I3>(" ??abcabc").success(" ??abcabc")
		
		, parse<I4>("abc???????").success("?")
		, parse<I4>("??abc???????").failure()
		, parse<I4>("abc??abc???????").success("abc???????")
		, parse<I4>("abc ??abc???????").success(" ??abc???????")
		, parse<I4>("").failure()
		
		, parse<I5>("abcabcabcabc??").success("")
		, parse<I5>("abcabcabcabc").success("")
		, parse<I5>("abcabcabcabc ??").success(" ??")
		, parse<I5>("abc").success("")
		, parse<I5>(" abc").failure()
		, parse<I5>("").failure()
		;
}

void ignore_operator()
{
	constexpr L1 l1;
	constexpr L2 l2;

	assert
		, i1 == ignore(l1)
		, i2 == ignore(+l1)
		, i3 == ignore(~(l1 | l2))
		, i4 == ignore(l1 >> *l2)
		, i5 == ignore(+l1 >> ~(l1 | l2))

		, i1 == ignore(i1)
		, i2 == ignore(i2)
		, i3 == ignore(i3)
		, i4 == ignore(i4)
		, i5 == ignore(i5)
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Ignore)
