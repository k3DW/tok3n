#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Exactly)

using namespace samples::all;

void prefix()
{
	assert
		, exa1 == exactly<3>(l1)
		, exa2 == exactly<5>(oc1)
		, exa3 == exactly<4>(l1 | oc1)
		, exa4 == exactly<2>(l1 >> oc1)
		;
}

void infix()
{
	assert
		, exa1 == l1 % exactly<3>
		, exa2 == oc1 % exactly<5>
		, exa3 == (l1 | oc1) % exactly<4>
		, exa4 == (l1 >> oc1) % exactly<2>
		;
}



template <Parser auto p>
concept valid_for_exactly = traits::operators::valid_modulo<p, exactly<2>>;

void exactly_anything()
{
	assert
		, oc1 % exactly<2> == Exactly<OC1, 2>{}
		, oc2 % exactly<2> == Exactly<OC2, 2>{}
		, oc3 % exactly<2> == Exactly<OC3, 2>{}
		, nc1 % exactly<2> == Exactly<NC1, 2>{}
		, nc2 % exactly<2> == Exactly<NC2, 2>{}
		, nc3 % exactly<2> == Exactly<NC3, 2>{}
		, l1 % exactly<2> == Exactly<L1, 2>{}
		, l2 % exactly<2> == Exactly<L2, 2>{}
		, l3 % exactly<2> == Exactly<L3, 2>{}
		, oc4 % exactly<2> == Exactly<OC4, 2>{}
		, nc4 % exactly<2> == Exactly<NC4, 2>{}
		, nc5 % exactly<2> == Exactly<NC5, 2>{}
		, l4 % exactly<2> == Exactly<L4, 2>{}
		, qq % exactly<2> == Exactly<QQ, 2>{}
		, abc % exactly<2> == Exactly<ABC, 2>{}
		, comma % exactly<2> == Exactly<Comma, 2>{}
		, spacedot % exactly<2> == Exactly<SpaceDot, 2>{}
		, cho1 % exactly<2> == Exactly<Cho1, 2>{}
		, cho2 % exactly<2> == Exactly<Cho2, 2>{}
		, cho3 % exactly<2> == Exactly<Cho3, 2>{}
		, cho4 % exactly<2> == Exactly<Cho4, 2>{}
		, seq1 % exactly<2> == Exactly<Seq1, 2>{}
		, seq2 % exactly<2> == Exactly<Seq2, 2>{}
		, seq3 % exactly<2> == Exactly<Seq3, 2>{}
		, seq4 % exactly<2> == Exactly<Seq4, 2>{}
		, may1 % exactly<2> == Exactly<May1, 2>{}
		, may2 % exactly<2> == Exactly<May2, 2>{}
		, may3 % exactly<2> == Exactly<May3, 2>{}
		, may4 % exactly<2> == Exactly<May4, 2>{}
		, exa1 % exactly<2> == Exactly<Exa1, 2>{}
		, exa2 % exactly<2> == Exactly<Exa2, 2>{}
		, exa3 % exactly<2> == Exactly<Exa3, 2>{}
		, exa4 % exactly<2> == Exactly<Exa4, 2>{}
		, oom1 % exactly<2> == Exactly<Oom1, 2>{}
		, oom2 % exactly<2> == Exactly<Oom2, 2>{}
		, oom3 % exactly<2> == Exactly<Oom3, 2>{}
		, oom4 % exactly<2> == Exactly<Oom4, 2>{}
		, zom1 % exactly<2> == Exactly<Zom1, 2>{}
		, zom2 % exactly<2> == Exactly<Zom2, 2>{}
		, zom3 % exactly<2> == Exactly<Zom3, 2>{}
		, zom4 % exactly<2> == Exactly<Zom4, 2>{}
		, not valid_for_exactly<ign1>
		, not valid_for_exactly<ign2>
		, not valid_for_exactly<ign3>
		, not valid_for_exactly<ign4>
		, not valid_for_exactly<ign5>
		, del1 % exactly<2> == Exactly<Del1, 2>{}
		, del2 % exactly<2> == Exactly<Del2, 2>{}
		, del3 % exactly<2> == Exactly<Del3, 2>{}
		, del4 % exactly<2> == Exactly<Del4, 2>{}
		, del5 % exactly<2> == Exactly<Del5, 2>{}
		, del6 % exactly<2> == Exactly<Del6, 2>{}
		, del7 % exactly<2> == Exactly<Del7, 2>{}
		, del8 % exactly<2> == Exactly<Del8, 2>{}
		, com1 % exactly<2> == Exactly<Com1, 2>{}
		, com2 % exactly<2> == Exactly<Com2, 2>{}
		, com3 % exactly<2> == Exactly<Com3, 2>{}
		, com4 % exactly<2> == Exactly<Com4, 2>{}
		, com5 % exactly<2> == Exactly<Com5, 2>{}
		, com6 % exactly<2> == Exactly<Com6, 2>{}
		, com7 % exactly<2> == Exactly<Com7, 2>{}
		, tra1 % exactly<2> == Exactly<Tra1, 2>{}
		, tra2 % exactly<2> == Exactly<Tra2, 2>{}
		, tra3 % exactly<2> == Exactly<Tra3, 2>{}
		, tra4 % exactly<2> == Exactly<Tra4, 2>{}
		, int1 % exactly<2> == Exactly<Int1, 2>{}
		, int2 % exactly<2> == Exactly<Int2, 2>{}
		, int3 % exactly<2> == Exactly<Int3, 2>{}
		, api1 % exactly<2> == Exactly<Api1, 2>{}
		, api2 % exactly<2> == Exactly<Api2, 2>{}
		, con1 % exactly<2> == Exactly<Con1, 2>{}
		, con2 % exactly<2> == Exactly<Con2, 2>{}
		, con3 % exactly<2> == Exactly<Con3, 2>{}
		, con4 % exactly<2> == Exactly<Con4, 2>{}
		, def1 % exactly<2> == Exactly<Def1, 2>{}
		, def2 % exactly<2> == Exactly<Def2, 2>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Exactly)
#endif
