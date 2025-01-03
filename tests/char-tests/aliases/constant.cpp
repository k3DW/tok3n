// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("constant_parser");

TEST("constant_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Con1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Con2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Con3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Con4, value_type);

	ASSERT_IS_PARSER(Con1, char, map_family, int);
	ASSERT_IS_PARSER(Con2, char, map_family, char);
	ASSERT_IS_PARSER(Con3, char, map_family, bool);
	ASSERT_IS_PARSER(Con4, char, map_family, std::nullptr_t);

	ASSERT_IS_PARSER(Con1, wchar_t, map_family, int);
	ASSERT_IS_PARSER(Con2, wchar_t, map_family, char);
	ASSERT_IS_PARSER(Con3, wchar_t, map_family, bool);
	ASSERT_IS_PARSER(Con4, wchar_t, map_family, std::nullptr_t);

	ASSERT_IS_PARSER(Con1, int, map_family, int);
	ASSERT_IS_PARSER(Con2, int, map_family, char);
	ASSERT_IS_PARSER(Con3, int, map_family, bool);
	ASSERT_IS_PARSER(Con4, int, map_family, std::nullptr_t);
}

TEST("constant_parser", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Con1, "abcabcabcab", 1, "ab");
	ASSERT_PARSE_FAILURE(Con1, "");
	ASSERT_PARSE_FAILURE(Con1, "ab");
	ASSERT_PARSE_SUCCESS(Con1, "abc", 1, "");
		
	ASSERT_PARSE_SUCCESS(Con2, "abcabc", 't', "abc");
	ASSERT_PARSE_SUCCESS(Con2, "a??bcabc", 't', "a??bcabc");
	ASSERT_PARSE_SUCCESS(Con2, "", 't', "");
	ASSERT_PARSE_SUCCESS(Con2, "??abcabc", 't', "abcabc");
	ASSERT_PARSE_SUCCESS(Con2, " ??abcabc", 't', " ??abcabc");
		
	ASSERT_PARSE_SUCCESS(Con3, "abc???????", true, "?");
	ASSERT_PARSE_FAILURE(Con3, "??abc???????");
	ASSERT_PARSE_SUCCESS(Con3, "abc??abc???????", true, "abc???????");
	ASSERT_PARSE_SUCCESS(Con3, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Con3, "");
		
	ASSERT_PARSE_SUCCESS(Con4, "abcabcabcabc??", nullptr, "");
	ASSERT_PARSE_SUCCESS(Con4, "abcabcabcabc", nullptr, "");
	ASSERT_PARSE_SUCCESS(Con4, "abcabcabcabc ??", nullptr, " ??");
	ASSERT_PARSE_SUCCESS(Con4, "abc", nullptr, "");
	ASSERT_PARSE_FAILURE(Con4, " abc");
	ASSERT_PARSE_FAILURE(Con4, "");

	ASSERT_PARSE_SUCCESS(Con1, L"abcabcabcab", 1, L"ab");
	ASSERT_PARSE_FAILURE(Con1, L"");
	ASSERT_PARSE_FAILURE(Con1, L"ab");
	ASSERT_PARSE_SUCCESS(Con1, L"abc", 1, L"");
		
	ASSERT_PARSE_SUCCESS(Con2, L"abcabc", 't', L"abc");
	ASSERT_PARSE_SUCCESS(Con2, L"a??bcabc", 't', L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Con2, L"", 't', L"");
	ASSERT_PARSE_SUCCESS(Con2, L"??abcabc", 't', L"abcabc");
	ASSERT_PARSE_SUCCESS(Con2, L" ??abcabc", 't', L" ??abcabc");
		
	ASSERT_PARSE_SUCCESS(Con3, L"abc???????", true, L"?");
	ASSERT_PARSE_FAILURE(Con3, L"??abc???????");
	ASSERT_PARSE_SUCCESS(Con3, L"abc??abc???????", true, L"abc???????");
	ASSERT_PARSE_SUCCESS(Con3, L"abc ??abc???????", true, L" ??abc???????");
	ASSERT_PARSE_FAILURE(Con3, L"");
		
	ASSERT_PARSE_SUCCESS(Con4, L"abcabcabcabc??", nullptr, L"");
	ASSERT_PARSE_SUCCESS(Con4, L"abcabcabcabc", nullptr, L"");
	ASSERT_PARSE_SUCCESS(Con4, L"abcabcabcabc ??", nullptr, L" ??");
	ASSERT_PARSE_SUCCESS(Con4, L"abc", nullptr, L"");
	ASSERT_PARSE_FAILURE(Con4, L" abc");
	ASSERT_PARSE_FAILURE(Con4, L"");

	ASSERT_PARSE_SUCCESS(Con1, e<int>("abcabcabcab"), 1, e<int>("ab"));
	ASSERT_PARSE_FAILURE(Con1, e<int>(""));
	ASSERT_PARSE_FAILURE(Con1, e<int>("ab"));
	ASSERT_PARSE_SUCCESS(Con1, e<int>("abc"), 1, e<int>(""));
		
	ASSERT_PARSE_SUCCESS(Con2, e<int>("abcabc"), 't', e<int>("abc"));
	ASSERT_PARSE_SUCCESS(Con2, e<int>("a??bcabc"), 't', e<int>("a??bcabc"));
	ASSERT_PARSE_SUCCESS(Con2, e<int>(""), 't', e<int>(""));
	ASSERT_PARSE_SUCCESS(Con2, e<int>("??abcabc"), 't', e<int>("abcabc"));
	ASSERT_PARSE_SUCCESS(Con2, e<int>(" ??abcabc"), 't', e<int>(" ??abcabc"));
		
	ASSERT_PARSE_SUCCESS(Con3, e<int>("abc???????"), true, e<int>("?"));
	ASSERT_PARSE_FAILURE(Con3, e<int>("??abc???????"));
	ASSERT_PARSE_SUCCESS(Con3, e<int>("abc??abc???????"), true, e<int>("abc???????"));
	ASSERT_PARSE_SUCCESS(Con3, e<int>("abc ??abc???????"), true, e<int>(" ??abc???????"));
	ASSERT_PARSE_FAILURE(Con3, e<int>(""));
		
	ASSERT_PARSE_SUCCESS(Con4, e<int>("abcabcabcabc??"), nullptr, e<int>(""));
	ASSERT_PARSE_SUCCESS(Con4, e<int>("abcabcabcabc"), nullptr, e<int>(""));
	ASSERT_PARSE_SUCCESS(Con4, e<int>("abcabcabcabc ??"), nullptr, e<int>(" ??"));
	ASSERT_PARSE_SUCCESS(Con4, e<int>("abc"), nullptr, e<int>(""));
	ASSERT_PARSE_FAILURE(Con4, e<int>(" abc"));
	ASSERT_PARSE_FAILURE(Con4, e<int>(""));
}
