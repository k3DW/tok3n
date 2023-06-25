#include "pch.h"

inline void prefix()
{
	assert
		, del1 == delimit(abc, comma)
		, del2 == delimit(abc, spacedot)
		, del3 == delimit(qq, comma)
		, del4 == delimit(qq, spacedot)
		, del5 == delimit(comma, abc)
		, del6 == delimit(spacedot, abc)
		, del7 == delimit(comma, qq)
		, del8 == delimit(spacedot, qq)
		;
}

inline void infix()
{
	assert
		, del1 == abc % delimit(comma)
		, del2 == abc % delimit(spacedot)
		, del3 == qq % delimit(comma)
		, del4 == qq % delimit(spacedot)
		, del5 == comma % delimit(abc)
		, del6 == spacedot % delimit(abc)
		, del7 == comma % delimit(qq)
		, del8 == spacedot % delimit(qq)
		;
}



constexpr auto delimit_checker = []<Parser P>(P) -> bool
{
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { delimit(P{}, comma); },  "delimit prefix operator compiles, but it shouldn't" );
		TOK3N_ASSERT_P( not requires { P{} % delimit(comma); }, "delimit infix operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { delimit(P{}, comma); },                              "delimit prefix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( delimit(P{}, comma) == (Delimit<P, Comma, std::false_type>{}),  "delimit prefix operator of any other parser should give Delimit parser of the argument" );
		TOK3N_ASSERT_P( requires { P{} % delimit(comma); },                             "delimit infix operator doesn't compile, but it should" );
		TOK3N_ASSERT_P( P{} % delimit(comma) == (Delimit<P, Comma, std::false_type>{}), "delimit infix operator of any other parser should give Delimit parser of the argument" );
	}

	return true;
};

inline void delimit_anything()
{
	assert
		, check_all_samples(delimit_checker)
		;
}
