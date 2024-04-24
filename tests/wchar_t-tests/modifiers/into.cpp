#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("into modifier");

TEST("into modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(int1, into<Class1>(spacedot));
	ASSERT_PARSER_VALUES_EQ(int2, into<Class2>(abc >> spacedot));
}

TEST("into modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(int1, spacedot % into<Class1>);
	ASSERT_PARSER_VALUES_EQ(int2, (abc >> spacedot) % into<Class2>);
}

TEST("into modifier", "non consteval")
{
	(into<Sink>(any1)).parse(L"abc");
	(any1 % into<Sink>).parse(L"abc");
}
