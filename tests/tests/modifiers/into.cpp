#include "pch.h"

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



#define INTO_MODIFIER_ASSERTER(P)                                                       \
	[&]<Parser PP>(PP) {                                                                \
		if constexpr (std::same_as<typename PP::result_type, void>)                     \
		{                                                                               \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(into<Sink>, (PP{}),                        \
				                             into<Sink>, (P{}));                        \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, into<Sink>,                   \
				                                    P{},  into<Sink>);                  \
		}                                                                               \
		else                                                                            \
		{                                                                               \
			DEP_ASSERT_MODIFIER_CALLABLE_R(into<Sink>, (PP{}), (Into<PP, Sink>{}),      \
				                           into<Sink>, (P{}),  (Into<P, Sink>{}));      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, into<Sink>, (Into<PP, Sink>{}), \
				                                  P{},  into<Sink>, (Into<P, Sink>{})); \
		}                                                                               \
	}(P{});

TEST("into modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(INTO_MODIFIER_ASSERTER);
}
