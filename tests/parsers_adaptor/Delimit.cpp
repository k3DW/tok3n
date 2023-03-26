#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Delimit)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Del1>
		, Del1::type == ParserType::Delimit
		, ParserResultOf<Del1>::is<std::vector<std::string_view>>

		, is_parser<Del2>
		, Del2::type == ParserType::Delimit
		, ParserResultOf<Del2>::is<std::vector<std::string_view>>

		, is_parser<Del3>
		, Del3::type == ParserType::Delimit
		, ParserResultOf<Del3>::is<std::vector<std::string_view>>

		, is_parser<Del4>
		, Del4::type == ParserType::Delimit
		, ParserResultOf<Del4>::is<std::vector<std::string_view>>

		, is_parser<Del5>
		, Del5::type == ParserType::Delimit
		, ParserResultOf<Del5>::is<std::vector<std::string_view>>

		, is_parser<Del6>
		, Del6::type == ParserType::Delimit
		, ParserResultOf<Del6>::is<std::vector<std::string_view>>

		, is_parser<Del7>
		, Del7::type == ParserType::Delimit
		, ParserResultOf<Del7>::is<std::vector<std::string_view>>

		, is_parser<Del8>
		, Del8::type == ParserType::Delimit
		, ParserResultOf<Del8>::is<std::vector<std::string_view>>
		;
}

void parse_Delimit_regular()
{
	assert
		, parse<Del1>("abc,abc,abc,,abc,abc,abc").success({ "abc", "abc", "abc" }, ",,abc,abc,abc")
		, parse<Del1>(",abc,abc,abc,,abc,abc,abc").failure()
		, parse<Del1>("abc ,abc,abc,abc,,abc,abc,abc").success({ "abc" }, " ,abc,abc,abc,,abc,abc,abc")
		, parse<Del1>("").failure()
		, parse<Del2>("abc.abc abc .abc.abc abc").success({ "abc", "abc", "abc" }, " .abc.abc abc")
		, parse<Del2>("abc abc.abc .abc.abc abc").success({ "abc", "abc", "abc" }, " .abc.abc abc")
		, parse<Del2>(".abc abc.abc .abc.abc abc").failure()
		, parse<Del2>(" abc abc.abc .abc.abc abc").failure()
		, parse<Del2>("").failure()
		, parse<Del3>("??,??,??,,??,??,??").success({ "??", "??", "??" }, ",,??,??,??")
		, parse<Del3>(",??,??,??,,??,??,??").failure()
		, parse<Del3>("?? ,??,??,??,,??,??,??").success({ "??" }, " ,??,??,??,,??,??,??")
		, parse<Del3>("").failure()
		, parse<Del4>("??.?? ?? .??.?? ??").success({ "??", "??", "??" }, " .??.?? ??")
		, parse<Del4>("?? ??.?? .??.?? ??").success({ "??", "??", "??" }, " .??.?? ??")
		, parse<Del4>(".?? ??.?? .??.?? ??").failure()
		, parse<Del4>(" ?? ??.?? .??.?? ??").failure()
		, parse<Del4>("").failure()
		;
}
void parse_Delimit_reversed()
{
	assert
		, parse<Del5>("abc,abc,abc,,abc,abc,abc").failure()
		, parse<Del5>(",abc,abc,abc,,abc,abc,abc").success({ ",", ",", ",", "," }, ",abc,abc,abc")
		, parse<Del5>("abc ,abc,abc,abc,,abc,abc,abc").failure()
		, parse<Del5>("").failure()
		, parse<Del6>("abc.abc abc .abc.abc abc").failure()
		, parse<Del6>("abc abc.abc .abc.abc abc").failure()
		, parse<Del6>(".abc abc.abc .abc.abc abc").success({ ".", " ", ".", " " }, ".abc.abc abc")
		, parse<Del6>(" abc abc.abc .abc.abc abc").success({ " ", " ", ".", " " }, ".abc.abc abc")
		, parse<Del6>("").failure()
		, parse<Del7>("??,??,??,,??,??,??").failure()
		, parse<Del7>(",??,??,??,,??,??,??").success({ ",", ",", ",", "," }, ",??,??,??")
		, parse<Del7>("?? ,??,??,??,,??,??,??").failure()
		, parse<Del7>("").failure()
		, parse<Del8>("??.?? ?? .??.?? ??").failure()
		, parse<Del8>("?? ??.?? .??.?? ??").failure()
		, parse<Del8>(".?? ??.?? .??.?? ??").success({ ".", " ", ".", " " }, ".??.?? ??")
		, parse<Del8>(" ?? ??.?? .??.?? ??").success({ " ", " ", ".", " " }, ".??.?? ??")
		, parse<Del8>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Delimit)
#endif
