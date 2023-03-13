#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Transform)

using namespace samples::all;

void prefix()
{
	assert
		, tra1 == fn<func1>(+abc)
		, tra2 == fn<func2>(~(abc | qq))
		, tra3 == fn<func3>(abc >> *qq)
		, tra4 == fn<func4(3)>(+abc >> ~(abc | qq))
		, tra4 != fn<func4(2)>(+abc >> ~(abc | qq))
		;
}

void infix()
{
	assert
		, tra1 == +abc % fn<func1>
		, tra2 == ~(abc | qq) % fn<func2>
		, tra3 == (abc >> *qq) % fn<func3>
		, tra4 == (+abc >> ~(abc | qq)) % fn<func4(3)>
		, tra4 != (+abc >> ~(abc | qq)) % fn<func4(2)>
		;
}



template <Parser auto p>
concept valid_for_transform = traits::operators::valid_modulo<p, fn<sink_func>>;

void transform_anything()
{
	assert
		, oc1 % fn<sink_func> == Transform<OC1, sink_func>{}
		, oc2 % fn<sink_func> == Transform<OC2, sink_func>{}
		, oc3 % fn<sink_func> == Transform<OC3, sink_func>{}
		, nc1 % fn<sink_func> == Transform<NC1, sink_func>{}
		, nc2 % fn<sink_func> == Transform<NC2, sink_func>{}
		, nc3 % fn<sink_func> == Transform<NC3, sink_func>{}
		, l1 % fn<sink_func> == Transform<L1, sink_func>{}
		, l2 % fn<sink_func> == Transform<L2, sink_func>{}
		, l3 % fn<sink_func> == Transform<L3, sink_func>{}
		, oc4 % fn<sink_func> == Transform<OC4, sink_func>{}
		, nc4 % fn<sink_func> == Transform<NC4, sink_func>{}
		, nc5 % fn<sink_func> == Transform<NC5, sink_func>{}
		, l4 % fn<sink_func> == Transform<L4, sink_func>{}
		, qq % fn<sink_func> == Transform<QQ, sink_func>{}
		, abc % fn<sink_func> == Transform<ABC, sink_func>{}
		, comma % fn<sink_func> == Transform<Comma, sink_func>{}
		, spacedot % fn<sink_func> == Transform<SpaceDot, sink_func>{}
		, cho1 % fn<sink_func> == Transform<Cho1, sink_func>{}
		, cho2 % fn<sink_func> == Transform<Cho2, sink_func>{}
		, cho3 % fn<sink_func> == Transform<Cho3, sink_func>{}
		, cho4 % fn<sink_func> == Transform<Cho4, sink_func>{}
		, seq1 % fn<sink_func> == Transform<Seq1, sink_func>{}
		, seq2 % fn<sink_func> == Transform<Seq2, sink_func>{}
		, seq3 % fn<sink_func> == Transform<Seq3, sink_func>{}
		, seq4 % fn<sink_func> == Transform<Seq4, sink_func>{}
		, may1 % fn<sink_func> == Transform<May1, sink_func>{}
		, may2 % fn<sink_func> == Transform<May2, sink_func>{}
		, may3 % fn<sink_func> == Transform<May3, sink_func>{}
		, may4 % fn<sink_func> == Transform<May4, sink_func>{}
		, exa1 % fn<sink_func> == Transform<Exa1, sink_func>{}
		, exa2 % fn<sink_func> == Transform<Exa2, sink_func>{}
		, exa3 % fn<sink_func> == Transform<Exa3, sink_func>{}
		, exa4 % fn<sink_func> == Transform<Exa4, sink_func>{}
		, oom1 % fn<sink_func> == Transform<Oom1, sink_func>{}
		, oom2 % fn<sink_func> == Transform<Oom2, sink_func>{}
		, oom3 % fn<sink_func> == Transform<Oom3, sink_func>{}
		, oom4 % fn<sink_func> == Transform<Oom4, sink_func>{}
		, zom1 % fn<sink_func> == Transform<Zom1, sink_func>{}
		, zom2 % fn<sink_func> == Transform<Zom2, sink_func>{}
		, zom3 % fn<sink_func> == Transform<Zom3, sink_func>{}
		, zom4 % fn<sink_func> == Transform<Zom4, sink_func>{}
		, not valid_for_transform<ign1>
		, not valid_for_transform<ign2>
		, not valid_for_transform<ign3>
		, not valid_for_transform<ign4>
		, not valid_for_transform<ign5>
		, del1 % fn<sink_func> == Transform<Del1, sink_func>{}
		, del2 % fn<sink_func> == Transform<Del2, sink_func>{}
		, del3 % fn<sink_func> == Transform<Del3, sink_func>{}
		, del4 % fn<sink_func> == Transform<Del4, sink_func>{}
		, del5 % fn<sink_func> == Transform<Del5, sink_func>{}
		, del6 % fn<sink_func> == Transform<Del6, sink_func>{}
		, del7 % fn<sink_func> == Transform<Del7, sink_func>{}
		, del8 % fn<sink_func> == Transform<Del8, sink_func>{}
		, com1 % fn<sink_func> == Transform<Com1, sink_func>{}
		, com2 % fn<sink_func> == Transform<Com2, sink_func>{}
		, com3 % fn<sink_func> == Transform<Com3, sink_func>{}
		, com4 % fn<sink_func> == Transform<Com4, sink_func>{}
		, com5 % fn<sink_func> == Transform<Com5, sink_func>{}
		, com6 % fn<sink_func> == Transform<Com6, sink_func>{}
		, com7 % fn<sink_func> == Transform<Com7, sink_func>{}
		, tra1 % fn<sink_func> == Transform<Tra1, sink_func>{}
		, tra2 % fn<sink_func> == Transform<Tra2, sink_func>{}
		, tra3 % fn<sink_func> == Transform<Tra3, sink_func>{}
		, tra4 % fn<sink_func> == Transform<Tra4, sink_func>{}
		, apt1 % fn<sink_func> == Transform<Apt1, sink_func>{}
		, apt2 % fn<sink_func> == Transform<Apt2, sink_func>{}
		, int1 % fn<sink_func> == Transform<Int1, sink_func>{}
		, int2 % fn<sink_func> == Transform<Int2, sink_func>{}
		, int3 % fn<sink_func> == Transform<Int3, sink_func>{}
		, api1 % fn<sink_func> == Transform<Api1, sink_func>{}
		, api2 % fn<sink_func> == Transform<Api2, sink_func>{}
		, con1 % fn<sink_func> == Transform<Con1, sink_func>{}
		, con2 % fn<sink_func> == Transform<Con2, sink_func>{}
		, con3 % fn<sink_func> == Transform<Con3, sink_func>{}
		, con4 % fn<sink_func> == Transform<Con4, sink_func>{}
		, def1 % fn<sink_func> == Transform<Def1, sink_func>{}
		, def2 % fn<sink_func> == Transform<Def2, sink_func>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Transform)
#endif
