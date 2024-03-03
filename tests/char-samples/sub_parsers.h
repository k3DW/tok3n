#pragma once
#include <k3/tok3n.h>
#include "char-samples/basic.h"

inline namespace sub
{
	using _11 = All1;
	using _12 = Any1;
	using _13 = Choice<All1, Any1>;
	using _14 = Sequence<All1, Any1>;

	using _21 = ABC;
	using _22 = OneOrMore<ABC>;
	using _23 = Maybe<Choice<ABC, QQ>>;
	using _24 = Sequence<ABC, ZeroOrMore<QQ>>;
	using _25 = Sequence<OneOrMore<ABC>, Maybe<Choice<ABC, QQ>>>;
}
