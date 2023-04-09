#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::Basic)

using namespace samples::basic;

inline void one_literal()
{
	assert
		, "abc"_one == oc1
		, "bcd"_one == oc2
		, "xyz"_one == oc3
		, "cd"_one == oc4
		, ","_one == comma
		, " ."_one == spacedot
		;
}

inline void one_operator()
{
	assert
		, one<"abc"> == oc1
		, one<"bcd"> == oc2
		, one<"xyz"> == oc3
		, one<"cd"> == oc4
		, one<","> == comma
		, one<" ."> == spacedot
		;
}

inline void not_literal()
{
	assert
		, "abc"_not == nc1
		, "bcd"_not == nc2
		, "xyz"_not == nc3
		, "cd"_not == nc4
		, "z"_not == nc5
		;
}

inline void not_operator()
{
	assert
		, not_<"abc"> == nc1
		, not_<"bcd"> == nc2
		, not_<"xyz"> == nc3
		, not_<"cd"> == nc4
		, not_<"z"> == nc5
		;
}

inline void lit_literal()
{
	assert
		, "literal"_lit == l1
		, "ly"_lit == l2
		, "test"_lit == l3
		, "ab"_lit == l4
		, "??"_lit == qq
		, "abc"_lit == abc
		;
}

inline void lit_operator()
{
	assert
		, lit<"literal"> == l1
		, lit<"ly"> == l2
		, lit<"test"> == l3
		, lit<"ab"> == l4
		, lit<"??"> == qq
		, lit<"abc"> == abc
		;
}

inline void ign_literal()
{
	assert
		, "literal"_ign == Ignore<L1>{}
		, "ly"_ign == Ignore<L2>{}
		, "test"_ign == Ignore<L3>{}
		, "ab"_ign == Ignore<L4>{}
		, "??"_ign == Ignore<QQ>{}
		, "abc"_ign == Ignore<ABC>{}
		;
}

inline void ign_operator()
{
	assert
		, ign<"literal"> == Ignore<L1>{}
		, ign<"ly"> == Ignore<L2>{}
		, ign<"test"> == Ignore<L3>{}
		, ign<"ab"> == Ignore<L4>{}
		, ign<"??"> == Ignore<QQ>{}
		, ign<"abc"> == Ignore<ABC>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(regular::Basic)
