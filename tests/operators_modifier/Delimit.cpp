#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Delimit)

using namespace samples::all;

void prefix()
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

void infix()
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



template <Parser auto p>
concept valid_for_delimit = traits::operators::valid_modulo<p, delimit(comma)>;

void delimit_anything()
{
	assert
		, oc1 % delimit(comma) == Delimit<OC1, Comma>{}
		, oc2 % delimit(comma) == Delimit<OC2, Comma>{}
		, oc3 % delimit(comma) == Delimit<OC3, Comma>{}
		, nc1 % delimit(comma) == Delimit<NC1, Comma>{}
		, nc2 % delimit(comma) == Delimit<NC2, Comma>{}
		, nc3 % delimit(comma) == Delimit<NC3, Comma>{}
		, l1 % delimit(comma) == Delimit<L1, Comma>{}
		, l2 % delimit(comma) == Delimit<L2, Comma>{}
		, l3 % delimit(comma) == Delimit<L3, Comma>{}
		, oc4 % delimit(comma) == Delimit<OC4, Comma>{}
		, nc4 % delimit(comma) == Delimit<NC4, Comma>{}
		, nc5 % delimit(comma) == Delimit<NC5, Comma>{}
		, l4 % delimit(comma) == Delimit<L4, Comma>{}
		, qq % delimit(comma) == Delimit<QQ, Comma>{}
		, abc % delimit(comma) == Delimit<ABC, Comma>{}
		, comma % delimit(comma) == Delimit<Comma, Comma>{}
		, spacedot % delimit(comma) == Delimit<SpaceDot, Comma>{}
		, cho1 % delimit(comma) == Delimit<Cho1, Comma>{}
		, cho2 % delimit(comma) == Delimit<Cho2, Comma>{}
		, cho3 % delimit(comma) == Delimit<Cho3, Comma>{}
		, cho4 % delimit(comma) == Delimit<Cho4, Comma>{}
		, seq1 % delimit(comma) == Delimit<Seq1, Comma>{}
		, seq2 % delimit(comma) == Delimit<Seq2, Comma>{}
		, seq3 % delimit(comma) == Delimit<Seq3, Comma>{}
		, seq4 % delimit(comma) == Delimit<Seq4, Comma>{}
		, may1 % delimit(comma) == Delimit<May1, Comma>{}
		, may2 % delimit(comma) == Delimit<May2, Comma>{}
		, may3 % delimit(comma) == Delimit<May3, Comma>{}
		, may4 % delimit(comma) == Delimit<May4, Comma>{}
		, exa1 % delimit(comma) == Delimit<Exa1, Comma>{}
		, exa2 % delimit(comma) == Delimit<Exa2, Comma>{}
		, exa3 % delimit(comma) == Delimit<Exa3, Comma>{}
		, exa4 % delimit(comma) == Delimit<Exa4, Comma>{}
		, oom1 % delimit(comma) == Delimit<Oom1, Comma>{}
		, oom2 % delimit(comma) == Delimit<Oom2, Comma>{}
		, oom3 % delimit(comma) == Delimit<Oom3, Comma>{}
		, oom4 % delimit(comma) == Delimit<Oom4, Comma>{}
		, zom1 % delimit(comma) == Delimit<Zom1, Comma>{}
		, zom2 % delimit(comma) == Delimit<Zom2, Comma>{}
		, zom3 % delimit(comma) == Delimit<Zom3, Comma>{}
		, zom4 % delimit(comma) == Delimit<Zom4, Comma>{}
		, not valid_for_delimit<ign1>
		, not valid_for_delimit<ign2>
		, not valid_for_delimit<ign3>
		, not valid_for_delimit<ign4>
		, not valid_for_delimit<ign5>
		, del1 % delimit(comma) == Delimit<Del1, Comma>{}
		, del2 % delimit(comma) == Delimit<Del2, Comma>{}
		, del3 % delimit(comma) == Delimit<Del3, Comma>{}
		, del4 % delimit(comma) == Delimit<Del4, Comma>{}
		, del5 % delimit(comma) == Delimit<Del5, Comma>{}
		, del6 % delimit(comma) == Delimit<Del6, Comma>{}
		, del7 % delimit(comma) == Delimit<Del7, Comma>{}
		, del8 % delimit(comma) == Delimit<Del8, Comma>{}
		, com1 % delimit(comma) == Delimit<Com1, Comma>{}
		, com2 % delimit(comma) == Delimit<Com2, Comma>{}
		, com3 % delimit(comma) == Delimit<Com3, Comma>{}
		, com4 % delimit(comma) == Delimit<Com4, Comma>{}
		, com5 % delimit(comma) == Delimit<Com5, Comma>{}
		, com6 % delimit(comma) == Delimit<Com6, Comma>{}
		, com7 % delimit(comma) == Delimit<Com7, Comma>{}
		, tra1 % delimit(comma) == Delimit<Tra1, Comma>{}
		, tra2 % delimit(comma) == Delimit<Tra2, Comma>{}
		, tra3 % delimit(comma) == Delimit<Tra3, Comma>{}
		, tra4 % delimit(comma) == Delimit<Tra4, Comma>{}
		, apt1 % delimit(comma) == Delimit<Apt1, Comma>{}
		, apt2 % delimit(comma) == Delimit<Apt2, Comma>{}
		, int1 % delimit(comma) == Delimit<Int1, Comma>{}
		, int2 % delimit(comma) == Delimit<Int2, Comma>{}
		, int3 % delimit(comma) == Delimit<Int3, Comma>{}
		, api1 % delimit(comma) == Delimit<Api1, Comma>{}
		, api2 % delimit(comma) == Delimit<Api2, Comma>{}
		, con1 % delimit(comma) == Delimit<Con1, Comma>{}
		, con2 % delimit(comma) == Delimit<Con2, Comma>{}
		, con3 % delimit(comma) == Delimit<Con3, Comma>{}
		, con4 % delimit(comma) == Delimit<Con4, Comma>{}
		, def1 % delimit(comma) == Delimit<Def1, Comma>{}
		, def2 % delimit(comma) == Delimit<Def2, Comma>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Delimit)
