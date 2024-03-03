#include "pch.h"
#include "char-samples/char-samples.h"

namespace
{
	using vec_type = std::vector<Output<char>>;
}

FIXTURE("Delimit regular");
FIXTURE("Delimit keep");

TEST("Delimit regular", "Requirements")
{
	ASSERT_IS_PARSER(Del1, DelimitFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Del2, DelimitFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Del3, DelimitFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Del4, DelimitFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Del5, DelimitFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Del6, DelimitFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Del7, DelimitFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Del8, DelimitFamily, std::vector<Output<char>>);
}

TEST("Delimit keep", "Requirements")
{
	ASSERT_IS_PARSER(Dek1, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
	ASSERT_IS_PARSER(Dek2, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
	ASSERT_IS_PARSER(Dek3, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
	ASSERT_IS_PARSER(Dek4, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
	ASSERT_IS_PARSER(Dek5, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
	ASSERT_IS_PARSER(Dek6, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
	ASSERT_IS_PARSER(Dek7, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
	ASSERT_IS_PARSER(Dek8, DelimitFamily, std::pair<std::vector<Output<char>>, std::vector<Output<char>>>);
}

TEST("Delimit regular", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Del1, "abc,abc,abc,,abc,abc,abc", vec_type({ "abc", "abc", "abc" }), ",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, ",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del1, "abc ,abc,abc,abc,,abc,abc,abc", vec_type({ "abc" }), " ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del1, "");
	ASSERT_PARSE_SUCCESS(Del2, "abc.abc abc .abc.abc abc", vec_type({ "abc", "abc", "abc" }), " .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del2, "abc abc.abc .abc.abc abc", vec_type({ "abc", "abc", "abc" }), " .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, ".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, " abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del2, "");
	ASSERT_PARSE_SUCCESS(Del3, "??,??,??,,??,??,??", vec_type({ "??", "??", "??" }), ",,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, ",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del3, "?? ,??,??,??,,??,??,??", vec_type({ "??" }), " ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del3, "");
	ASSERT_PARSE_SUCCESS(Del4, "??.?? ?? .??.?? ??", vec_type({ "??", "??", "??" }), " .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del4, "?? ??.?? .??.?? ??", vec_type({ "??", "??", "??" }), " .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, ".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, " ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del4, "");
}

TEST("Delimit regular", "Parse all inverted")
{
	ASSERT_PARSE_FAILURE(Del5, "abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Del5, ",abc,abc,abc,,abc,abc,abc", vec_type({ ",", ",", ",", "," }), ",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, "abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Del5, "");
	ASSERT_PARSE_FAILURE(Del6, "abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, "abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, ".abc abc.abc .abc.abc abc", vec_type({ ".", " ", ".", " " }), ".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Del6, " abc abc.abc .abc.abc abc", vec_type({ " ", " ", ".", " " }), ".abc.abc abc");
	ASSERT_PARSE_FAILURE(Del6, "");
	ASSERT_PARSE_FAILURE(Del7, "??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Del7, ",??,??,??,,??,??,??", vec_type({ ",", ",", ",", "," }), ",??,??,??");
	ASSERT_PARSE_FAILURE(Del7, "?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Del7, "");
	ASSERT_PARSE_FAILURE(Del8, "??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, "?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, ".?? ??.?? .??.?? ??", vec_type({ ".", " ", ".", " " }), ".??.?? ??");
	ASSERT_PARSE_SUCCESS(Del8, " ?? ??.?? .??.?? ??", vec_type({ " ", " ", ".", " " }), ".??.?? ??");
	ASSERT_PARSE_FAILURE(Del8, "");
}

TEST("Delimit keep", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Dek1, "abc,abc,abc,,abc,abc,abc", std::pair(vec_type({ "abc", "abc", "abc" }), vec_type({ ",", "," })), ",,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, ",abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek1, "abc ,abc,abc,abc,,abc,abc,abc", std::pair(vec_type({ "abc" }), vec_type{}), " ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek1, "");
	ASSERT_PARSE_SUCCESS(Dek2, "abc.abc abc .abc.abc abc", std::pair(vec_type({ "abc", "abc", "abc" }), vec_type({ ".", " " })), " .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek2, "abc abc.abc .abc.abc abc", std::pair(vec_type({ "abc", "abc", "abc" }), vec_type({ " ", "." })), " .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, ".abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, " abc abc.abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek2, "");
	ASSERT_PARSE_SUCCESS(Dek3, "??,??,??,,??,??,??", std::pair(vec_type({ "??", "??", "??" }), vec_type({ ",", "," })), ",,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, ",??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek3, "?? ,??,??,??,,??,??,??", std::pair(vec_type({ "??" }), vec_type{}), " ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek3, "");
	ASSERT_PARSE_SUCCESS(Dek4, "??.?? ?? .??.?? ??", std::pair(vec_type({ "??", "??", "??" }), vec_type({ ".", " " })), " .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek4, "?? ??.?? .??.?? ??", std::pair(vec_type({ "??", "??", "??" }), vec_type({ " ", "." })), " .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, ".?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, " ?? ??.?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek4, "");
}

TEST("Delimit keep", "Parse all inverted")
{
	ASSERT_PARSE_FAILURE(Dek5, "abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_SUCCESS(Dek5, ",abc,abc,abc,,abc,abc,abc", std::pair(vec_type({ ",", ",", ",", ","}), vec_type({ "abc", "abc", "abc" })), ",abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, "abc ,abc,abc,abc,,abc,abc,abc");
	ASSERT_PARSE_FAILURE(Dek5, "");
	ASSERT_PARSE_FAILURE(Dek6, "abc.abc abc .abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, "abc abc.abc .abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, ".abc abc.abc .abc.abc abc", std::pair(vec_type({ ".", " ", ".", " "}), vec_type({ "abc", "abc", "abc" })), ".abc.abc abc");
	ASSERT_PARSE_SUCCESS(Dek6, " abc abc.abc .abc.abc abc", std::pair(vec_type({ " ", " ", ".", " "}), vec_type({ "abc", "abc", "abc" })), ".abc.abc abc");
	ASSERT_PARSE_FAILURE(Dek6, "");
	ASSERT_PARSE_FAILURE(Dek7, "??,??,??,,??,??,??");
	ASSERT_PARSE_SUCCESS(Dek7, ",??,??,??,,??,??,??", std::pair(vec_type({ ",", ",", ",", ","}), vec_type({ "??", "??", "??" })), ",??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, "?? ,??,??,??,,??,??,??");
	ASSERT_PARSE_FAILURE(Dek7, "");
	ASSERT_PARSE_FAILURE(Dek8, "??.?? ?? .??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, "?? ??.?? .??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, ".?? ??.?? .??.?? ??", std::pair(vec_type({ ".", " ", ".", " "}), vec_type({ "??", "??", "??" })), ".??.?? ??");
	ASSERT_PARSE_SUCCESS(Dek8, " ?? ??.?? .??.?? ??", std::pair(vec_type({ " ", " ", ".", " "}), vec_type({ "??", "??", "??" })), ".??.?? ??");
	ASSERT_PARSE_FAILURE(Dek8, "");
}
