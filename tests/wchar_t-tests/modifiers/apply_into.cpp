#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("apply_into modifier");

TEST("apply_into modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(api1, apply_into<Class2>(abc >> spacedot));
	ASSERT_PARSER_VALUES_EQ(api2, apply_into<Class5>(spacedot >> abc));
}

TEST("apply_into modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(api1, (abc >> spacedot) % apply_into<Class2>);
	ASSERT_PARSER_VALUES_EQ(api2, (spacedot >> abc) % apply_into<Class5>);
}

TEST("apply_into modifier", "non consteval")
{
	(apply_into<Sink>(any1 >> any2)).parse(L"abc");
	((any1 >> any2) % apply_into<Sink>).parse(L"abc");
}
