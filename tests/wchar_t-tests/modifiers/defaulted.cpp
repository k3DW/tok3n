#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("defaulted modifier");

TEST("defaulted modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(def1, defaulted<int>(+abc));
	ASSERT_PARSER_VALUES_EQ(def2, defaulted<Class3>(~(abc | qq)));
}

TEST("defaulted modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(def1, +abc % defaulted<int>);
	ASSERT_PARSER_VALUES_EQ(def2, ~(abc | qq) % defaulted<Class3>);
}

TEST("defaulted modifier", "non consteval")
{
	(defaulted<int>(any1)).parse(L"abc");
	(any1 % defaulted<int>).parse(L"abc");
}
