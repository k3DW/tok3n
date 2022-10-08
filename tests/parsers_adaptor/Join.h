#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Join)

using L1 = Literal<"abc">;
using L2 = Literal<"??">;

using J1 = Join<L1>;
constexpr J1 j1;
using J2 = Join<OneOrMore<L1>>;
constexpr J2 j2;
using J3 = Join<Maybe<Choice<L1, L2>>>;
constexpr J3 j3;
using J4 = Join<Sequence<L1, ZeroOrMore<L2>>>;
constexpr J4 j4;
using J5 = Join<Sequence<OneOrMore<L1>, Maybe<Choice<L1, L2>>>>;
constexpr J5 j5;

void requirements()
{
	assert
		, is_parser<J1>
		, parser_type_of<J1>.is_Join
		, result_of<J1>.is<std::string_view>
		, J1::parse == j1.parse
		, J1::lookahead == j1.lookahead
		
		, is_parser<J2>
		, parser_type_of<J2>.is_Join
		, result_of<J2>.is<std::string_view>
		, J2::parse == j2.parse
		, J2::lookahead == j2.lookahead
		
		, is_parser<J3>
		, parser_type_of<J3>.is_Join
		, result_of<J3>.is<std::string_view>
		, J3::parse == j3.parse
		, J3::lookahead == j3.lookahead
		
		, is_parser<J4>
		, parser_type_of<J4>.is_Join
		, result_of<J4>.is<std::string_view>
		, J4::parse == j4.parse
		, J4::lookahead == j4.lookahead
		
		, is_parser<J5>
		, parser_type_of<J5>.is_Join
		, result_of<J5>.is<std::string_view>
		, J5::parse == j5.parse
		, J5::lookahead == j5.lookahead
		;
}

void parse_Join()
{
	assert
		, parse<J1>("abcabc").success("abc", "abc")
		, parse<J1>("Abcabc").failure("Abcabc")
		, parse<J1>(" abcabc").failure(" abcabc")

		, parse<J2>("abcabcabcab").success("abcabcabc", "ab")
		, parse<J2>("").failure("")
		, parse<J2>("ab").failure("ab")
		, parse<J2>("abc").success("abc", "")

		, parse<J3>("abcabc").success("abc", "abc")
		, parse<J3>("a??bcabc").success("", "a??bcabc")
		, parse<J3>("").success("", "")
		, parse<J3>("??abcabc").success("??", "abcabc")
		, parse<J3>(" ??abcabc").success("", " ??abcabc")

		, parse<J4>("abc???????").success("abc??????", "?")
		, parse<J4>("??abc???????").failure("??abc???????")
		, parse<J4>("abc??abc???????").success("abc??", "abc???????")
		, parse<J4>("abc ??abc???????").success("abc", " ??abc???????")
		, parse<J4>("").failure("")

		, parse<J5>("abcabcabcabc??").success("abcabcabcabc??", "")
		, parse<J5>("abcabcabcabc").success("abcabcabcabc", "")
		, parse<J5>("abcabcabcabc ??").success("abcabcabcabc", " ??")
		, parse<J5>("abc").success("abc", "")
		, parse<J5>(" abc").failure(" abc")
		, parse<J5>("").failure("")
		;
}

void join_operator()
{
	constexpr L1 l1;
	constexpr L2 l2;

	assert
		, j1 != l1 % join
		, l1 % join == l1
		, j2 == +l1 % join
		, j3 == ~(l1 | l2) % join
		, j4 == (l1 >> *l2) % join
		, j5 == (+l1 >> ~(l1 | l2)) % join

		, j1 == j1 % join
		, j1 == j1 % join % join
		, j2 == j2 % join
		, j2 == j2 % join % join
		, j3 == j3 % join
		, j3 == j3 % join % join
		, j4 == j4 % join
		, j4 == j4 % join % join
		, j5 == j5 % join
		, j5 == j5 % join % join
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Join)
