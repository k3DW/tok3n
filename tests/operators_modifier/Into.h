#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(modifier::Into)

using namespace samples::all;

void prefix()
{
	assert
		, int1 == into<Class1>(spacedot)
		, int2 == into<Class2>(abc >> spacedot)
		;
}

void infix()
{
	assert
		, int1 == spacedot % into<Class1>
		, int2 == (abc >> spacedot) % into<Class2>
		;
}



template <auto p>
constexpr bool valid_for_into = traits::operators::valid_modulo<p, into<Sink>>;

void into_anything()
{
	assert
		, oc1 % into<Sink> == Into<OC1, Sink>{}
		, oc2 % into<Sink> == Into<OC2, Sink>{}
		, oc3 % into<Sink> == Into<OC3, Sink>{}
		, nc1 % into<Sink> == Into<NC1, Sink>{}
		, nc2 % into<Sink> == Into<NC2, Sink>{}
		, nc3 % into<Sink> == Into<NC3, Sink>{}
		, l1 % into<Sink> == Into<L1, Sink>{}
		, l2 % into<Sink> == Into<L2, Sink>{}
		, l3 % into<Sink> == Into<L3, Sink>{}
		, oc4 % into<Sink> == Into<OC4, Sink>{}
		, nc4 % into<Sink> == Into<NC4, Sink>{}
		, nc5 % into<Sink> == Into<NC5, Sink>{}
		, l4 % into<Sink> == Into<L4, Sink>{}
		, qq % into<Sink> == Into<QQ, Sink>{}
		, abc % into<Sink> == Into<ABC, Sink>{}
		, comma % into<Sink> == Into<Comma, Sink>{}
		, spacedot % into<Sink> == Into<SpaceDot, Sink>{}
		, cho1 % into<Sink> == Into<Cho1, Sink>{}
		, cho2 % into<Sink> == Into<Cho2, Sink>{}
		, cho3 % into<Sink> == Into<Cho3, Sink>{}
		, cho4 % into<Sink> == Into<Cho4, Sink>{}
		, seq1 % into<Sink> == Into<Seq1, Sink>{}
		, seq2 % into<Sink> == Into<Seq2, Sink>{}
		, seq3 % into<Sink> == Into<Seq3, Sink>{}
		, seq4 % into<Sink> == Into<Seq4, Sink>{}
		, may1 % into<Sink> == Into<May1, Sink>{}
		, may2 % into<Sink> == Into<May2, Sink>{}
		, may3 % into<Sink> == Into<May3, Sink>{}
		, may4 % into<Sink> == Into<May4, Sink>{}
		, exa1 % into<Sink> == Into<Exa1, Sink>{}
		, exa2 % into<Sink> == Into<Exa2, Sink>{}
		, exa3 % into<Sink> == Into<Exa3, Sink>{}
		, exa4 % into<Sink> == Into<Exa4, Sink>{}
		, oom1 % into<Sink> == Into<Oom1, Sink>{}
		, oom2 % into<Sink> == Into<Oom2, Sink>{}
		, oom3 % into<Sink> == Into<Oom3, Sink>{}
		, oom4 % into<Sink> == Into<Oom4, Sink>{}
		, zom1 % into<Sink> == Into<Zom1, Sink>{}
		, zom2 % into<Sink> == Into<Zom2, Sink>{}
		, zom3 % into<Sink> == Into<Zom3, Sink>{}
		, zom4 % into<Sink> == Into<Zom4, Sink>{}
		, not valid_for_into<ign1>
		, not valid_for_into<ign2>
		, not valid_for_into<ign3>
		, not valid_for_into<ign4>
		, not valid_for_into<ign5>
		, del1 % into<Sink> == Into<Del1, Sink>{}
		, del2 % into<Sink> == Into<Del2, Sink>{}
		, del3 % into<Sink> == Into<Del3, Sink>{}
		, del4 % into<Sink> == Into<Del4, Sink>{}
		, del5 % into<Sink> == Into<Del5, Sink>{}
		, del6 % into<Sink> == Into<Del6, Sink>{}
		, del7 % into<Sink> == Into<Del7, Sink>{}
		, del8 % into<Sink> == Into<Del8, Sink>{}
		, com1 % into<Sink> == Into<Com1, Sink>{}
		, com2 % into<Sink> == Into<Com2, Sink>{}
		, com3 % into<Sink> == Into<Com3, Sink>{}
		, com4 % into<Sink> == Into<Com4, Sink>{}
		, com5 % into<Sink> == Into<Com5, Sink>{}
		, com6 % into<Sink> == Into<Com6, Sink>{}
		, com7 % into<Sink> == Into<Com7, Sink>{}
		, tra1 % into<Sink> == Into<Tra1, Sink>{}
		, tra2 % into<Sink> == Into<Tra2, Sink>{}
		, tra3 % into<Sink> == Into<Tra3, Sink>{}
		, tra4 % into<Sink> == Into<Tra4, Sink>{}
		, int1 % into<Sink> == Into<Int1, Sink>{}
		, int2 % into<Sink> == Into<Int2, Sink>{}
		, int3 % into<Sink> == Into<Int3, Sink>{}
		, con1 % into<Sink> == Into<Con1, Sink>{}
		, con2 % into<Sink> == Into<Con2, Sink>{}
		, con3 % into<Sink> == Into<Con3, Sink>{}
		, con4 % into<Sink> == Into<Con4, Sink>{}
		, def1 % into<Sink> == Into<Def1, Sink>{}
		, def2 % into<Sink> == Into<Def2, Sink>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::Into)
