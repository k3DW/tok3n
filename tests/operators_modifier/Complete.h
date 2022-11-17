#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Complete)

using namespace samples::all;

void prefix()
{
	assert
		, com1 == complete(l1)
		, com2 == complete(oc1)
		, com3 == complete(l1 | oc1)
		, com4 == complete(l1 >> oc1)
		, com5 == complete(~(l1 >> oc1))
		, com6 == complete(+(l1 >> oc1))
		, com7 == complete(*(l1 >> oc1))
		;
}

void infix()
{
	assert
		, com1 == l1 % complete
		, com2 == oc1 % complete
		, com3 == (l1 | oc1) % complete
		, com4 == (l1 >> oc1) % complete
		, com5 == ~(l1 >> oc1) % complete
		, com6 == +(l1 >> oc1) % complete
		, com7 == *(l1 >> oc1) % complete
		;
}

void idempotent()
{
	assert
		, com1 == complete(com1)
		, com2 == complete(com2)
		, com3 == complete(com3)
		, com4 == complete(com4)
		, com5 == complete(com5)
		, com6 == complete(com6)
		, com7 == complete(com7)
		, com1 == com1 % complete
		, com2 == com2 % complete
		, com3 == com3 % complete
		, com4 == com4 % complete
		, com5 == com5 % complete
		, com6 == com6 % complete
		, com7 == com7 % complete
		;
}



void complete_anything()
{
	assert
		, oc1 % complete == Complete<OC1>{}
		, oc2 % complete == Complete<OC2>{}
		, oc3 % complete == Complete<OC3>{}
		, nc1 % complete == Complete<NC1>{}
		, nc2 % complete == Complete<NC2>{}
		, nc3 % complete == Complete<NC3>{}
		, l1 % complete == Complete<L1>{}
		, l2 % complete == Complete<L2>{}
		, l3 % complete == Complete<L3>{}
		, oc4 % complete == Complete<OC4>{}
		, nc4 % complete == Complete<NC4>{}
		, nc5 % complete == Complete<NC5>{}
		, l4 % complete == Complete<L4>{}
		, qq % complete == Complete<QQ>{}
		, abc % complete == Complete<ABC>{}
		, comma % complete == Complete<Comma>{}
		, spacedot % complete == Complete<SpaceDot>{}
		, cho1 % complete == Complete<Cho1>{}
		, cho2 % complete == Complete<Cho2>{}
		, cho3 % complete == Complete<Cho3>{}
		, cho4 % complete == Complete<Cho4>{}
		, seq1 % complete == Complete<Seq1>{}
		, seq2 % complete == Complete<Seq2>{}
		, seq3 % complete == Complete<Seq3>{}
		, seq4 % complete == Complete<Seq4>{}
		, may1 % complete == Complete<May1>{}
		, may2 % complete == Complete<May2>{}
		, may3 % complete == Complete<May3>{}
		, may4 % complete == Complete<May4>{}
		, exa1 % complete == Complete<Exa1>{}
		, exa2 % complete == Complete<Exa2>{}
		, exa3 % complete == Complete<Exa3>{}
		, exa4 % complete == Complete<Exa4>{}
		, oom1 % complete == Complete<Oom1>{}
		, oom2 % complete == Complete<Oom2>{}
		, oom3 % complete == Complete<Oom3>{}
		, oom4 % complete == Complete<Oom4>{}
		, zom1 % complete == Complete<Zom1>{}
		, zom2 % complete == Complete<Zom2>{}
		, zom3 % complete == Complete<Zom3>{}
		, zom4 % complete == Complete<Zom4>{}
		, ign1 % complete == Complete<Ign1>{}
		, ign2 % complete == Complete<Ign2>{}
		, ign3 % complete == Complete<Ign3>{}
		, ign4 % complete == Complete<Ign4>{}
		, ign5 % complete == Complete<Ign5>{}
		, del1 % complete == Complete<Del1>{}
		, del2 % complete == Complete<Del2>{}
		, del3 % complete == Complete<Del3>{}
		, del4 % complete == Complete<Del4>{}
		, del5 % complete == Complete<Del5>{}
		, del6 % complete == Complete<Del6>{}
		, del7 % complete == Complete<Del7>{}
		, del8 % complete == Complete<Del8>{}
		, com1 % complete == Com1{}
		, com2 % complete == Com2{}
		, com3 % complete == Com3{}
		, com4 % complete == Com4{}
		, com5 % complete == Com5{}
		, com6 % complete == Com6{}
		, com7 % complete == Com7{}
		, tra1 % complete == Complete<Tra1>{}
		, tra2 % complete == Complete<Tra2>{}
		, tra3 % complete == Complete<Tra3>{}
		, tra4 % complete == Complete<Tra4>{}
		, int1 % complete == Complete<Int1>{}
		, int2 % complete == Complete<Int2>{}
		, con1 % complete == Complete<Con1>{}
		, con2 % complete == Complete<Con2>{}
		, con3 % complete == Complete<Con3>{}
		, con4 % complete == Complete<Con4>{}
		, def1 % complete == Complete<Def1>{}
		, def2 % complete == Complete<Def2>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Complete)
