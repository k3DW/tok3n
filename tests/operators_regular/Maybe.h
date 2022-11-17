#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::Maybe)

using namespace samples::all;

void Maybe_Maybe()
{
	assert
		, ~may1 == may1
		, ~~may1 == may1
		, ~~~may1 == may1
		, ~may2 == may2
		, ~~may2 == may2
		, ~~~may2 == may2
		, ~may3 == may3
		, ~~may3 == may3
		, ~~~may3 == may3
		, ~may4 == may4
		, ~~may4 == may4
		, ~~~may4 == may4
		;
}

void Maybe_OneOrMore()
{
	assert
		, ~oom1 == zom1
		, ~~oom1 == zom1
		, ~~~oom1 == zom1
		, ~oom2 == zom2
		, ~~oom2 == zom2
		, ~~~oom2 == zom2
		, ~oom3 == zom3
		, ~~oom3 == zom3
		, ~~~oom3 == zom3
		, ~oom4 == zom4
		, ~~oom4 == zom4
		, ~~~oom4 == zom4
		;
}

void Maybe_ZeroOrMore()
{
	assert
		, ~zom1 == zom1
		, ~~zom1 == zom1
		, ~~~zom1 == zom1
		, ~zom2 == zom2
		, ~~zom2 == zom2
		, ~~~zom2 == zom2
		, ~zom3 == zom3
		, ~~zom3 == zom3
		, ~~~zom3 == zom3
		, ~zom4 == zom4
		, ~~zom4 == zom4
		, ~~~zom4 == zom4
		;
}



template <auto p>
constexpr bool valid_for_Maybe = requires { ~p; };

void Maybe_anything()
{
	assert
		, ~oc1 == Maybe<OC1>{}
		, ~oc2 == Maybe<OC2>{}
		, ~oc3 == Maybe<OC3>{}
		, ~nc1 == Maybe<NC1>{}
		, ~nc2 == Maybe<NC2>{}
		, ~nc3 == Maybe<NC3>{}
		, ~l1 == Maybe<L1>{}
		, ~l2 == Maybe<L2>{}
		, ~l3 == Maybe<L3>{}
		, ~oc4 == Maybe<OC4>{}
		, ~nc4 == Maybe<NC4>{}
		, ~nc5 == Maybe<NC5>{}
		, ~l4 == Maybe<L4>{}
		, ~qq == Maybe<QQ>{}
		, ~abc == Maybe<ABC>{}
		, ~comma == Maybe<Comma>{}
		, ~spacedot == Maybe<SpaceDot>{}
		, ~cho1 == Maybe<Cho1>{}
		, ~cho2 == Maybe<Cho2>{}
		, ~cho3 == Maybe<Cho3>{}
		, ~cho4 == Maybe<Cho4>{}
		, ~seq1 == Maybe<Seq1>{}
		, ~seq2 == Maybe<Seq2>{}
		, ~seq3 == Maybe<Seq3>{}
		, ~seq4 == Maybe<Seq4>{}
		, ~may1 == May1{}
		, ~may2 == May2{}
		, ~may3 == May3{}
		, ~may4 == May4{}
		, ~exa1 == Maybe<Exa1>{}
		, ~exa2 == Maybe<Exa2>{}
		, ~exa3 == Maybe<Exa3>{}
		, ~exa4 == Maybe<Exa4>{}
		, ~oom1 == Zom1{}
		, ~oom2 == Zom2{}
		, ~oom3 == Zom3{}
		, ~oom4 == Zom4{}
		, ~zom1 == Zom1{}
		, ~zom2 == Zom2{}
		, ~zom3 == Zom3{}
		, ~zom4 == Zom4{}
		, not valid_for_Maybe<ign1>
		, not valid_for_Maybe<ign2>
		, not valid_for_Maybe<ign3>
		, not valid_for_Maybe<ign4>
		, not valid_for_Maybe<ign5>
		, ~del1 == Maybe<Del1>{}
		, ~del2 == Maybe<Del2>{}
		, ~del3 == Maybe<Del3>{}
		, ~del4 == Maybe<Del4>{}
		, ~del5 == Maybe<Del5>{}
		, ~del6 == Maybe<Del6>{}
		, ~del7 == Maybe<Del7>{}
		, ~del8 == Maybe<Del8>{}
		, ~com1 == Maybe<Com1>{}
		, ~com2 == Maybe<Com2>{}
		, ~com3 == Maybe<Com3>{}
		, ~com4 == Maybe<Com4>{}
		, ~com5 == Maybe<Com5>{}
		, ~com6 == Maybe<Com6>{}
		, ~com7 == Maybe<Com7>{}
		, ~tra1 == Maybe<Tra1>{}
		, ~tra2 == Maybe<Tra2>{}
		, ~tra3 == Maybe<Tra3>{}
		, ~tra4 == Maybe<Tra4>{}
		, ~int1 == Maybe<Int1>{}
		, ~int2 == Maybe<Int2>{}
		, ~con1 == Maybe<Con1>{}
		, ~con2 == Maybe<Con2>{}
		, ~con3 == Maybe<Con3>{}
		, ~con4 == Maybe<Con4>{}
		, ~def1 == Maybe<Def1>{}
		, ~def2 == Maybe<Def2>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(regular::Maybe)
