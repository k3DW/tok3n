#include "pch.h"

inline void prefix()
{
	assert
		, joi1 != join(abc)
		, abc == join(abc)
		, joi2 == join(+abc)
		, joi3 == join(~(abc | qq))
		, joi4 == join(abc >> *qq)
		, joi5 == join(+abc >> ~(abc | qq))
		;
}

inline void infix()
{
	assert
		, joi1 != abc % join
		, abc == abc % join
		, joi2 == +abc % join
		, joi3 == ~(abc | qq) % join
		, joi4 == (abc >> *qq) % join
		, joi5 == (+abc >> ~(abc | qq)) % join
		;
}

inline void idempotent()
{
	assert
		, joi1 == join(joi1)
		, joi2 == join(joi2)
		, joi3 == join(joi3)
		, joi4 == join(joi4)
		, joi5 == join(joi5)
		, joi1 == joi1 % join
		, joi2 == joi2 % join
		, joi3 == joi3 % join
		, joi4 == joi4 % join
		, joi5 == joi5 % join
		;
}



constexpr auto join_checker = []<Parser P>(P) -> bool
{
	if constexpr (not k3::tok3n::detail::is_joinable_v<typename P::result_type>)
	{
		TOK3N_ASSERT_P( not requires { join(P{}); },  "join prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % join; }, "join infix operator compiles, but it shouldn't" );
	}
	else if constexpr (std::same_as<typename P::result_type, std::string_view>)
	{
		TOK3N_ASSERT_P( requires { join(P{}); },  "join prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( join(P{}) == P{},         "join prefix operator of any parser with result_type of std::string_view should give itself" );
		TOK3N_ASSERT_P( requires { P{} % join; }, "join infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % join == P{},        "join infix operator of any parser with result_type of std::string_view should give itself" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { join(P{}); },  "join prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( join(P{}) == Join<P>{},   "join prefix operator of any other parser should give Join parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % join; }, "join infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % join == Join<P>{},  "join infix operator of any other parser should give Join parser of the argument" );
	}

	return true;
};

inline void join_anything()
{
	assert
		, check_all_samples(join_checker)
		;
}
