#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

namespace
{
	template <class V>
	using vec_type = std::vector<output_span<V>>;
}

FIXTURE("delimit_parser regular");
FIXTURE("delimit_parser keep");

TEST("delimit_parser regular", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Del1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Del2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Del3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Del4, value_type);
	ASSERT_PARSER_VALUE_TYPE(Del5, value_type);
	ASSERT_PARSER_VALUE_TYPE(Del6, value_type);
	ASSERT_PARSER_VALUE_TYPE(Del7, value_type);
	ASSERT_PARSER_VALUE_TYPE(Del8, value_type);

	ASSERT_IS_PARSER(Del1, char, delimit_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Del2, char, delimit_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Del3, char, delimit_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Del4, char, delimit_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Del5, char, delimit_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Del6, char, delimit_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Del7, char, delimit_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Del8, char, delimit_family, std::vector<output_span<char>>);

	ASSERT_IS_PARSER(Del1, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Del2, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Del3, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Del4, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Del5, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Del6, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Del7, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Del8, wchar_t, delimit_family, std::vector<output_span<wchar_t>>);

	ASSERT_IS_PARSER(Del1, int, delimit_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Del2, int, delimit_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Del3, int, delimit_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Del4, int, delimit_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Del5, int, delimit_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Del6, int, delimit_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Del7, int, delimit_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Del8, int, delimit_family, std::vector<output_span<int>>);
}

