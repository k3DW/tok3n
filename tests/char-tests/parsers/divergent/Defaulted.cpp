#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("Defaulted");

TEST("Defaulted", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Def1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Def2, value_type);

	ASSERT_IS_PARSER(Def1, char, map_family, int);
	ASSERT_IS_PARSER(Def2, char, map_family, Class3);

	ASSERT_IS_PARSER(Def1, wchar_t, map_family, int);
	ASSERT_IS_PARSER(Def2, wchar_t, map_family, Class3);

	ASSERT_IS_PARSER(Def1, int, map_family, int);
	ASSERT_IS_PARSER(Def2, int, map_family, Class3);
}

TEST("Defaulted", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Def1, "abcabcabcab", 0, "ab");
	ASSERT_PARSE_FAILURE(Def1, "");
	ASSERT_PARSE_FAILURE(Def1, "ab");
	ASSERT_PARSE_SUCCESS(Def1, "abc", 0, "");

	ASSERT_PARSE_SUCCESS(Def2, "abcabc", Class3{}, "abc");
	ASSERT_PARSE_SUCCESS(Def2, "a??bcabc", Class3{}, "a??bcabc");
	ASSERT_PARSE_SUCCESS(Def2, "", Class3{}, "");
	ASSERT_PARSE_SUCCESS(Def2, "??abcabc", Class3{}, "abcabc");
	ASSERT_PARSE_SUCCESS(Def2, " ??abcabc", Class3{}, " ??abcabc");

	ASSERT_PARSE_SUCCESS(Def1, L"abcabcabcab", 0, L"ab");
	ASSERT_PARSE_FAILURE(Def1, L"");
	ASSERT_PARSE_FAILURE(Def1, L"ab");
	ASSERT_PARSE_SUCCESS(Def1, L"abc", 0, L"");

	ASSERT_PARSE_SUCCESS(Def2, L"abcabc", Class3{}, L"abc");
	ASSERT_PARSE_SUCCESS(Def2, L"a??bcabc", Class3{}, L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Def2, L"", Class3{}, L"");
	ASSERT_PARSE_SUCCESS(Def2, L"??abcabc", Class3{}, L"abcabc");
	ASSERT_PARSE_SUCCESS(Def2, L" ??abcabc", Class3{}, L" ??abcabc");

	ASSERT_PARSE_SUCCESS(Def1, e<int>("abcabcabcab"), 0, e<int>("ab"));
	ASSERT_PARSE_FAILURE(Def1, e<int>(""));
	ASSERT_PARSE_FAILURE(Def1, e<int>("ab"));
	ASSERT_PARSE_SUCCESS(Def1, e<int>("abc"), 0, e<int>(""));

	ASSERT_PARSE_SUCCESS(Def2, e<int>("abcabc"), Class3{}, e<int>("abc"));
	ASSERT_PARSE_SUCCESS(Def2, e<int>("a??bcabc"), Class3{}, e<int>("a??bcabc"));
	ASSERT_PARSE_SUCCESS(Def2, e<int>(""), Class3{}, e<int>(""));
	ASSERT_PARSE_SUCCESS(Def2, e<int>("??abcabc"), Class3{}, e<int>("abcabc"));
	ASSERT_PARSE_SUCCESS(Def2, e<int>(" ??abcabc"), Class3{}, e<int>(" ??abcabc"));
}
