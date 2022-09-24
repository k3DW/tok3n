#include "pch.h"

BEGIN_NAMESPACE_TOK3N(tests::compound::combine)

constexpr Choice<Literal<"ab">, NotChar<"cd">> c1;
constexpr Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">> c2;

void choice_Choice()
{
	assert
		, (c1 | c1) == c1
		, (c2 | c2) == c2
		, (c1 | c2) == Choice<Literal<"ab">, NotChar<"cd">, NotChar<'z'>, Literal<"ab">, OneChar<"cd">>{}
		, (c2 | c1) == Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">, Literal<"ab">, NotChar<"cd">>{}
		;
}



constexpr Sequence<Literal<"ab">, NotChar<"cd">> s1;
constexpr Sequence<Literal<"ab">, OneChar<"cd">, NotChar<'z'>> s2;

void sequence_Sequence()
{
	assert
		, (s1 >> s2) == Sequence<Literal<"ab">, NotChar<"cd">, Literal<"ab">, OneChar<"cd">, NotChar<'z'>>{}
		, (s2 >> s1) == Sequence<Literal<"ab">, OneChar<"cd">, NotChar<'z'>, Literal<"ab">, NotChar<"cd">>{}
		;
}

END_NAMESPACE_TOK3N(tests::compound::combine)
