// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("filter modifier");

TEST("filter modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(fil1, filter<filter_func1>(+abc));
	ASSERT_PARSER_VALUES_EQ(fil2, filter<filter_func2>(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(fil3, filter<filter_func3>(abc >> *qq));
}

TEST("filter modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(fil1, +abc % filter<filter_func1>);
	ASSERT_PARSER_VALUES_EQ(fil2, ~(abc | qq) % filter<filter_func2>);
	ASSERT_PARSER_VALUES_EQ(fil3, (abc >> *qq) % filter<filter_func3>);
}

TEST("filter modifier", "non consteval")
{
	(filter<true_filter>(any1)).parse(TT("abc"));
	(any1 % filter<true_filter>).parse(TT("abc"));
}



#define FILTER_MODIFIER_ASSERTER(P)                                                                                             \
	[]<parser PP>(PP) {                                                                                                         \
		DEP_ASSERT_MODIFIER_CALLABLE_R(filter<true_filter>, (PP{}), (filter_parser<PP, integral_constant<true_filter>>{}),      \
			                           filter<true_filter>, (P{}),  (filter_parser<P, integral_constant<true_filter>>{}));      \
		DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, filter<true_filter>, (filter_parser<PP, integral_constant<true_filter>>{}), \
			                                  P{},  filter<true_filter>, (filter_parser<P, integral_constant<true_filter>>{})); \
	}(P{});

TEST("filter modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(FILTER_MODIFIER_ASSERTER);
}
