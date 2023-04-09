#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

inline void prefix()
{
	assert
		, con1 == constant<1>(+abc)
		, con2 == constant<'t'>(~(abc | qq))
		, con3 == constant<true>(abc >> *qq)
		, con4 == constant<nullptr>(+abc >> ~(abc | qq))
		;
}

inline void infix()
{
	assert
		, con1 == +abc % constant<1>
		, con2 == ~(abc | qq) % constant<'t'>
		, con3 == (abc >> *qq) % constant<true>
		, con4 == (+abc >> ~(abc | qq)) % constant<nullptr>
		;
}



inline void constant_anything()
{
	assert
		, oc1 % constant<0> == Constant<OC1, 0>{}
		, oc2 % constant<0> == Constant<OC2, 0>{}
		, oc3 % constant<0> == Constant<OC3, 0>{}
		, nc1 % constant<0> == Constant<NC1, 0>{}
		, nc2 % constant<0> == Constant<NC2, 0>{}
		, nc3 % constant<0> == Constant<NC3, 0>{}
		, l1 % constant<0> == Constant<L1, 0>{}
		, l2 % constant<0> == Constant<L2, 0>{}
		, l3 % constant<0> == Constant<L3, 0>{}
		, oc4 % constant<0> == Constant<OC4, 0>{}
		, nc4 % constant<0> == Constant<NC4, 0>{}
		, nc5 % constant<0> == Constant<NC5, 0>{}
		, l4 % constant<0> == Constant<L4, 0>{}
		, qq % constant<0> == Constant<QQ, 0>{}
		, abc % constant<0> == Constant<ABC, 0>{}
		, comma % constant<0> == Constant<Comma, 0>{}
		, spacedot % constant<0> == Constant<SpaceDot, 0>{}
		, cho1 % constant<0> == Constant<Cho1, 0>{}
		, cho2 % constant<0> == Constant<Cho2, 0>{}
		, cho3 % constant<0> == Constant<Cho3, 0>{}
		, cho4 % constant<0> == Constant<Cho4, 0>{}
		, seq1 % constant<0> == Constant<Seq1, 0>{}
		, seq2 % constant<0> == Constant<Seq2, 0>{}
		, seq3 % constant<0> == Constant<Seq3, 0>{}
		, seq4 % constant<0> == Constant<Seq4, 0>{}
		, may1 % constant<0> == Constant<May1, 0>{}
		, may2 % constant<0> == Constant<May2, 0>{}
		, may3 % constant<0> == Constant<May3, 0>{}
		, may4 % constant<0> == Constant<May4, 0>{}
		, exa1 % constant<0> == Constant<Exa1, 0>{}
		, exa2 % constant<0> == Constant<Exa2, 0>{}
		, exa3 % constant<0> == Constant<Exa3, 0>{}
		, exa4 % constant<0> == Constant<Exa4, 0>{}
		, oom1 % constant<0> == Constant<Oom1, 0>{}
		, oom2 % constant<0> == Constant<Oom2, 0>{}
		, oom3 % constant<0> == Constant<Oom3, 0>{}
		, oom4 % constant<0> == Constant<Oom4, 0>{}
		, zom1 % constant<0> == Constant<Zom1, 0>{}
		, zom2 % constant<0> == Constant<Zom2, 0>{}
		, zom3 % constant<0> == Constant<Zom3, 0>{}
		, zom4 % constant<0> == Constant<Zom4, 0>{}
		, ign1 % constant<0> == Constant<Ign1, 0>{}
		, ign2 % constant<0> == Constant<Ign2, 0>{}
		, ign3 % constant<0> == Constant<Ign3, 0>{}
		, ign4 % constant<0> == Constant<Ign4, 0>{}
		, ign5 % constant<0> == Constant<Ign5, 0>{}
		, del1 % constant<0> == Constant<Del1, 0>{}
		, del2 % constant<0> == Constant<Del2, 0>{}
		, del3 % constant<0> == Constant<Del3, 0>{}
		, del4 % constant<0> == Constant<Del4, 0>{}
		, del5 % constant<0> == Constant<Del5, 0>{}
		, del6 % constant<0> == Constant<Del6, 0>{}
		, del7 % constant<0> == Constant<Del7, 0>{}
		, del8 % constant<0> == Constant<Del8, 0>{}
		, com1 % constant<0> == Constant<Com1, 0>{}
		, com2 % constant<0> == Constant<Com2, 0>{}
		, com3 % constant<0> == Constant<Com3, 0>{}
		, com4 % constant<0> == Constant<Com4, 0>{}
		, com5 % constant<0> == Constant<Com5, 0>{}
		, com6 % constant<0> == Constant<Com6, 0>{}
		, com7 % constant<0> == Constant<Com7, 0>{}
		, tra1 % constant<0> == Constant<Tra1, 0>{}
		, tra2 % constant<0> == Constant<Tra2, 0>{}
		, tra3 % constant<0> == Constant<Tra3, 0>{}
		, tra4 % constant<0> == Constant<Tra4, 0>{}
		, apt1 % constant<0> == Constant<Apt1, 0>{}
		, apt2 % constant<0> == Constant<Apt2, 0>{}
		, int1 % constant<0> == Constant<Int1, 0>{}
		, int2 % constant<0> == Constant<Int2, 0>{}
		, int3 % constant<0> == Constant<Int3, 0>{}
		, api1 % constant<0> == Constant<Api1, 0>{}
		, api2 % constant<0> == Constant<Api2, 0>{}
		, con1 % constant<0> == Constant<Con1, 0>{}
		, con2 % constant<0> == Constant<Con2, 0>{}
		, con3 % constant<0> == Constant<Con3, 0>{}
		, con4 % constant<0> == Constant<Con4, 0>{}
		, def1 % constant<0> == Constant<Def1, 0>{}
		, def2 % constant<0> == Constant<Def2, 0>{}
		;
}

TOK3N_END_NAMESPACE(tests)