TEST("delimit_parser keep", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Dek1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Dek2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Dek3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Dek4, value_type);
	ASSERT_PARSER_VALUE_TYPE(Dek5, value_type);
	ASSERT_PARSER_VALUE_TYPE(Dek6, value_type);
	ASSERT_PARSER_VALUE_TYPE(Dek7, value_type);
	ASSERT_PARSER_VALUE_TYPE(Dek8, value_type);

	ASSERT_IS_PARSER(Dek1, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);
	ASSERT_IS_PARSER(Dek2, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);
	ASSERT_IS_PARSER(Dek3, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);
	ASSERT_IS_PARSER(Dek4, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);
	ASSERT_IS_PARSER(Dek5, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);
	ASSERT_IS_PARSER(Dek6, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);
	ASSERT_IS_PARSER(Dek7, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);
	ASSERT_IS_PARSER(Dek8, char, delimit_family, std::pair<std::vector<output_span<char>>, std::vector<output_span<char>>>);

	ASSERT_IS_PARSER(Dek1, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Dek2, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Dek3, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Dek4, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Dek5, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Dek6, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Dek7, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Dek8, wchar_t, delimit_family, std::pair<std::vector<output_span<wchar_t>>, std::vector<output_span<wchar_t>>>);

	ASSERT_IS_PARSER(Dek1, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
	ASSERT_IS_PARSER(Dek2, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
	ASSERT_IS_PARSER(Dek3, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
	ASSERT_IS_PARSER(Dek4, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
	ASSERT_IS_PARSER(Dek5, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
	ASSERT_IS_PARSER(Dek6, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
	ASSERT_IS_PARSER(Dek7, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
	ASSERT_IS_PARSER(Dek8, int, delimit_family, std::pair<std::vector<output_span<int>>, std::vector<output_span<int>>>);
}

TEST("delimit_parser regular", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Del1, "abc,abc,abc,,abc,abc,abc", vec_type<char>({ "abc", "abc", "abc" }), ",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, ",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del1, "abc ,abc,abc,abc,,abc,abc,abc", vec_type<char>({ "abc" }), " ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, "");
	ASSERT_PARSE_SUCCESS(Del2, "abc.abc abc .abc.abc abc", vec_type<char>({ "abc", "abc", "abc" }), " .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del2, "abc abc.abc .abc.abc abc", vec_type<char>({ "abc", "abc", "abc" }), " .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, ".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, " abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, "");
	ASSERT_PARSE_SUCCESS(Del3, "??,??,??,,??,??,??", vec_type<char>({ "??", "??", "??" }), ",,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, ",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del3, "?? ,??,??,??,,??,??,??", vec_type<char>({ "??" }), " ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, "");
	ASSERT_PARSE_SUCCESS(Del4, "??.?? ?? .??.?? ??", vec_type<char>({ "??", "??", "??" }), " .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del4, "?? ??.?? .??.?? ??", vec_type<char>({ "??", "??", "??" }), " .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, ".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, " ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, "");

	ASSERT_PARSE_SUCCESS(Del1, L"abc,abc,abc,,abc,abc,abc", vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), L",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, L",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del1, L"abc ,abc,abc,abc,,abc,abc,abc", vec_type<wchar_t>({ L"abc" }), L" ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, L"");
	ASSERT_PARSE_SUCCESS(Del2, L"abc.abc abc .abc.abc abc", vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), L" .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del2, L"abc abc.abc .abc.abc abc", vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), L" .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, L".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, L" abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, L"");
	ASSERT_PARSE_SUCCESS(Del3, L"??,??,??,,??,??,??", vec_type<wchar_t>({ L"??", L"??", L"??" }), L",,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, L",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del3, L"?? ,??,??,??,,??,??,??", vec_type<wchar_t>({ L"??" }), L" ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, L"");
	ASSERT_PARSE_SUCCESS(Del4, L"??.?? ?? .??.?? ??", vec_type<wchar_t>({ L"??", L"??", L"??" }), L" .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del4, L"?? ??.?? .??.?? ??", vec_type<wchar_t>({ L"??", L"??", L"??" }), L" .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, L".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, L" ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, L"");

	ASSERT_PARSE_SUCCESS(Del1, e<int>("abc,abc,abc,,abc,abc,abc"), vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") }), e<int>(",,abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Del1, e<int>(",abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_SUCCESS(Del1, e<int>("abc ,abc,abc,abc,,abc,abc,abc"), vec_type<int>({ e<int>("abc") }), e<int>(" ,abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Del1, e<int>());
	ASSERT_PARSE_SUCCESS(Del2, e<int>("abc.abc abc .abc.abc abc"), vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") }), e<int>(" .abc.abc abc"));
	ASSERT_PARSE_SUCCESS(Del2, e<int>("abc abc.abc .abc.abc abc"), vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") }), e<int>(" .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Del2, e<int>(".abc abc.abc .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Del2, e<int>(" abc abc.abc .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Del2, e<int>());
	ASSERT_PARSE_SUCCESS(Del3, e<int>("??,??,??,,??,??,??"), vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") }), e<int>(",,??,??,??"));
	ASSERT_PARSE_FAILURE(Del3, e<int>(",??,??,??,,??,??,??"));
	ASSERT_PARSE_SUCCESS(Del3, e<int>("?? ,??,??,??,,??,??,??"), vec_type<int>({ e<int>("??") }), e<int>(" ,??,??,??,,??,??,??"));
	ASSERT_PARSE_FAILURE(Del3, e<int>());
	ASSERT_PARSE_SUCCESS(Del4, e<int>("??.?? ?? .??.?? ??"), vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") }), e<int>(" .??.?? ??"));
	ASSERT_PARSE_SUCCESS(Del4, e<int>("?? ??.?? .??.?? ??"), vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") }), e<int>(" .??.?? ??"));
	ASSERT_PARSE_FAILURE(Del4, e<int>(".?? ??.?? .??.?? ??"));
	ASSERT_PARSE_FAILURE(Del4, e<int>(" ?? ??.?? .??.?? ??"));
	ASSERT_PARSE_FAILURE(Del4, e<int>());
}

TEST("delimit_parser regular", "Parse all inverted")
{
	ASSERT_PARSE_FAILURE(Del5, "abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del5, ",abc,abc,abc,,abc,abc,abc", vec_type<char>({ ",", ",", ",", "," }), ",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, "abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, "");
	ASSERT_PARSE_FAILURE(Del6, "abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, "abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, ".abc abc.abc .abc.abc abc", vec_type<char>({ ".", " ", ".", " " }), ".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, " abc abc.abc .abc.abc abc", vec_type<char>({ " ", " ", ".", " " }), ".abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, "");
	ASSERT_PARSE_FAILURE(Del7, "??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del7, ",??,??,??,,??,??,??", vec_type<char>({ ",", ",", ",", "," }), ",??,??,??");
	ASSERT_PARSE_FAILURE(Del7, "?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del7, "");
	ASSERT_PARSE_FAILURE(Del8, "??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, "?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, ".?? ??.?? .??.?? ??", vec_type<char>({ ".", " ", ".", " " }), ".??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, " ?? ??.?? .??.?? ??", vec_type<char>({ " ", " ", ".", " " }), ".??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, "");

	ASSERT_PARSE_FAILURE(Del5, L"abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del5, L",abc,abc,abc,,abc,abc,abc", vec_type<wchar_t>({ L",", L",", L",", L"," }), L",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, L"abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, L"");
	ASSERT_PARSE_FAILURE(Del6, L"abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, L"abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, L".abc abc.abc .abc.abc abc", vec_type<wchar_t>({ L".", L" ", L".", L" " }), L".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, L" abc abc.abc .abc.abc abc", vec_type<wchar_t>({ L" ", L" ", L".", L" " }), L".abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, L"");
	ASSERT_PARSE_FAILURE(Del7, L"??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del7, L",??,??,??,,??,??,??", vec_type<wchar_t>({ L",", L",", L",", L"," }), L",??,??,??");
	ASSERT_PARSE_FAILURE(Del7, L"?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del7, L"");
	ASSERT_PARSE_FAILURE(Del8, L"??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, L"?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, L".?? ??.?? .??.?? ??", vec_type<wchar_t>({ L".", L" ", L".", L" " }), L".??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, L" ?? ??.?? .??.?? ??", vec_type<wchar_t>({ L" ", L" ", L".", L" " }), L".??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, L"");

	ASSERT_PARSE_FAILURE(Del5, e<int>("abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_SUCCESS(Del5, e<int>(",abc,abc,abc,,abc,abc,abc"), vec_type<int>({ e<int>(","), e<int>(","), e<int>(","), e<int>(",") }), e<int>(",abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Del5, e<int>("abc ,abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Del5, e<int>());
	ASSERT_PARSE_FAILURE(Del6, e<int>("abc.abc abc .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Del6, e<int>("abc abc.abc .abc.abc abc"));
	ASSERT_PARSE_SUCCESS(Del6, e<int>(".abc abc.abc .abc.abc abc"), vec_type<int>({ e<int>("."), e<int>(" "), e<int>("."), e<int>(" ") }), e<int>(".abc.abc abc"));
	ASSERT_PARSE_SUCCESS(Del6, e<int>(" abc abc.abc .abc.abc abc"), vec_type<int>({ e<int>(" "), e<int>(" "), e<int>("."), e<int>(" ") }), e<int>(".abc.abc abc"));
	ASSERT_PARSE_FAILURE(Del6, e<int>());
	ASSERT_PARSE_FAILURE(Del7, e<int>("??,??,??,,??,??,??"));
	ASSERT_PARSE_SUCCESS(Del7, e<int>(",??,??,??,,??,??,??"), vec_type<int>({ e<int>(","), e<int>(","), e<int>(","), e<int>(",") }), e<int>(",??,??,??"));
	ASSERT_PARSE_FAILURE(Del7, e<int>("?? ,??,??,??,,??,??,??"));
	ASSERT_PARSE_FAILURE(Del7, e<int>());
	ASSERT_PARSE_FAILURE(Del8, e<int>("??.?? ?? .??.?? ??"));
	ASSERT_PARSE_FAILURE(Del8, e<int>("?? ??.?? .??.?? ??"));
	ASSERT_PARSE_SUCCESS(Del8, e<int>(".?? ??.?? .??.?? ??"), vec_type<int>({ e<int>("."), e<int>(" "), e<int>("."), e<int>(" ") }), e<int>(".??.?? ??"));
	ASSERT_PARSE_SUCCESS(Del8, e<int>(" ?? ??.?? .??.?? ??"), vec_type<int>({ e<int>(" "), e<int>(" "), e<int>("."), e<int>(" ") }), e<int>(".??.?? ??"));
	ASSERT_PARSE_FAILURE(Del8, e<int>());
}

TEST("delimit_parser keep", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Dek1, "abc,abc,abc,,abc,abc,abc", std::pair(vec_type<char>({ "abc", "abc", "abc" }), vec_type<char>({ ",", "," })), ",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, ",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek1, "abc ,abc,abc,abc,,abc,abc,abc", std::pair(vec_type<char>({ "abc" }), vec_type<char>{}), " ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, "");
	ASSERT_PARSE_SUCCESS(Dek2, "abc.abc abc .abc.abc abc", std::pair(vec_type<char>({ "abc", "abc", "abc" }), vec_type<char>({ ".", " " })), " .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek2, "abc abc.abc .abc.abc abc", std::pair(vec_type<char>({ "abc", "abc", "abc" }), vec_type<char>({ " ", "." })), " .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, ".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, " abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, "");
	ASSERT_PARSE_SUCCESS(Dek3, "??,??,??,,??,??,??", std::pair(vec_type<char>({ "??", "??", "??" }), vec_type<char>({ ",", "," })), ",,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, ",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek3, "?? ,??,??,??,,??,??,??", std::pair(vec_type<char>({ "??" }), vec_type<char>{}), " ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, "");
	ASSERT_PARSE_SUCCESS(Dek4, "??.?? ?? .??.?? ??", std::pair(vec_type<char>({ "??", "??", "??" }), vec_type<char>({ ".", " " })), " .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek4, "?? ??.?? .??.?? ??", std::pair(vec_type<char>({ "??", "??", "??" }), vec_type<char>({ " ", "." })), " .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, ".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, " ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, "");

	ASSERT_PARSE_SUCCESS(Dek1, L"abc,abc,abc,,abc,abc,abc", std::pair(vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), vec_type<wchar_t>({ L",", L"," })), L",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, L",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek1, L"abc ,abc,abc,abc,,abc,abc,abc", std::pair(vec_type<wchar_t>({ L"abc" }), vec_type<wchar_t>{}), L" ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, L"");
	ASSERT_PARSE_SUCCESS(Dek2, L"abc.abc abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), vec_type<wchar_t>({ L".", L" " })), L" .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek2, L"abc abc.abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L"abc", L"abc", L"abc" }), vec_type<wchar_t>({ L" ", L"." })), L" .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, L".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, L" abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, L"");
	ASSERT_PARSE_SUCCESS(Dek3, L"??,??,??,,??,??,??", std::pair(vec_type<wchar_t>({ L"??", L"??", L"??" }), vec_type<wchar_t>({ L",", L"," })), L",,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, L",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek3, L"?? ,??,??,??,,??,??,??", std::pair(vec_type<wchar_t>({ L"??" }), vec_type<wchar_t>{}), L" ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, L"");
	ASSERT_PARSE_SUCCESS(Dek4, L"??.?? ?? .??.?? ??", std::pair(vec_type<wchar_t>({ L"??", L"??", L"??" }), vec_type<wchar_t>({ L".", L" " })), L" .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek4, L"?? ??.?? .??.?? ??", std::pair(vec_type<wchar_t>({ L"??", L"??", L"??" }), vec_type<wchar_t>({ L" ", L"." })), L" .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, L".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, L" ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, L"");

	ASSERT_PARSE_SUCCESS(Dek1, e<int>("abc,abc,abc,,abc,abc,abc"), std::pair(vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") }), vec_type<int>({ e<int>(","), e<int>(",") })), e<int>(",,abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Dek1, e<int>(",abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_SUCCESS(Dek1, e<int>("abc ,abc,abc,abc,,abc,abc,abc"), std::pair(vec_type<int>({ e<int>("abc") }), vec_type<int>{}), e<int>(" ,abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Dek1, e<int>());
	ASSERT_PARSE_SUCCESS(Dek2, e<int>("abc.abc abc .abc.abc abc"), std::pair(vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") }), vec_type<int>({ e<int>("."), e<int>(" ") })), e<int>(" .abc.abc abc"));
	ASSERT_PARSE_SUCCESS(Dek2, e<int>("abc abc.abc .abc.abc abc"), std::pair(vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") }), vec_type<int>({ e<int>(" "), e<int>(".") })), e<int>(" .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Dek2, e<int>(".abc abc.abc .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Dek2, e<int>(" abc abc.abc .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Dek2, e<int>());
	ASSERT_PARSE_SUCCESS(Dek3, e<int>("??,??,??,,??,??,??"), std::pair(vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") }), vec_type<int>({ e<int>(","), e<int>(",") })), e<int>(",,??,??,??"));
	ASSERT_PARSE_FAILURE(Dek3, e<int>(",??,??,??,,??,??,??"));
	ASSERT_PARSE_SUCCESS(Dek3, e<int>("?? ,??,??,??,,??,??,??"), std::pair(vec_type<int>({ e<int>("??") }), vec_type<int>{}), e<int>(" ,??,??,??,,??,??,??"));
	ASSERT_PARSE_FAILURE(Dek3, e<int>());
	ASSERT_PARSE_SUCCESS(Dek4, e<int>("??.?? ?? .??.?? ??"), std::pair(vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") }), vec_type<int>({ e<int>("."), e<int>(" ") })), e<int>(" .??.?? ??"));
	ASSERT_PARSE_SUCCESS(Dek4, e<int>("?? ??.?? .??.?? ??"), std::pair(vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") }), vec_type<int>({ e<int>(" "), e<int>(".") })), e<int>(" .??.?? ??"));
	ASSERT_PARSE_FAILURE(Dek4, e<int>(".?? ??.?? .??.?? ??"));
	ASSERT_PARSE_FAILURE(Dek4, e<int>(" ?? ??.?? .??.?? ??"));
	ASSERT_PARSE_FAILURE(Dek4, e<int>());
}

TEST("delimit_parser keep", "Parse all inverted")
{
	ASSERT_PARSE_FAILURE(Dek5, "abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek5, ",abc,abc,abc,,abc,abc,abc", std::pair(vec_type<char>({ ",", ",", ",", ","}), vec_type<char>({ "abc", "abc", "abc" })), ",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, "abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, "");
	ASSERT_PARSE_FAILURE(Dek6, "abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, "abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, ".abc abc.abc .abc.abc abc", std::pair(vec_type<char>({ ".", " ", ".", " "}), vec_type<char>({ "abc", "abc", "abc" })), ".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, " abc abc.abc .abc.abc abc", std::pair(vec_type<char>({ " ", " ", ".", " "}), vec_type<char>({ "abc", "abc", "abc" })), ".abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, "");
	ASSERT_PARSE_FAILURE(Dek7, "??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek7, ",??,??,??,,??,??,??", std::pair(vec_type<char>({ ",", ",", ",", ","}), vec_type<char>({ "??", "??", "??" })), ",??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, "?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, "");
	ASSERT_PARSE_FAILURE(Dek8, "??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, "?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, ".?? ??.?? .??.?? ??", std::pair(vec_type<char>({ ".", " ", ".", " "}), vec_type<char>({ "??", "??", "??" })), ".??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, " ?? ??.?? .??.?? ??", std::pair(vec_type<char>({ " ", " ", ".", " "}), vec_type<char>({ "??", "??", "??" })), ".??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, "");

	ASSERT_PARSE_FAILURE(Dek5, L"abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek5, L",abc,abc,abc,,abc,abc,abc", std::pair(vec_type<wchar_t>({ L",", L",", L",", L"," }), vec_type<wchar_t>({ L"abc", L"abc", L"abc" })), L",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, L"abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, L"");
	ASSERT_PARSE_FAILURE(Dek6, L"abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, L"abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, L".abc abc.abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L".", L" ", L".", L" " }), vec_type<wchar_t>({ L"abc", L"abc", L"abc" })), L".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, L" abc abc.abc .abc.abc abc", std::pair(vec_type<wchar_t>({ L" ", L" ", L".", L" " }), vec_type<wchar_t>({ L"abc", L"abc", L"abc" })), L".abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, L"");
	ASSERT_PARSE_FAILURE(Dek7, L"??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek7, L",??,??,??,,??,??,??", std::pair(vec_type<wchar_t>({ L",", L",", L",", L"," }), vec_type<wchar_t>({ L"??", L"??", L"??" })), L",??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, L"?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, L"");
	ASSERT_PARSE_FAILURE(Dek8, L"??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, L"?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, L".?? ??.?? .??.?? ??", std::pair(vec_type<wchar_t>({ L".", L" ", L".", L" " }), vec_type<wchar_t>({ L"??", L"??", L"??" })), L".??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, L" ?? ??.?? .??.?? ??", std::pair(vec_type<wchar_t>({ L" ", L" ", L".", L" " }), vec_type<wchar_t>({ L"??", L"??", L"??" })), L".??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, L"");

	ASSERT_PARSE_FAILURE(Dek5, e<int>("abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_SUCCESS(Dek5, e<int>(",abc,abc,abc,,abc,abc,abc"), std::pair(vec_type<int>({ e<int>(","), e<int>(","), e<int>(","), e<int>(",") }), vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") })), e<int>(",abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Dek5, e<int>("abc ,abc,abc,abc,,abc,abc,abc"));
	ASSERT_PARSE_FAILURE(Dek5, e<int>());
	ASSERT_PARSE_FAILURE(Dek6, e<int>("abc.abc abc .abc.abc abc"));
	ASSERT_PARSE_FAILURE(Dek6, e<int>("abc abc.abc .abc.abc abc"));
	ASSERT_PARSE_SUCCESS(Dek6, e<int>(".abc abc.abc .abc.abc abc"), std::pair(vec_type<int>({ e<int>("."), e<int>(" "), e<int>("."), e<int>(" ") }), vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") })), e<int>(".abc.abc abc"));
	ASSERT_PARSE_SUCCESS(Dek6, e<int>(" abc abc.abc .abc.abc abc"), std::pair(vec_type<int>({ e<int>(" "), e<int>(" "), e<int>("."), e<int>(" ") }), vec_type<int>({ e<int>("abc"), e<int>("abc"), e<int>("abc") })), e<int>(".abc.abc abc"));
	ASSERT_PARSE_FAILURE(Dek6, e<int>());
	ASSERT_PARSE_FAILURE(Dek7, e<int>("??,??,??,,??,??,??"));
	ASSERT_PARSE_SUCCESS(Dek7, e<int>(",??,??,??,,??,??,??"), std::pair(vec_type<int>({ e<int>(","), e<int>(","), e<int>(","), e<int>(",") }), vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") })), e<int>(",??,??,??"));
	ASSERT_PARSE_FAILURE(Dek7, e<int>("?? ,??,??,??,,??,??,??"));
	ASSERT_PARSE_FAILURE(Dek7, e<int>());
	ASSERT_PARSE_FAILURE(Dek8, e<int>("??.?? ?? .??.?? ??"));
	ASSERT_PARSE_FAILURE(Dek8, e<int>("?? ??.?? .??.?? ??"));
	ASSERT_PARSE_SUCCESS(Dek8, e<int>(".?? ??.?? .??.?? ??"), std::pair(vec_type<int>({ e<int>("."), e<int>(" "), e<int>("."), e<int>(" ") }), vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") })), e<int>(".??.?? ??"));
	ASSERT_PARSE_SUCCESS(Dek8, e<int>(" ?? ??.?? .??.?? ??"), std::pair(vec_type<int>({ e<int>(" "), e<int>(" "), e<int>("."), e<int>(" ") }), vec_type<int>({ e<int>("??"), e<int>("??"), e<int>("??") })), e<int>(".??.?? ??"));
	ASSERT_PARSE_FAILURE(Dek8, e<int>());
}
