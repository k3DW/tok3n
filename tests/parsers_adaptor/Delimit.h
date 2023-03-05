#ifdef TOK3N_TESTING
#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Delimit)

using namespace samples::all;

void requirements()
{
	assert
		, is_parser<Del1>
		, parser_type_of<Del1>.is_Delimit
		, result_of<Del1>.is<std::vector<std::string_view>>

		, is_parser<Del2>
		, parser_type_of<Del2>.is_Delimit
		, result_of<Del2>.is<std::vector<std::string_view>>

		, is_parser<Del3>
		, parser_type_of<Del3>.is_Delimit
		, result_of<Del3>.is<std::vector<std::string_view>>

		, is_parser<Del4>
		, parser_type_of<Del4>.is_Delimit
		, result_of<Del4>.is<std::vector<std::string_view>>

		, is_parser<Del5>
		, parser_type_of<Del5>.is_Delimit
		, result_of<Del5>.is<std::vector<std::string_view>>

		, is_parser<Del6>
		, parser_type_of<Del6>.is_Delimit
		, result_of<Del6>.is<std::vector<std::string_view>>

		, is_parser<Del7>
		, parser_type_of<Del7>.is_Delimit
		, result_of<Del7>.is<std::vector<std::string_view>>

		, is_parser<Del8>
		, parser_type_of<Del8>.is_Delimit
		, result_of<Del8>.is<std::vector<std::string_view>>
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
