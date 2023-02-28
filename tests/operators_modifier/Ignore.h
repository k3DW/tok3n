#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Ignore)

using namespace samples::all;

void prefix()
{
	assert
		, ign1 == ignore(abc)
		, ign2 == ignore(+abc)
		, ign3 == ignore(~(abc | qq))
		, ign4 == ignore(abc >> *qq)
		, ign5 == ignore(+abc >> ~(abc | qq))
		;
}

void infix()
{
	assert
		, ign1 == abc % ignore
		, ign2 == +abc % ignore
		, ign3 == ~(abc | qq) % ignore
		, ign4 == (abc >> *qq) % ignore
		, ign5 == (+abc >> ~(abc | qq)) % ignore
		;
}

void idempotent()
{
	assert
		, ign1 == ignore(ign1)
		, ign2 == ignore(ign2)
		, ign3 == ignore(ign3)
		, ign4 == ignore(ign4)
		, ign5 == ignore(ign5)
		, ign1 == ign1 % ignore
		, ign2 == ign2 % ignore
		, ign3 == ign3 % ignore
		, ign4 == ign4 % ignore
		, ign5 == ign5 % ignore
		;
}



void ignore_anything()
{
	assert
		, oc1 % ignore == Ignore<OC1>{}
		, oc2 % ignore == Ignore<OC2>{}
		, oc3 % ignore == Ignore<OC3>{}
		, nc1 % ignore == Ignore<NC1>{}
		, nc2 % ignore == Ignore<NC2>{}
		, nc3 % ignore == Ignore<NC3>{}
		, l1 % ignore == Ignore<L1>{}
		, l2 % ignore == Ignore<L2>{}
		, l3 % ignore == Ignore<L3>{}
		, oc4 % ignore == Ignore<OC4>{}
		, nc4 % ignore == Ignore<NC4>{}
		, nc5 % ignore == Ignore<NC5>{}
		, l4 % ignore == Ignore<L4>{}
		, qq % ignore == Ignore<QQ>{}
		, abc % ignore == Ignore<ABC>{}
		, comma % ignore == Ignore<Comma>{}
		, spacedot % ignore == Ignore<SpaceDot>{}
		, cho1 % ignore == Ignore<Cho1>{}
		, cho2 % ignore == Ignore<Cho2>{}
		, cho3 % ignore == Ignore<Cho3>{}
		, cho4 % ignore == Ignore<Cho4>{}
		, seq1 % ignore == Ignore<Seq1>{}
		, seq2 % ignore == Ignore<Seq2>{}
		, seq3 % ignore == Ignore<Seq3>{}
		, seq4 % ignore == Ignore<Seq4>{}
		, may1 % ignore == Ignore<May1>{}
		, may2 % ignore == Ignore<May2>{}
		, may3 % ignore == Ignore<May3>{}
		, may4 % ignore == Ignore<May4>{}
		, exa1 % ignore == Ignore<Exa1>{}
		, exa2 % ignore == Ignore<Exa2>{}
		, exa3 % ignore == Ignore<Exa3>{}
		, exa4 % ignore == Ignore<Exa4>{}
		, oom1 % ignore == Ignore<Oom1>{}
		, oom2 % ignore == Ignore<Oom2>{}
		, oom3 % ignore == Ignore<Oom3>{}
		, oom4 % ignore == Ignore<Oom4>{}
		, zom1 % ignore == Ignore<Zom1>{}
		, zom2 % ignore == Ignore<Zom2>{}
		, zom3 % ignore == Ignore<Zom3>{}
		, zom4 % ignore == Ignore<Zom4>{}
		, ign1 % ignore == Ign1{}
		, ign2 % ignore == Ign2{}
		, ign3 % ignore == Ign3{}
		, ign4 % ignore == Ign4{}
		, ign5 % ignore == Ign5{}
		, del1 % ignore == Ignore<Del1>{}
		, del2 % ignore == Ignore<Del2>{}
		, del3 % ignore == Ignore<Del3>{}
		, del4 % ignore == Ignore<Del4>{}
		, del5 % ignore == Ignore<Del5>{}
		, del6 % ignore == Ignore<Del6>{}
		, del7 % ignore == Ignore<Del7>{}
		, del8 % ignore == Ignore<Del8>{}
		, com1 % ignore == Ignore<Com1>{}
		, com2 % ignore == Ignore<Com2>{}
		, com3 % ignore == Ignore<Com3>{}
		, com4 % ignore == Ignore<Com4>{}
		, com5 % ignore == Ignore<Com5>{}
		, com6 % ignore == Ignore<Com6>{}
		, com7 % ignore == Ignore<Com7>{}
		, tra1 % ignore == Ignore<Tra1>{}
		, tra2 % ignore == Ignore<Tra2>{}
		, tra3 % ignore == Ignore<Tra3>{}
		, tra4 % ignore == Ignore<Tra4>{}
		, int1 % ignore == Ignore<Int1>{}
		, int2 % ignore == Ignore<Int2>{}
		, int3 % ignore == Ignore<Int3>{}
		, api1 % ignore == Ignore<Api1>{}
		, api2 % ignore == Ignore<Api2>{}
		, con1 % ignore == Ignore<Con1>{}
		, con2 % ignore == Ignore<Con2>{}
		, con3 % ignore == Ignore<Con3>{}
		, con4 % ignore == Ignore<Con4>{}
		, def1 % ignore == Ignore<Def1>{}
		, def2 % ignore == Ignore<Def2>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Ignore)
