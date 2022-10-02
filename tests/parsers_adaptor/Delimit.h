#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Delimit)

using L1 = Literal<"abc">;
using L2 = Literal<"??">;

using OC1 = OneChar<",">;
using OC2 = OneChar<" .">;

using D1 = Delimit<L1, OC1>;
constexpr D1 d1;
using D2 = Delimit<L1, OC2>;
constexpr D2 d2;
using D3 = Delimit<L2, OC1>;
constexpr D3 d3;
using D4 = Delimit<L2, OC2>;
constexpr D4 d4;

using D5 = Delimit<OC1, L1>;
constexpr D5 d5;
using D6 = Delimit<OC2, L1>;
constexpr D6 d6;
using D7 = Delimit<OC1, L2>;
constexpr D7 d7;
using D8 = Delimit<OC2, L2>;
constexpr D8 d8;

void requirements_regular()
{
	assert
		, is_parser<D1>
		, parser_type_of<D1>.is_Delimit
		, result_of<D1>.is<std::vector<std::string_view>>
		, D1::parse == d1.parse
		, D1::lookahead == d1.lookahead

		, is_parser<D2>
		, parser_type_of<D2>.is_Delimit
		, result_of<D2>.is<std::vector<std::string_view>>
		, D2::parse == d2.parse
		, D2::lookahead == d2.lookahead

		, is_parser<D3>
		, parser_type_of<D3>.is_Delimit
		, result_of<D3>.is<std::vector<std::string_view>>
		, D3::parse == d3.parse
		, D3::lookahead == d3.lookahead

		, is_parser<D4>
		, parser_type_of<D4>.is_Delimit
		, result_of<D4>.is<std::vector<std::string_view>>
		, D4::parse == d4.parse
		, D4::lookahead == d4.lookahead
		;
}
void requirements_reversed()
{
	assert
		, is_parser<D5>
		, parser_type_of<D5>.is_Delimit
		, result_of<D5>.is<std::vector<std::string_view>>
		, D5::parse == d5.parse
		, D5::lookahead == d5.lookahead

		, is_parser<D6>
		, parser_type_of<D6>.is_Delimit
		, result_of<D6>.is<std::vector<std::string_view>>
		, D6::parse == d6.parse
		, D6::lookahead == d6.lookahead

		, is_parser<D7>
		, parser_type_of<D7>.is_Delimit
		, result_of<D7>.is<std::vector<std::string_view>>
		, D7::parse == d7.parse
		, D7::lookahead == d7.lookahead

		, is_parser<D8>
		, parser_type_of<D8>.is_Delimit
		, result_of<D8>.is<std::vector<std::string_view>>
		, D8::parse == d8.parse
		, D8::lookahead == d8.lookahead
		;
}

void parse_Delimit_regular()
{
	assert
		, parse<D1>("abc,abc,abc,,abc,abc,abc").success({ "abc", "abc", "abc" }, ",,abc,abc,abc")
		, parse<D1>(",abc,abc,abc,,abc,abc,abc").failure(",abc,abc,abc,,abc,abc,abc")
		, parse<D1>("abc ,abc,abc,abc,,abc,abc,abc").success({ "abc" }, " ,abc,abc,abc,,abc,abc,abc")
		, parse<D1>("").failure("")
		, parse<D2>("abc.abc abc .abc.abc abc").success({ "abc", "abc", "abc" }, " .abc.abc abc")
		, parse<D2>("abc abc.abc .abc.abc abc").success({ "abc", "abc", "abc" }, " .abc.abc abc")
		, parse<D2>(".abc abc.abc .abc.abc abc").failure(".abc abc.abc .abc.abc abc")
		, parse<D2>(" abc abc.abc .abc.abc abc").failure(" abc abc.abc .abc.abc abc")
		, parse<D2>("").failure("")
		, parse<D3>("??,??,??,,??,??,??").success({ "??", "??", "??" }, ",,??,??,??")
		, parse<D3>(",??,??,??,,??,??,??").failure(",??,??,??,,??,??,??")
		, parse<D3>("?? ,??,??,??,,??,??,??").success({ "??" }, " ,??,??,??,,??,??,??")
		, parse<D3>("").failure("")
		, parse<D4>("??.?? ?? .??.?? ??").success({ "??", "??", "??" }, " .??.?? ??")
		, parse<D4>("?? ??.?? .??.?? ??").success({ "??", "??", "??" }, " .??.?? ??")
		, parse<D4>(".?? ??.?? .??.?? ??").failure(".?? ??.?? .??.?? ??")
		, parse<D4>(" ?? ??.?? .??.?? ??").failure(" ?? ??.?? .??.?? ??")
		, parse<D4>("").failure("")
		;
}
void parse_Delimit_reversed()
{
	assert
		, parse<D5>("abc,abc,abc,,abc,abc,abc").failure("abc,abc,abc,,abc,abc,abc")
		, parse<D5>(",abc,abc,abc,,abc,abc,abc").success({ ",", ",", ",", "," }, ",abc,abc,abc")
		, parse<D5>("abc ,abc,abc,abc,,abc,abc,abc").failure("abc ,abc,abc,abc,,abc,abc,abc")
		, parse<D5>("").failure("")
		, parse<D6>("abc.abc abc .abc.abc abc").failure("abc.abc abc .abc.abc abc")
		, parse<D6>("abc abc.abc .abc.abc abc").failure("abc abc.abc .abc.abc abc")
		, parse<D6>(".abc abc.abc .abc.abc abc").success({ ".", " ", ".", " " }, ".abc.abc abc")
		, parse<D6>(" abc abc.abc .abc.abc abc").success({ " ", " ", ".", " " }, ".abc.abc abc")
		, parse<D6>("").failure("")
		, parse<D7>("??,??,??,,??,??,??").failure("??,??,??,,??,??,??")
		, parse<D7>(",??,??,??,,??,??,??").success({ ",", ",", ",", "," }, ",??,??,??")
		, parse<D7>("?? ,??,??,??,,??,??,??").failure("?? ,??,??,??,,??,??,??")
		, parse<D7>("").failure("")
		, parse<D8>("??.?? ?? .??.?? ??").failure("??.?? ?? .??.?? ??")
		, parse<D8>("?? ??.?? .??.?? ??").failure("?? ??.?? .??.?? ??")
		, parse<D8>(".?? ??.?? .??.?? ??").success({ ".", " ", ".", " " }, ".??.?? ??")
		, parse<D8>(" ?? ??.?? .??.?? ??").success({ " ", " ", ".", " " }, ".??.?? ??")
		, parse<D8>("").failure("")
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Delimit)
