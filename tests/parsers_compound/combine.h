#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(compound::combine)

constexpr Choice<Literal<"ab">, NotChar<"cd">> c1;
constexpr Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">> c2;

void choice_of_two_Choice()
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

void sequence_of_two_Sequence()
{
	assert
		, (s1 >> s1) == Sequence<Literal<"ab">, NotChar<"cd">, Literal<"ab">, NotChar<"cd">>{}
		, (s2 >> s2) == Sequence<Literal<"ab">, OneChar<"cd">, NotChar<'z'>, Literal<"ab">, OneChar<"cd">, NotChar<'z'>>{}
		, (s1 >> s2) == Sequence<Literal<"ab">, NotChar<"cd">, Literal<"ab">, OneChar<"cd">, NotChar<'z'>>{}
		, (s2 >> s1) == Sequence<Literal<"ab">, OneChar<"cd">, NotChar<'z'>, Literal<"ab">, NotChar<"cd">>{}
		;
}



template <auto p1, auto p2>
constexpr bool Choice_operator_is_valid = requires { p1 | p2; };

void Choice_operator()
{
	assert
		, not Choice_operator_is_valid<c1, s1>
		, not Choice_operator_is_valid<c2, s1>
		, not Choice_operator_is_valid<c1, s2>
		, not Choice_operator_is_valid<c2, s2>
		, not Choice_operator_is_valid<s1, c1>
		, not Choice_operator_is_valid<s1, c2>
		, not Choice_operator_is_valid<s2, c1>
		, not Choice_operator_is_valid<s2, c2>
		, not Choice_operator_is_valid<s1, s2>
		, not Choice_operator_is_valid<s2, s1>
		;
}



void Sequence_operator()
{
	assert
		, c1 >> s1 == Sequence<Choice<Literal<"ab">, NotChar<"cd">>, Literal<"ab">, NotChar<"cd">>{}
		, c1 >> s2 == Sequence<Choice<Literal<"ab">, NotChar<"cd">>, Literal<"ab">, OneChar<"cd">, NotChar<'z'>>{}
		, c2 >> s1 == Sequence<Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">>, Literal<"ab">, NotChar<"cd">>{}
		, c2 >> s2 == Sequence<Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">>, Literal<"ab">, OneChar<"cd">, NotChar<'z'>>{}
		, s1 >> c1 == Sequence<Literal<"ab">, NotChar<"cd">, Choice<Literal<"ab">, NotChar<"cd">>>{}
		, s2 >> c1 == Sequence<Literal<"ab">, OneChar<"cd">, NotChar<'z'>, Choice<Literal<"ab">, NotChar<"cd">>>{}
		, s1 >> c2 == Sequence<Literal<"ab">, NotChar<"cd">, Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">>>{}
		, s2 >> c2 == Sequence<Literal<"ab">, OneChar<"cd">, NotChar<'z'>, Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">>>{}
		, c1 >> c2 == Sequence<Choice<Literal<"ab">, NotChar<"cd">>, Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">>>{}
		, c2 >> c1 == Sequence<Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">>, Choice<Literal<"ab">, NotChar<"cd">>>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(compound::combine)
