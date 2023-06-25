#include "pch.h"


inline void OneOrMore_Maybe()
{
	assert
		, +may1 == zom1
		, + +may1 == zom1
		, + + +may1 == zom1
		, +may2 == zom2
		, + +may2 == zom2
		, + + +may2 == zom2
		, +may3 == zom3
		, + +may3 == zom3
		, + + +may3 == zom3
		, +may4 == zom4
		, + +may4 == zom4
		, + + +may4 == zom4
		;
}

inline void OneOrMore_OneOrMore()
{
	assert
		, +oom1 == oom1
		, + +oom1 == oom1
		, + + +oom1 == oom1
		, +oom2 == oom2
		, + +oom2 == oom2
		, + + +oom2 == oom2
		, +oom3 == oom3
		, + +oom3 == oom3
		, + + +oom3 == oom3
		, +oom4 == oom4
		, + +oom4 == oom4
		, + + +oom4 == oom4
		;
}

inline void OneOrMore_ZeroOrMore()
{
	assert
		, +zom1 == zom1
		, + +zom1 == zom1
		, + + +zom1 == zom1
		, +zom2 == zom2
		, + +zom2 == zom2
		, + + +zom2 == zom2
		, +zom3 == zom3
		, + +zom3 == zom3
		, + + +zom3 == zom3
		, +zom4 == zom4
		, + +zom4 == zom4
		, + + +zom4 == zom4
		;
}



constexpr auto one_or_more_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { +P{}; }, "one_or_more operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { +P{}; },               "one_or_more operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( requires { { +P{} } -> Parser; }, "one_or_more operator compiles, but doesn't give a Parser" );

		if constexpr (P::type == MaybeType)
			TOK3N_ASSERT_P( +P{} == ZeroOrMore<underlying::parser<P>>{}, "one_or_more operator of Maybe parser should give ZeroOrMore parser of the underlying" );

		else if constexpr (P::type == OneOrMoreType)
			TOK3N_ASSERT_P( +P{} == P{}, "one_or_more operator of OneOrMore parser should give itself" );

		else if constexpr (P::type == ZeroOrMoreType)
			TOK3N_ASSERT_P( +P{} == P{}, "one_or_more operator of ZeroOrMore parser should give itself" );

		else
			TOK3N_ASSERT_P( +P{} == OneOrMore<P>{}, "one_or_more operator of any other parser should give OneOrMore parser of the argument" );
	}

	return true;
};

inline void one_or_more_anything()
{
	assert
		, check_all_samples(one_or_more_checker)
		;
}
