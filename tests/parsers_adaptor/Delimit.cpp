#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Delimit)

using namespace samples::all;

void requirements()
{
	assert
		, IsParser<Del1, DelimitType, std::vector<std::string_view>>
		, IsParser<Del2, DelimitType, std::vector<std::string_view>>
		, IsParser<Del3, DelimitType, std::vector<std::string_view>>
		, IsParser<Del4, DelimitType, std::vector<std::string_view>>
		, IsParser<Del5, DelimitType, std::vector<std::string_view>>
		, IsParser<Del6, DelimitType, std::vector<std::string_view>>
		, IsParser<Del7, DelimitType, std::vector<std::string_view>>
		, IsParser<Del8, DelimitType, std::vector<std::string_view>>
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
