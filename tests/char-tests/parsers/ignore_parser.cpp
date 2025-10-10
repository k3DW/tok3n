// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("ignore_parser");

TEST("ignore_parser", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Ign1, value_type);
    ASSERT_PARSER_VALUE_TYPE(Ign2, value_type);
    ASSERT_PARSER_VALUE_TYPE(Ign3, value_type);
    ASSERT_PARSER_VALUE_TYPE(Ign4, value_type);
    ASSERT_PARSER_VALUE_TYPE(Ign5, value_type);

    ASSERT_IS_PARSER(Ign1, char, ignore_family, void);
    ASSERT_IS_PARSER(Ign2, char, ignore_family, void);
    ASSERT_IS_PARSER(Ign3, char, ignore_family, void);
    ASSERT_IS_PARSER(Ign4, char, ignore_family, void);
    ASSERT_IS_PARSER(Ign5, char, ignore_family, void);

    ASSERT_IS_PARSER(Ign1, wchar_t, ignore_family, void);
    ASSERT_IS_PARSER(Ign2, wchar_t, ignore_family, void);
    ASSERT_IS_PARSER(Ign3, wchar_t, ignore_family, void);
    ASSERT_IS_PARSER(Ign4, wchar_t, ignore_family, void);
    ASSERT_IS_PARSER(Ign5, wchar_t, ignore_family, void);

    ASSERT_IS_PARSER(Ign1, int, ignore_family, void);
    ASSERT_IS_PARSER(Ign2, int, ignore_family, void);
    ASSERT_IS_PARSER(Ign3, int, ignore_family, void);
    ASSERT_IS_PARSER(Ign4, int, ignore_family, void);
    ASSERT_IS_PARSER(Ign5, int, ignore_family, void);
}

TEST("ignore_parser", "Parse all")
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
