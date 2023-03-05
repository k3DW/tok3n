#ifdef TOK3N_TESTING
#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::OneOrMore)

using namespace samples::all;

void OneOrMore_Maybe()
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

void OneOrMore_OneOrMore()
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

void OneOrMore_ZeroOrMore()
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



template <auto p>
constexpr bool valid_for_OneOrMore = requires { +p; };

void OneOrMore_anything()
{
	assert
		, +oc1 == OneOrMore<OC1>{}
		, +oc2 == OneOrMore<OC2>{}
		, +oc3 == OneOrMore<OC3>{}
		, +nc1 == OneOrMore<NC1>{}
		, +nc2 == OneOrMore<NC2>{}
		, +nc3 == OneOrMore<NC3>{}
		, +l1 == OneOrMore<L1>{}
		, +l2 == OneOrMore<L2>{}
		, +l3 == OneOrMore<L3>{}
		, +oc4 == OneOrMore<OC4>{}
		, +nc4 == OneOrMore<NC4>{}
		, +nc5 == OneOrMore<NC5>{}
		, +l4 == OneOrMore<L4>{}
		, +qq == OneOrMore<QQ>{}
		, +abc == OneOrMore<ABC>{}
		, +comma == OneOrMore<Comma>{}
		, +spacedot == OneOrMore<SpaceDot>{}
		, +cho1 == OneOrMore<Cho1>{}
		, +cho2 == OneOrMore<Cho2>{}
		, +cho3 == OneOrMore<Cho3>{}
		, +cho4 == OneOrMore<Cho4>{}
		, +seq1 == OneOrMore<Seq1>{}
		, +seq2 == OneOrMore<Seq2>{}
		, +seq3 == OneOrMore<Seq3>{}
		, +seq4 == OneOrMore<Seq4>{}
		, +may1 == Zom1{}
		, +may2 == Zom2{}
		, +may3 == Zom3{}
		, +may4 == Zom4{}
		, +exa1 == OneOrMore<Exa1>{}
		, +exa2 == OneOrMore<Exa2>{}
		, +exa3 == OneOrMore<Exa3>{}
		, +exa4 == OneOrMore<Exa4>{}
		, +oom1 == Oom1{}
		, +oom2 == Oom2{}
		, +oom3 == Oom3{}
		, +oom4 == Oom4{}
		, +zom1 == Zom1{}
		, +zom2 == Zom2{}
		, +zom3 == Zom3{}
		, +zom4 == Zom4{}
		, not valid_for_OneOrMore<ign1>
		, not valid_for_OneOrMore<ign2>
		, not valid_for_OneOrMore<ign3>
		, not valid_for_OneOrMore<ign4>
		, not valid_for_OneOrMore<ign5>
		, +del1 == OneOrMore<Del1>{}
		, +del2 == OneOrMore<Del2>{}
		, +del3 == OneOrMore<Del3>{}
		, +del4 == OneOrMore<Del4>{}
		, +del5 == OneOrMore<Del5>{}
		, +del6 == OneOrMore<Del6>{}
		, +del7 == OneOrMore<Del7>{}
		, +del8 == OneOrMore<Del8>{}
		, +com1 == OneOrMore<Com1>{}
		, +com2 == OneOrMore<Com2>{}
		, +com3 == OneOrMore<Com3>{}
		, +com4 == OneOrMore<Com4>{}
		, +com5 == OneOrMore<Com5>{}
		, +com6 == OneOrMore<Com6>{}
		, +com7 == OneOrMore<Com7>{}
		, +tra1 == OneOrMore<Tra1>{}
		, +tra2 == OneOrMore<Tra2>{}
		, +tra3 == OneOrMore<Tra3>{}
		, +tra4 == OneOrMore<Tra4>{}
		, +int1 == OneOrMore<Int1>{}
		, +int2 == OneOrMore<Int2>{}
		, +int3 == OneOrMore<Int3>{}
		, +api1 == OneOrMore<Api1>{}
		, +api2 == OneOrMore<Api2>{}
		, +con1 == OneOrMore<Con1>{}
		, +con2 == OneOrMore<Con2>{}
		, +con3 == OneOrMore<Con3>{}
		, +con4 == OneOrMore<Con4>{}
		, +def1 == OneOrMore<Def1>{}
		, +def2 == OneOrMore<Def2>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(regular::OneOrMore)

#endif
