#include "pch.h"

static void requirements()
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

static void requirements_keep()
{
	assert
		, IsParser<Dek1, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		, IsParser<Dek2, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		, IsParser<Dek3, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		, IsParser<Dek4, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		, IsParser<Dek5, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		, IsParser<Dek6, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		, IsParser<Dek7, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		, IsParser<Dek8, DelimitType, std::pair<std::vector<std::string_view>, std::vector<std::string_view>>>
		;
}

static void parse_Delimit_regular()
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

static void parse_Delimit_reversed()
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

static void parse_Delimit_keep_regular()
{
	assert
		, parse<Dek1>("abc,abc,abc,,abc,abc,abc").success({ { "abc", "abc", "abc" }, { ",", "," } }, ",,abc,abc,abc")
		, parse<Dek1>(",abc,abc,abc,,abc,abc,abc").failure()
		, parse<Dek1>("abc ,abc,abc,abc,,abc,abc,abc").success({ { "abc" }, {} }, " ,abc,abc,abc,,abc,abc,abc")
		, parse<Dek1>("").failure()
		, parse<Dek2>("abc.abc abc .abc.abc abc").success({ { "abc", "abc", "abc" }, { ".", " " } }, " .abc.abc abc")
		, parse<Dek2>("abc abc.abc .abc.abc abc").success({ { "abc", "abc", "abc" }, { " ", "." } }, " .abc.abc abc")
		, parse<Dek2>(".abc abc.abc .abc.abc abc").failure()
		, parse<Dek2>(" abc abc.abc .abc.abc abc").failure()
		, parse<Dek2>("").failure()
		, parse<Dek3>("??,??,??,,??,??,??").success({ { "??", "??", "??" }, { ",", "," } }, ",,??,??,??")
		, parse<Dek3>(",??,??,??,,??,??,??").failure()
		, parse<Dek3>("?? ,??,??,??,,??,??,??").success({ { "??" }, {} }, " ,??,??,??,,??,??,??")
		, parse<Dek3>("").failure()
		, parse<Dek4>("??.?? ?? .??.?? ??").success({ { "??", "??", "??" }, { ".", " " } }, " .??.?? ??")
		, parse<Dek4>("?? ??.?? .??.?? ??").success({ { "??", "??", "??" }, { " ", "." } }, " .??.?? ??")
		, parse<Dek4>(".?? ??.?? .??.?? ??").failure()
		, parse<Dek4>(" ?? ??.?? .??.?? ??").failure()
		, parse<Dek4>("").failure()
		;
}

static void parse_Delimit_keep_reversed()
{
	assert
		, parse<Dek5>("abc,abc,abc,,abc,abc,abc").failure()
		, parse<Dek5>(",abc,abc,abc,,abc,abc,abc").success({ { ",", ",", ",", "," }, { "abc", "abc", "abc" } }, ",abc,abc,abc")
		, parse<Dek5>("abc ,abc,abc,abc,,abc,abc,abc").failure()
		, parse<Dek5>("").failure()
		, parse<Dek6>("abc.abc abc .abc.abc abc").failure()
		, parse<Dek6>("abc abc.abc .abc.abc abc").failure()
		, parse<Dek6>(".abc abc.abc .abc.abc abc").success({ { ".", " ", ".", " " }, { "abc", "abc", "abc" } }, ".abc.abc abc")
		, parse<Dek6>(" abc abc.abc .abc.abc abc").success({ { " ", " ", ".", " " }, { "abc", "abc", "abc" } }, ".abc.abc abc")
		, parse<Dek6>("").failure()
		, parse<Dek7>("??,??,??,,??,??,??").failure()
		, parse<Dek7>(",??,??,??,,??,??,??").success({ { ",", ",", ",", "," }, { "??", "??", "??" } }, ",??,??,??")
		, parse<Dek7>("?? ,??,??,??,,??,??,??").failure()
		, parse<Dek7>("").failure()
		, parse<Dek8>("??.?? ?? .??.?? ??").failure()
		, parse<Dek8>("?? ??.?? .??.?? ??").failure()
		, parse<Dek8>(".?? ??.?? .??.?? ??").success({ { ".", " ", ".", " " }, { "??", "??", "??" } }, ".??.?? ??")
		, parse<Dek8>(" ?? ??.?? .??.?? ??").success({ { " ", " ", ".", " " }, { "??", "??", "??" } }, ".??.?? ??")
		, parse<Dek8>("").failure()
		;
}

void Delimit_tests()
{
	requirements();
	requirements_keep();
	parse_Delimit_regular();
	parse_Delimit_reversed();
	parse_Delimit_keep_regular();
	parse_Delimit_keep_reversed();
}
