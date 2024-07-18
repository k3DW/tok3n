#include "samples.h"

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
	(into<Sink>(any1)).parse(TT("abc"));
	(any1 % into<Sink>).parse(TT("abc"));
}



#define INTO_MODIFIER_ASSERTER(P)                                                   \
	[]<Parser PP>(PP) {                                                             \
		DEP_ASSERT_MODIFIER_CALLABLE_R(into<Sink>, (PP{}), (Into<PP, Sink>{}),      \
			                           into<Sink>, (P{}),  (Into<P, Sink>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, into<Sink>, (Into<PP, Sink>{}), \
			                                  P{},  into<Sink>, (Into<P, Sink>{})); \
	}(P{});

TEST("into modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(INTO_MODIFIER_ASSERTER);
}
