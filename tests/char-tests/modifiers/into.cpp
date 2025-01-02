// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

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



#define INTO_MODIFIER_ASSERTER(P)                                                          \
	[]<parser PP>(PP) {                                                                    \
		DEP_ASSERT_MODIFIER_CALLABLE_R(into<Sink>, (PP{}), (into_parser<PP, Sink>{}),      \
			                           into<Sink>, (P{}),  (into_parser<P, Sink>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, into<Sink>, (into_parser<PP, Sink>{}), \
			                                  P{},  into<Sink>, (into_parser<P, Sink>{})); \
	}(P{});

TEST("into modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(INTO_MODIFIER_ASSERTER);
}
