#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("JoinOneOrMoreBasic");

using Joi_Oom_OC = Join<OneOrMore<any_of_parser<TT("123")>>>;
using Joi_Oom_NC = Join<OneOrMore<none_of_parser<TT("123")>>>;
using Joi_Oom_L  = Join<OneOrMore<all_of_parser<TT("123")>>>;

TEST("JoinOneOrMoreBasic", "Requirements")
{
    ASSERT_PARSER_VALUE_TYPE(Joi_Oom_OC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Oom_NC, value_type);
    ASSERT_PARSER_VALUE_TYPE(Joi_Oom_L, value_type);

    ASSERT_IS_PARSER(Joi_Oom_OC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_Oom_NC, char, join_family, output_span<char>);
    ASSERT_IS_PARSER(Joi_Oom_L, char, join_family, output_span<char>);

    ASSERT_IS_PARSER(Joi_Oom_OC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Oom_NC, wchar_t, join_family, output_span<wchar_t>);
    ASSERT_IS_PARSER(Joi_Oom_L, wchar_t, join_family, output_span<wchar_t>);

    ASSERT_IS_PARSER(Joi_Oom_OC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_Oom_NC, int, join_family, output_span<int>);
    ASSERT_IS_PARSER(Joi_Oom_L, int, join_family, output_span<int>);
}

TEST("JoinOneOrMoreBasic", "OneOrMore<any_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12321321", "12321321", "");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "1232 1321", "1232", " 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, "012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"12321321", L"12321321", L"");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"1232 1321", L"1232", L" 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, L"12341321", L"123", L"41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, e<int>("12321321"), e<int>("12321321"), e<int>(""));
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, e<int>("1232 1321"), e<int>("1232"), e<int>(" 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_OC, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_OC, e<int>("012341321"));
}

TEST("JoinOneOrMoreBasic", "OneOrMore<none_of_parser>")
{
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, " 12321321", " ", "12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, "12341321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, "012341321", "0", "12341321");

    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"1232 1321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, L" 12321321", L" ", L"12321321");
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, L"12341321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, L"012341321", L"0", L"12341321");

    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("12321321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("1232 1321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, e<int>(" 12321321"), e<int>(" "), e<int>("12321321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_NC, e<int>("12341321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_NC, e<int>("012341321"), e<int>("0"), e<int>("12341321"));
}

TEST("JoinOneOrMoreBasic", "OneOrMore<all_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12321321", "123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12312321321", "123123", "21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "1232 1321", "123", "2 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, " 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, "12341321", "123", "41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, "012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12321321", L"123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12312321321", L"123123", L"21321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"1232 1321", L"123", L"2 1321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L" 12321321");
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, L"12341321", L"123", L"41321");
    ASSERT_PARSE_FAILURE(Joi_Oom_L, L"012341321");

    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("12321321"), e<int>("123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("12312321321"), e<int>("123123"), e<int>("21321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("1232 1321"), e<int>("123"), e<int>("2 1321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, e<int>(" 12321321"));
    ASSERT_PARSE_SUCCESS(Joi_Oom_L, e<int>("12341321"), e<int>("123"), e<int>("41321"));
    ASSERT_PARSE_FAILURE(Joi_Oom_L, e<int>("012341321"));
}
