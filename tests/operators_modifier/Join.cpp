#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Join)

using namespace samples::all;

void prefix()
{
	assert
		, joi1 != join(abc)
		, abc == join(abc)
		, joi2 == join(+abc)
		, joi3 == join(~(abc | qq))
		, joi4 == join(abc >> *qq)
		, joi5 == join(+abc >> ~(abc | qq))
		;
}

void infix()
{
	assert
		, joi1 != abc % join
		, abc == abc % join
		, joi2 == +abc % join
		, joi3 == ~(abc | qq) % join
		, joi4 == (abc >> *qq) % join
		, joi5 == (+abc >> ~(abc | qq)) % join
		;
}

void idempotent()
{
	assert
		, joi1 == join(joi1)
		, joi2 == join(joi2)
		, joi3 == join(joi3)
		, joi4 == join(joi4)
		, joi5 == join(joi5)
		, joi1 == joi1 % join
		, joi2 == joi2 % join
		, joi3 == joi3 % join
		, joi4 == joi4 % join
		, joi5 == joi5 % join
		;
}



template <Parser auto p>
concept valid_for_join = traits::operators::valid_modulo<p, join>;

void join_anything()
{
	assert
		, oc1 % join == OC1{}
		, oc2 % join == OC2{}
		, oc3 % join == OC3{}
		, nc1 % join == NC1{}
		, nc2 % join == NC2{}
		, nc3 % join == NC3{}
		, l1 % join == L1{}
		, l2 % join == L2{}
		, l3 % join == L3{}
		, oc4 % join == OC4{}
		, nc4 % join == NC4{}
		, nc5 % join == NC5{}
		, l4 % join == L4{}
		, qq % join == QQ{}
		, abc % join == ABC{}
		, comma % join == Comma{}
		, spacedot % join == SpaceDot{}
		, cho1 % join == Cho1{}
		, cho2 % join == Cho2{}
		, cho3 % join == Cho3{}
		, cho4 % join == Cho4{}
		, seq1 % join == Join<Seq1>{}
		, seq2 % join == Join<Seq2>{}
		, seq3 % join == Join<Seq3>{}
		, seq4 % join == Join<Seq4>{}
		, may1 % join == Join<May1>{}
		, may2 % join == Join<May2>{}
		, may3 % join == Join<May3>{}
		, may4 % join == Join<May4>{}
		, exa1 % join == Join<Exa1>{}
		, exa2 % join == Join<Exa2>{}
		, exa3 % join == Join<Exa3>{}
		, exa4 % join == Join<Exa4>{}
		, oom1 % join == Join<Oom1>{}
		, oom2 % join == Join<Oom2>{}
		, oom3 % join == Join<Oom3>{}
		, oom4 % join == Join<Oom4>{}
		, zom1 % join == Join<Zom1>{}
		, zom2 % join == Join<Zom2>{}
		, zom3 % join == Join<Zom3>{}
		, zom4 % join == Join<Zom4>{}
		, not valid_for_join<ign1>
		, not valid_for_join<ign2>
		, not valid_for_join<ign3>
		, not valid_for_join<ign4>
		, not valid_for_join<ign5>
		, del1 % join == Join<Del1>{}
		, del2 % join == Join<Del2>{}
		, del3 % join == Join<Del3>{}
		, del4 % join == Join<Del4>{}
		, del5 % join == Join<Del5>{}
		, del6 % join == Join<Del6>{}
		, del7 % join == Join<Del7>{}
		, del8 % join == Join<Del8>{}
		, com1 % join == Com1{}
		, com2 % join == Com2{}
		, com3 % join == Com3{}
		, com4 % join == Join<Com4>{}
		, com5 % join == Join<Com5>{}
		, com6 % join == Join<Com6>{}
		, com7 % join == Join<Com7>{}
		, not valid_for_join<tra1>
		, not valid_for_join<tra2>
		, not valid_for_join<tra3>
		, not valid_for_join<tra4>
		, not valid_for_join<int1>
		, not valid_for_join<int2>
		, not valid_for_join<int3>
		, not valid_for_join<api1>
		, not valid_for_join<api2>
		, not valid_for_join<con1>
		, not valid_for_join<con2>
		, not valid_for_join<con3>
		, not valid_for_join<con4>
		, not valid_for_join<def1>
		, not valid_for_join<def2>
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Join)
#endif
