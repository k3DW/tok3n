#ifdef TOK3N_TESTING
#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(regular::ZeroOrMore)

using namespace samples::all;

void ZeroOrMore_Maybe()
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

void ZeroOrMore_OneOrMore()
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

void ZeroOrMore_ZeroOrMore()
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



template <auto p>
constexpr bool valid_for_ZeroOrMore = requires { *p; };

void ZeroOrMore_anything()
{
	assert
		, *oc1 == ZeroOrMore<OC1>{}
		, *oc2 == ZeroOrMore<OC2>{}
		, *oc3 == ZeroOrMore<OC3>{}
		, *nc1 == ZeroOrMore<NC1>{}
		, *nc2 == ZeroOrMore<NC2>{}
		, *nc3 == ZeroOrMore<NC3>{}
		, *l1 == ZeroOrMore<L1>{}
		, *l2 == ZeroOrMore<L2>{}
		, *l3 == ZeroOrMore<L3>{}
		, *oc4 == ZeroOrMore<OC4>{}
		, *nc4 == ZeroOrMore<NC4>{}
		, *nc5 == ZeroOrMore<NC5>{}
		, *l4 == ZeroOrMore<L4>{}
		, *qq == ZeroOrMore<QQ>{}
		, *abc == ZeroOrMore<ABC>{}
		, *comma == ZeroOrMore<Comma>{}
		, *spacedot == ZeroOrMore<SpaceDot>{}
		, *cho1 == ZeroOrMore<Cho1>{}
		, *cho2 == ZeroOrMore<Cho2>{}
		, *cho3 == ZeroOrMore<Cho3>{}
		, *cho4 == ZeroOrMore<Cho4>{}
		, *seq1 == ZeroOrMore<Seq1>{}
		, *seq2 == ZeroOrMore<Seq2>{}
		, *seq3 == ZeroOrMore<Seq3>{}
		, *seq4 == ZeroOrMore<Seq4>{}
		, *may1 == Zom1{}
		, *may2 == Zom2{}
		, *may3 == Zom3{}
		, *may4 == Zom4{}
		, *exa1 == ZeroOrMore<Exa1>{}
		, *exa2 == ZeroOrMore<Exa2>{}
		, *exa3 == ZeroOrMore<Exa3>{}
		, *exa4 == ZeroOrMore<Exa4>{}
		, *oom1 == Zom1{}
		, *oom2 == Zom2{}
		, *oom3 == Zom3{}
		, *oom4 == Zom4{}
		, *zom1 == Zom1{}
		, *zom2 == Zom2{}
		, *zom3 == Zom3{}
		, *zom4 == Zom4{}
		, not valid_for_ZeroOrMore<ign1>
		, not valid_for_ZeroOrMore<ign2>
		, not valid_for_ZeroOrMore<ign3>
		, not valid_for_ZeroOrMore<ign4>
		, not valid_for_ZeroOrMore<ign5>
		, *del1 == ZeroOrMore<Del1>{}
		, *del2 == ZeroOrMore<Del2>{}
		, *del3 == ZeroOrMore<Del3>{}
		, *del4 == ZeroOrMore<Del4>{}
		, *del5 == ZeroOrMore<Del5>{}
		, *del6 == ZeroOrMore<Del6>{}
		, *del7 == ZeroOrMore<Del7>{}
		, *del8 == ZeroOrMore<Del8>{}
		, *com1 == ZeroOrMore<Com1>{}
		, *com2 == ZeroOrMore<Com2>{}
		, *com3 == ZeroOrMore<Com3>{}
		, *com4 == ZeroOrMore<Com4>{}
		, *com5 == ZeroOrMore<Com5>{}
		, *com6 == ZeroOrMore<Com6>{}
		, *com7 == ZeroOrMore<Com7>{}
		, *tra1 == ZeroOrMore<Tra1>{}
		, *tra2 == ZeroOrMore<Tra2>{}
		, *tra3 == ZeroOrMore<Tra3>{}
		, *tra4 == ZeroOrMore<Tra4>{}
		, *int1 == ZeroOrMore<Int1>{}
		, *int2 == ZeroOrMore<Int2>{}
		, *int3 == ZeroOrMore<Int3>{}
		, *api1 == ZeroOrMore<Api1>{}
		, *api2 == ZeroOrMore<Api2>{}
		, *con1 == ZeroOrMore<Con1>{}
		, *con2 == ZeroOrMore<Con2>{}
		, *con3 == ZeroOrMore<Con3>{}
		, *con4 == ZeroOrMore<Con4>{}
		, *def1 == ZeroOrMore<Def1>{}
		, *def2 == ZeroOrMore<Def2>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(regular::ZeroOrMore)

#endif
