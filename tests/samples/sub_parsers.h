#pragma once
#include <k3/tok3n.h>
#include "samples/basic.h"

TOK3N_BEGIN_NAMESPACE(tests)

inline namespace sub
{
	using _11 = L1;
	using _12 = OC1;
	using _13 = Choice<L1, OC1>;
	using _14 = Sequence<L1, OC1>;

	using _21 = ABC;
	using _22 = OneOrMore<ABC>;
	using _23 = Maybe<Choice<ABC, QQ>>;
	using _24 = Sequence<ABC, ZeroOrMore<QQ>>;
	using _25 = Sequence<OneOrMore<ABC>, Maybe<Choice<ABC, QQ>>>;
}

TOK3N_END_NAMESPACE(tests)
