#include "pch.h"

FIXTURE("join modifier");

TEST("join modifier", "prefix")
{
	ASSERT_PARSER_VALUES_NE(joi1, join(abc));
	ASSERT_PARSER_VALUES_EQ(abc, join(abc));
	ASSERT_PARSER_VALUES_EQ(joi2, join(+abc));
	ASSERT_PARSER_VALUES_EQ(joi3, join(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(joi4, join(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(joi5, join(+abc >> ~(abc | qq)));
}

TEST("join modifier", "infix")
{
	ASSERT_PARSER_VALUES_NE(joi1, abc % join);
	ASSERT_PARSER_VALUES_EQ(abc, abc % join);
	ASSERT_PARSER_VALUES_EQ(joi2, +abc % join);
	ASSERT_PARSER_VALUES_EQ(joi3, ~(abc | qq) % join);
	ASSERT_PARSER_VALUES_EQ(joi4, (abc >> *qq) % join);
	ASSERT_PARSER_VALUES_EQ(joi5, (+abc >> ~(abc | qq)) % join);
}

TEST("join modifier", "idempotent")
{
	ASSERT_PARSER_VALUES_EQ(joi1, join(joi1));
	ASSERT_PARSER_VALUES_EQ(joi2, join(joi2));
	ASSERT_PARSER_VALUES_EQ(joi3, join(joi3));
	ASSERT_PARSER_VALUES_EQ(joi4, join(joi4));
	ASSERT_PARSER_VALUES_EQ(joi5, join(joi5));
	ASSERT_PARSER_VALUES_EQ(joi1, joi1 % join);
	ASSERT_PARSER_VALUES_EQ(joi2, joi2 % join);
	ASSERT_PARSER_VALUES_EQ(joi3, joi3 % join);
	ASSERT_PARSER_VALUES_EQ(joi4, joi4 % join);
	ASSERT_PARSER_VALUES_EQ(joi5, joi5 % join);
}



constexpr auto join_checker = []<Parser P>(P) -> bool
{
	if constexpr (not detail::is_joinable_v<typename P::result_type>)
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

TEST("join modifier", "modify anything")
{
	ASSERT(check_all_samples(join_checker), "check_all_samples(join_checker) failed");
}
