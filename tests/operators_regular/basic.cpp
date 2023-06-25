#include "pch.h"

namespace k3::tok3n::tests {

inline void one_literal()
{
	assert
		, "abc"_one == oc1
		, "bcd"_one == oc2
		, "xyz"_one == oc3
		, "cd"_one == oc4
		, ","_one == comma
		, " ."_one == spacedot
		, ""_one == OneChar<"">{}
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
		, one<""> == OneChar<"">{}
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
		, ""_not == NotChar<"">{}
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
		, not_<""> == NotChar<"">{}
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
		, ""_lit == Literal<"">{}
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
		, lit<""> == Literal<"">{}
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
		, ""_ign == Ignore<Literal<"">>{}
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
		, ign<""> == Ignore<Literal<"">>{}
		;
}

inline void non_sorted_and_uniqued()
{
	assert
		, "212312323321212311"_one == OneChar<"123">{}
		, "212312323321212311"_not == NotChar<"123">{}
		, "123abc"_one == OneChar<"123abc">{}
		, "123abc"_not == NotChar<"123abc">{}
		, "abc123"_one == OneChar<"123abc">{}
		, "abc123"_not == NotChar<"123abc">{}
		, "a1b2c3"_one == OneChar<"123abc">{}
		, "a1b2c3"_not == NotChar<"123abc">{}
		, "Aa"_one == OneChar<"Aa">{}
		, "Aa"_not == NotChar<"Aa">{}
		, "aA"_one == OneChar<"Aa">{}
		, "aA"_not == NotChar<"Aa">{}
		, "A"_one == OneChar<"A">{}
		, "A"_not == NotChar<"A">{}
		, ""_one == OneChar<"">{}
		, ""_not == NotChar<"">{}
		;
}

} // namespace k3::tok3n::tests