#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

namespace
{
	using vec_type = std::vector<Output<wchar_t>>;
}

FIXTURE("Delimit regular");
FIXTURE("Delimit keep");

TEST("Delimit regular", "Requirements")
{
	ASSERT_IS_PARSER(Del1, DelimitFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Del2, DelimitFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Del3, DelimitFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Del4, DelimitFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Del5, DelimitFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Del6, DelimitFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Del7, DelimitFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Del8, DelimitFamily, std::vector<Output<wchar_t>>);
}

TEST("Delimit keep", "Requirements")
{
	ASSERT_IS_PARSER(Dek1, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
	ASSERT_IS_PARSER(Dek2, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
	ASSERT_IS_PARSER(Dek3, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
	ASSERT_IS_PARSER(Dek4, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
	ASSERT_IS_PARSER(Dek5, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
	ASSERT_IS_PARSER(Dek6, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
	ASSERT_IS_PARSER(Dek7, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
	ASSERT_IS_PARSER(Dek8, DelimitFamily, std::pair<std::vector<Output<wchar_t>>, std::vector<Output<wchar_t>>>);
}

TEST("Delimit regular", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Del1, L"abc,abc,abc,,abc,abc,abc", vec_type({ L"abc", L"abc", L"abc" }), L",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, L",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del1, L"abc ,abc,abc,abc,,abc,abc,abc", vec_type({ L"abc" }), L" ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, L"");
	ASSERT_PARSE_SUCCESS(Del2, L"abc.abc abc .abc.abc abc", vec_type({ L"abc", L"abc", L"abc" }), L" .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del2, L"abc abc.abc .abc.abc abc", vec_type({ L"abc", L"abc", L"abc" }), L" .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, L".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, L" abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, L"");
	ASSERT_PARSE_SUCCESS(Del3, L"??,??,??,,??,??,??", vec_type({ L"??", L"??", L"??" }), L",,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, L",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del3, L"?? ,??,??,??,,??,??,??", vec_type({ L"??" }), L" ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, L"");
	ASSERT_PARSE_SUCCESS(Del4, L"??.?? ?? .??.?? ??", vec_type({ L"??", L"??", L"??" }), L" .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del4, L"?? ??.?? .??.?? ??", vec_type({ L"??", L"??", L"??" }), L" .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, L".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, L" ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, L"");
}

TEST("Delimit regular", "Parse all inverted")
{
	ASSERT_PARSE_FAILURE(Del5, L"abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del5, L",abc,abc,abc,,abc,abc,abc", vec_type({ L",", L",", L",", L"," }), L",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, L"abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, L"");
	ASSERT_PARSE_FAILURE(Del6, L"abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, L"abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, L".abc abc.abc .abc.abc abc", vec_type({ L".", L" ", L".", L" " }), L".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, L" abc abc.abc .abc.abc abc", vec_type({ L" ", L" ", L".", L" " }), L".abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, L"");
	ASSERT_PARSE_FAILURE(Del7, L"??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del7, L",??,??,??,,??,??,??", vec_type({ L",", L",", L",", L"," }), L",??,??,??");
	ASSERT_PARSE_FAILURE(Del7, L"?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del7, L"");
	ASSERT_PARSE_FAILURE(Del8, L"??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, L"?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, L".?? ??.?? .??.?? ??", vec_type({ L".", L" ", L".", L" " }), L".??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, L" ?? ??.?? .??.?? ??", vec_type({ L" ", L" ", L".", L" " }), L".??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, L"");
}

TEST("Delimit keep", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Dek1, L"abc,abc,abc,,abc,abc,abc", std::pair(vec_type({ L"abc", L"abc", L"abc" }), vec_type({ L",", L"," })), L",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, L",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek1, L"abc ,abc,abc,abc,,abc,abc,abc", std::pair(vec_type({ L"abc" }), vec_type{}), L" ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, L"");
	ASSERT_PARSE_SUCCESS(Dek2, L"abc.abc abc .abc.abc abc", std::pair(vec_type({ L"abc", L"abc", L"abc" }), vec_type({ L".", L" " })), L" .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek2, L"abc abc.abc .abc.abc abc", std::pair(vec_type({ L"abc", L"abc", L"abc" }), vec_type({ L" ", L"." })), L" .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, L".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, L" abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, L"");
	ASSERT_PARSE_SUCCESS(Dek3, L"??,??,??,,??,??,??", std::pair(vec_type({ L"??", L"??", L"??" }), vec_type({ L",", L"," })), L",,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, L",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek3, L"?? ,??,??,??,,??,??,??", std::pair(vec_type({ L"??" }), vec_type{}), L" ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, L"");
	ASSERT_PARSE_SUCCESS(Dek4, L"??.?? ?? .??.?? ??", std::pair(vec_type({ L"??", L"??", L"??" }), vec_type({ L".", L" " })), L" .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek4, L"?? ??.?? .??.?? ??", std::pair(vec_type({ L"??", L"??", L"??" }), vec_type({ L" ", L"." })), L" .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, L".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, L" ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, L"");
}

TEST("Delimit keep", "Parse all inverted")
{
	ASSERT_PARSE_FAILURE(Dek5, L"abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek5, L",abc,abc,abc,,abc,abc,abc", std::pair(vec_type({ L",", L",", L",", L","}), vec_type({ L"abc", L"abc", L"abc" })), L",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, L"abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, L"");
	ASSERT_PARSE_FAILURE(Dek6, L"abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, L"abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, L".abc abc.abc .abc.abc abc", std::pair(vec_type({ L".", L" ", L".", L" "}), vec_type({ L"abc", L"abc", L"abc" })), L".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, L" abc abc.abc .abc.abc abc", std::pair(vec_type({ L" ", L" ", L".", L" "}), vec_type({ L"abc", L"abc", L"abc" })), L".abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, L"");
	ASSERT_PARSE_FAILURE(Dek7, L"??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek7, L",??,??,??,,??,??,??", std::pair(vec_type({ L",", L",", L",", L","}), vec_type({ L"??", L"??", L"??" })), L",??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, L"?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, L"");
	ASSERT_PARSE_FAILURE(Dek8, L"??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, L"?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, L".?? ??.?? .??.?? ??", std::pair(vec_type({ L".", L" ", L".", L" "}), vec_type({ L"??", L"??", L"??" })), L".??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, L" ?? ??.?? .??.?? ??", std::pair(vec_type({ L" ", L" ", L".", L" "}), vec_type({ L"??", L"??", L"??" })), L".??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, L"");
}
