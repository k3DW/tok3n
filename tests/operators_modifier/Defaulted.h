#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Defaulted)

using namespace samples::all;

void prefix()
{
	assert
		, def1 == defaulted<int>(+abc)
		, def2 == defaulted<Class3>(~(abc | qq))
		;
}

void infix()
{
	assert
		, def1 == +abc % defaulted<int>
		, def2 == ~(abc | qq) % defaulted<Class3>
		;
}



void defaulted_anything()
{
	assert
		, oc1 % defaulted<bool> == Defaulted<OC1, bool>{}
		, oc2 % defaulted<bool> == Defaulted<OC2, bool>{}
		, oc3 % defaulted<bool> == Defaulted<OC3, bool>{}
		, nc1 % defaulted<bool> == Defaulted<NC1, bool>{}
		, nc2 % defaulted<bool> == Defaulted<NC2, bool>{}
		, nc3 % defaulted<bool> == Defaulted<NC3, bool>{}
		, l1 % defaulted<bool> == Defaulted<L1, bool>{}
		, l2 % defaulted<bool> == Defaulted<L2, bool>{}
		, l3 % defaulted<bool> == Defaulted<L3, bool>{}
		, oc4 % defaulted<bool> == Defaulted<OC4, bool>{}
		, nc4 % defaulted<bool> == Defaulted<NC4, bool>{}
		, nc5 % defaulted<bool> == Defaulted<NC5, bool>{}
		, l4 % defaulted<bool> == Defaulted<L4, bool>{}
		, qq % defaulted<bool> == Defaulted<QQ, bool>{}
		, abc % defaulted<bool> == Defaulted<ABC, bool>{}
		, comma % defaulted<bool> == Defaulted<Comma, bool>{}
		, spacedot % defaulted<bool> == Defaulted<SpaceDot, bool>{}
		, cho1 % defaulted<bool> == Defaulted<Cho1, bool>{}
		, cho2 % defaulted<bool> == Defaulted<Cho2, bool>{}
		, cho3 % defaulted<bool> == Defaulted<Cho3, bool>{}
		, cho4 % defaulted<bool> == Defaulted<Cho4, bool>{}
		, seq1 % defaulted<bool> == Defaulted<Seq1, bool>{}
		, seq2 % defaulted<bool> == Defaulted<Seq2, bool>{}
		, seq3 % defaulted<bool> == Defaulted<Seq3, bool>{}
		, seq4 % defaulted<bool> == Defaulted<Seq4, bool>{}
		, may1 % defaulted<bool> == Defaulted<May1, bool>{}
		, may2 % defaulted<bool> == Defaulted<May2, bool>{}
		, may3 % defaulted<bool> == Defaulted<May3, bool>{}
		, may4 % defaulted<bool> == Defaulted<May4, bool>{}
		, exa1 % defaulted<bool> == Defaulted<Exa1, bool>{}
		, exa2 % defaulted<bool> == Defaulted<Exa2, bool>{}
		, exa3 % defaulted<bool> == Defaulted<Exa3, bool>{}
		, exa4 % defaulted<bool> == Defaulted<Exa4, bool>{}
		, oom1 % defaulted<bool> == Defaulted<Oom1, bool>{}
		, oom2 % defaulted<bool> == Defaulted<Oom2, bool>{}
		, oom3 % defaulted<bool> == Defaulted<Oom3, bool>{}
		, oom4 % defaulted<bool> == Defaulted<Oom4, bool>{}
		, zom1 % defaulted<bool> == Defaulted<Zom1, bool>{}
		, zom2 % defaulted<bool> == Defaulted<Zom2, bool>{}
		, zom3 % defaulted<bool> == Defaulted<Zom3, bool>{}
		, zom4 % defaulted<bool> == Defaulted<Zom4, bool>{}
		, ign1 % defaulted<bool> == Defaulted<Ign1, bool>{}
		, ign2 % defaulted<bool> == Defaulted<Ign2, bool>{}
		, ign3 % defaulted<bool> == Defaulted<Ign3, bool>{}
		, ign4 % defaulted<bool> == Defaulted<Ign4, bool>{}
		, ign5 % defaulted<bool> == Defaulted<Ign5, bool>{}
		, del1 % defaulted<bool> == Defaulted<Del1, bool>{}
		, del2 % defaulted<bool> == Defaulted<Del2, bool>{}
		, del3 % defaulted<bool> == Defaulted<Del3, bool>{}
		, del4 % defaulted<bool> == Defaulted<Del4, bool>{}
		, del5 % defaulted<bool> == Defaulted<Del5, bool>{}
		, del6 % defaulted<bool> == Defaulted<Del6, bool>{}
		, del7 % defaulted<bool> == Defaulted<Del7, bool>{}
		, del8 % defaulted<bool> == Defaulted<Del8, bool>{}
		, com1 % defaulted<bool> == Defaulted<Com1, bool>{}
		, com2 % defaulted<bool> == Defaulted<Com2, bool>{}
		, com3 % defaulted<bool> == Defaulted<Com3, bool>{}
		, com4 % defaulted<bool> == Defaulted<Com4, bool>{}
		, com5 % defaulted<bool> == Defaulted<Com5, bool>{}
		, com6 % defaulted<bool> == Defaulted<Com6, bool>{}
		, com7 % defaulted<bool> == Defaulted<Com7, bool>{}
		, tra1 % defaulted<bool> == Defaulted<Tra1, bool>{}
		, tra2 % defaulted<bool> == Defaulted<Tra2, bool>{}
		, tra3 % defaulted<bool> == Defaulted<Tra3, bool>{}
		, tra4 % defaulted<bool> == Defaulted<Tra4, bool>{}
		, int1 % defaulted<bool> == Defaulted<Int1, bool>{}
		, int2 % defaulted<bool> == Defaulted<Int2, bool>{}
		, int3 % defaulted<bool> == Defaulted<Int3, bool>{}
		, con1 % defaulted<bool> == Defaulted<Con1, bool>{}
		, con2 % defaulted<bool> == Defaulted<Con2, bool>{}
		, con3 % defaulted<bool> == Defaulted<Con3, bool>{}
		, con4 % defaulted<bool> == Defaulted<Con4, bool>{}
		, def1 % defaulted<bool> == Defaulted<Def1, bool>{}
		, def2 % defaulted<bool> == Defaulted<Def2, bool>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Defaulted)
