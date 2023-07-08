#include "pch.h"

namespace
{
	using vec_type = std::vector<std::string_view>;
}

TEST("Delimit regular", "Requirements")
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

TEST("Delimit keep", "Requirements")
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
