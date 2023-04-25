#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

inline void ZeroOrMore_Maybe()
{
	assert
		, *may1 == zom1
		, **may1 == zom1
		, ***may1 == zom1
		, *may2 == zom2
		, **may2 == zom2
		, ***may2 == zom2
		, *may3 == zom3
		, **may3 == zom3
		, ***may3 == zom3
		, *may4 == zom4
		, **may4 == zom4
		, ***may4 == zom4
		;
}

inline void ZeroOrMore_OneOrMore()
{
	assert
		, *oom1 == zom1
		, **oom1 == zom1
		, ***oom1 == zom1
		, *oom2 == zom2
		, **oom2 == zom2
		, ***oom2 == zom2
		, *oom3 == zom3
		, **oom3 == zom3
		, ***oom3 == zom3
		, *oom4 == zom4
		, **oom4 == zom4
		, ***oom4 == zom4
		;
}

inline void ZeroOrMore_ZeroOrMore()
{
	assert
		, *zom1 == zom1
		, **zom1 == zom1
		, ***zom1 == zom1
		, *zom2 == zom2
		, **zom2 == zom2
		, ***zom2 == zom2
		, *zom3 == zom3
		, **zom3 == zom3
		, ***zom3 == zom3
		, *zom4 == zom4
		, **zom4 == zom4
		, ***zom4 == zom4
		;
}



constexpr auto zero_or_more_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { *P{}; }, "zero_or_more operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { *P{}; },               "zero_or_more operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( requires { { *P{} } -> Parser; }, "zero_or_more operator compiles, but doesn't give a Parser" );

		if constexpr (P::type == MaybeType)
			TOK3N_ASSERT_P( *P{} == ZeroOrMore<underlying::parser<P>>{}, "zero_or_more operator of Maybe parser should give ZeroOrMore parser of the underlying" );

		else if constexpr (P::type == OneOrMoreType)
			TOK3N_ASSERT_P( *P{} == ZeroOrMore<underlying::parser<P>>{}, "zero_or_more operator of OneOrMore parser should give ZeroOrMore parser of the underlying" );

		else if constexpr (P::type == ZeroOrMoreType)
			TOK3N_ASSERT_P( *P{} == P{}, "zero_or_more operator of ZeroOrMore parser should give itself" );

		else
			TOK3N_ASSERT_P( *P{} == ZeroOrMore<P>{}, "zero_or_more operator of any other parser should give ZeroOrMore parser of the argument" );
	}

	return true;
};

inline void zero_or_more_anything()
{
	assert
		, check_all_samples(zero_or_more_checker)
		;
}

TOK3N_END_NAMESPACE(tests)
