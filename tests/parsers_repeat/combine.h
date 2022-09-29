#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(repeat::combine)

using L = Literal<"literal">;
using OC = OneChar<"abcde">;

constexpr auto oom1 = OneOrMore<L>{};
constexpr auto oom2 = OneOrMore<OC>{};

constexpr auto zom1 = ZeroOrMore<L>{};
constexpr auto zom2 = ZeroOrMore<OC>{};

constexpr auto m1 = Maybe<L>{};
constexpr auto m2 = Maybe<OC>{};



void one_or_more_OneOrMore()
{
	assert
		, +oom1 == oom1
		, + +oom1 == oom1
		, + + +oom1 == oom1
		, +oom2 == oom2
		, + +oom2 == oom2
		, + + +oom2 == oom2
		;
}
void one_or_more_ZeroOrMore()
{
	assert
		, +zom1 == zom1
		, + +zom1 == zom1
		, + + +zom1 == zom1
		, +zom2 == zom2
		, + +zom2 == zom2
		, + + +zom2 == zom2
		;
}
void one_or_more_Maybe()
{
	assert
		, +m1 == zom1
		, + +m1 == zom1
		, + + +m1 == zom1
		, +m2 == zom2
		, + +m2 == zom2
		, + + +m2 == zom2
		;
}



void zero_or_more_OneOrMore()
{
	assert
		, *oom1 == zom1
		, **oom1 == zom1
		, ***oom1 == zom1
		, *oom2 == zom2
		, **oom2 == zom2
		, ***oom2 == zom2
		;
}
void zero_or_more_ZeroOrMore()
{
	assert
		, *zom1 == zom1
		, **zom1 == zom1
		, ***zom1 == zom1
		, *zom2 == zom2
		, **zom2 == zom2
		, ***zom2 == zom2
		;
}
void zero_or_more_Maybe()
{
	assert
		, *m1 == zom1
		, **m1 == zom1
		, ***m1 == zom1
		, *m2 == zom2
		, **m2 == zom2
		, ***m2 == zom2
		;
}



void maybe_OneOrMore()
{
	assert
		, ~oom1 == zom1
		, ~~oom1 == zom1
		, ~~~oom1 == zom1
		, ~oom2 == zom2
		, ~~oom2 == zom2
		, ~~~oom2 == zom2
		;
}
void maybe_ZeroOrMore()
{
	assert
		, ~zom1 == zom1
		, ~~zom1 == zom1
		, ~~~zom1 == zom1
		, ~zom2 == zom2
		, ~~zom2 == zom2
		, ~~~zom2 == zom2
		;
}
void maybe_Maybe()
{
	assert
		, ~m1 == m1
		, ~~m1 == m1
		, ~~~m1 == m1
		, ~m2 == m2
		, ~~m2 == m2
		, ~~~m2 == m2
		;
}

TOK3N_END_NAMESPACE_TESTS(repeat::combine)
