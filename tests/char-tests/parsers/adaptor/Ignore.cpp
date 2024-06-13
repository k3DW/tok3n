#include "char-tests/samples.h"

FIXTURE("Ignore");

TEST("Ignore", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Ign1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Ign2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Ign3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Ign4, value_type);
	ASSERT_PARSER_VALUE_TYPE(Ign5, value_type);

	ASSERT_IS_PARSER(Ign1, char, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign2, char, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign3, char, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign4, char, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign5, char, IgnoreFamily, void);

	ASSERT_IS_PARSER(Ign1, wchar_t, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign2, wchar_t, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign3, wchar_t, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign4, wchar_t, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign5, wchar_t, IgnoreFamily, void);

	ASSERT_IS_PARSER(Ign1, int, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign2, int, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign3, int, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign4, int, IgnoreFamily, void);
	ASSERT_IS_PARSER(Ign5, int, IgnoreFamily, void);
}

TEST("Ignore", "Parse all")
{
	ASSERT_PARSE_SUCCESS_VOID(Ign1, "abcabc", "abc");
	ASSERT_PARSE_FAILURE(Ign1, "Abcabc");
	ASSERT_PARSE_FAILURE(Ign1, " abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign2, "abcabcabcab", "ab");
	ASSERT_PARSE_FAILURE(Ign2, "");
	ASSERT_PARSE_FAILURE(Ign2, "ab");
	ASSERT_PARSE_SUCCESS_VOID(Ign2, "abc", "");

	ASSERT_PARSE_SUCCESS_VOID(Ign3, "abcabc", "abc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, "a??bcabc", "a??bcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, "", "");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, "??abcabc", "abcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, " ??abcabc", " ??abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc???????", "?");
	ASSERT_PARSE_FAILURE(Ign4, "??abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc??abc???????", "abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc ??abc???????", " ??abc???????");
	ASSERT_PARSE_FAILURE(Ign4, "");

	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc??", "");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc", "");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc ??", " ??");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, "abc", "");
	ASSERT_PARSE_FAILURE(Ign5, " abc");
	ASSERT_PARSE_FAILURE(Ign5, "");

	ASSERT_PARSE_SUCCESS_VOID(Ign1, L"abcabc", L"abc");
	ASSERT_PARSE_FAILURE(Ign1, L"Abcabc");
	ASSERT_PARSE_FAILURE(Ign1, L" abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign2, L"abcabcabcab", L"ab");
	ASSERT_PARSE_FAILURE(Ign2, L"");
	ASSERT_PARSE_FAILURE(Ign2, L"ab");
	ASSERT_PARSE_SUCCESS_VOID(Ign2, L"abc", L"");

	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"abcabc", L"abc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"a??bcabc", L"a??bcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"", L"");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L"??abcabc", L"abcabc");
	ASSERT_PARSE_SUCCESS_VOID(Ign3, L" ??abcabc", L" ??abcabc");

	ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc???????", L"?");
	ASSERT_PARSE_FAILURE(Ign4, L"??abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc??abc???????", L"abc???????");
	ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc ??abc???????", L" ??abc???????");
	ASSERT_PARSE_FAILURE(Ign4, L"");

	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc??", L"");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc", L"");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc ??", L" ??");
	ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abc", L"");
	ASSERT_PARSE_FAILURE(Ign5, L" abc");
	ASSERT_PARSE_FAILURE(Ign5, L"");

	ASSERT_PARSE_SUCCESS_VOID(Ign1, e<int>("abcabc"), e<int>("abc"));
	ASSERT_PARSE_FAILURE(Ign1, e<int>("Abcabc"));
	ASSERT_PARSE_FAILURE(Ign1, e<int>(" abcabc"));

	ASSERT_PARSE_SUCCESS_VOID(Ign2, e<int>("abcabcabcab"), e<int>("ab"));
	ASSERT_PARSE_FAILURE(Ign2, e<int>());
	ASSERT_PARSE_FAILURE(Ign2, e<int>("ab"));
	ASSERT_PARSE_SUCCESS_VOID(Ign2, e<int>("abc"), e<int>());

	ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>("abcabc"), e<int>("abc"));
	ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>("a??bcabc"), e<int>("a??bcabc"));
	ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>(), e<int>());
	ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>("??abcabc"), e<int>("abcabc"));
	ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>(" ??abcabc"), e<int>(" ??abcabc"));

	ASSERT_PARSE_SUCCESS_VOID(Ign4, e<int>("abc???????"), e<int>("?"));
	ASSERT_PARSE_FAILURE(Ign4, e<int>("??abc???????"));
	ASSERT_PARSE_SUCCESS_VOID(Ign4, e<int>("abc??abc???????"), e<int>("abc???????"));
	ASSERT_PARSE_SUCCESS_VOID(Ign4, e<int>("abc ??abc???????"), e<int>(" ??abc???????"));
	ASSERT_PARSE_FAILURE(Ign4, e<int>());

	ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abcabcabcabc??"), e<int>());
	ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abcabcabcabc"), e<int>());
	ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abcabcabcabc ??"), e<int>(" ??"));
	ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abc"), e<int>());
	ASSERT_PARSE_FAILURE(Ign5, e<int>(" abc"));
	ASSERT_PARSE_FAILURE(Ign5, e<int>());
}
