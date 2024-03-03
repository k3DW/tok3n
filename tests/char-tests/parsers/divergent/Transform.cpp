#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("Transform");

TEST("Transform", "Requirements")
{
	ASSERT_IS_PARSER(Tra1, TransformFamily, std::size_t);
	ASSERT_IS_PARSER(Tra2, TransformFamily, std::vector<char>);
	ASSERT_IS_PARSER(Tra3, TransformFamily, bool);
	ASSERT_IS_PARSER(Tra4, TransformFamily, std::size_t);
}

TEST("Transform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Tra1, "abcabcabcab", 3, "ab");
	ASSERT_PARSE_FAILURE(Tra1, "");
	ASSERT_PARSE_FAILURE(Tra1, "ab");
	ASSERT_PARSE_SUCCESS(Tra1, "abc", 1, "");
		
	ASSERT_PARSE_SUCCESS(Tra2, "abcabc", std::vector({ 'a', 'b', 'c' }), "abc");
	ASSERT_PARSE_SUCCESS(Tra2, "a??bcabc", std::vector<char>{}, "a??bcabc");
	ASSERT_PARSE_SUCCESS(Tra2, "", std::vector<char>{}, "");
	ASSERT_PARSE_SUCCESS(Tra2, "??abcabc", std::vector<char>({ '?', '?' }), "abcabc");
	ASSERT_PARSE_SUCCESS(Tra2, " ??abcabc", std::vector<char>{}, " ??abcabc");
		
	ASSERT_PARSE_SUCCESS(Tra3, "abc???????", false, "?");
	ASSERT_PARSE_FAILURE(Tra3, "??abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, "abc??abc???????", false, "abc???????");
	ASSERT_PARSE_SUCCESS(Tra3, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Tra3, "");
		
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Tra4, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Tra4, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Tra4, " abc");
	ASSERT_PARSE_FAILURE(Tra4, "");
}

TEST("Transform", "Move only")
{
	using T = MoveOnlyWrapper<Output<char>>;
	using P = Transform<ABC, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
	ASSERT_PARSE_FAILURE(P, "dcba");
	ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
}

TEST("Transform", "Copy only")
{
	using T = CopyOnlyWrapper<Output<char>>;
	using P = Transform<ABC, Const<T::make>>;

	ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
	ASSERT_PARSE_FAILURE(P, "dcba");
	ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
}
