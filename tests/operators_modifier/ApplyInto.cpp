#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

using namespace samples::all;

inline void prefix()
{
	assert
		, api1 == apply_into<Class2>(abc >> spacedot)
		, api2 == apply_into<Class5>(spacedot >> abc)
		;
}

inline void infix()
{
	assert
		, api1 == (abc >> spacedot) % apply_into<Class2>
		, api2 == (spacedot >> abc) % apply_into<Class5>
		;
}



template <Parser auto p>
concept valid_for_apply_into = traits::operators::valid_modulo<p, apply_into<Sink>>;

inline void into_anything()
{
	assert
		, not valid_for_apply_into<oc1>
		, not valid_for_apply_into<oc2>
		, not valid_for_apply_into<oc3>
		, not valid_for_apply_into<nc1>
		, not valid_for_apply_into<nc2>
		, not valid_for_apply_into<nc3>
		, not valid_for_apply_into<l1>
		, not valid_for_apply_into<l2>
		, not valid_for_apply_into<l3>
		, not valid_for_apply_into<oc4>
		, not valid_for_apply_into<nc4>
		, not valid_for_apply_into<nc5>
		, not valid_for_apply_into<l4>
		, not valid_for_apply_into<qq>
		, not valid_for_apply_into<abc>
		, not valid_for_apply_into<comma>
		, not valid_for_apply_into<spacedot>
		, not valid_for_apply_into<cho1>
		, not valid_for_apply_into<cho2>
		, not valid_for_apply_into<cho3>
		, not valid_for_apply_into<cho4>
		, seq1 % apply_into<Sink> == ApplyInto<Seq1, Sink>{}
		, seq2 % apply_into<Sink> == ApplyInto<Seq2, Sink>{}
		, seq3 % apply_into<Sink> == ApplyInto<Seq3, Sink>{}
		, seq4 % apply_into<Sink> == ApplyInto<Seq4, Sink>{}
		, not valid_for_apply_into<may1>
		, not valid_for_apply_into<may2>
		, not valid_for_apply_into<may3>
		, not valid_for_apply_into<may4>
		, exa1 % apply_into<Sink> == ApplyInto<Exa1, Sink>{}
		, exa2 % apply_into<Sink> == ApplyInto<Exa2, Sink>{}
		, exa3 % apply_into<Sink> == ApplyInto<Exa3, Sink>{}
		, exa4 % apply_into<Sink> == ApplyInto<Exa4, Sink>{}
		, not valid_for_apply_into<oom1>
		, not valid_for_apply_into<oom2>
		, not valid_for_apply_into<oom3>
		, not valid_for_apply_into<oom4>
		, not valid_for_apply_into<zom1>
		, not valid_for_apply_into<zom2>
		, not valid_for_apply_into<zom3>
		, not valid_for_apply_into<zom4>
		, not valid_for_apply_into<ign1>
		, not valid_for_apply_into<ign2>
		, not valid_for_apply_into<ign3>
		, not valid_for_apply_into<ign4>
		, not valid_for_apply_into<ign5>
		, not valid_for_apply_into<del1>
		, not valid_for_apply_into<del2>
		, not valid_for_apply_into<del3>
		, not valid_for_apply_into<del4>
		, not valid_for_apply_into<del5>
		, not valid_for_apply_into<del6>
		, not valid_for_apply_into<del7>
		, not valid_for_apply_into<del8>
		, not valid_for_apply_into<com1>
		, not valid_for_apply_into<com2>
		, not valid_for_apply_into<com3>
		, com4 % apply_into<Sink> == ApplyInto<Com4, Sink>{}
		, not valid_for_apply_into<com5>
		, not valid_for_apply_into<com6>
		, not valid_for_apply_into<com7>
		, not valid_for_apply_into<tra1>
		, not valid_for_apply_into<tra2>
		, not valid_for_apply_into<tra3>
		, not valid_for_apply_into<tra4>
		, not valid_for_apply_into<apt1>
		, not valid_for_apply_into<apt2>
		, not valid_for_apply_into<int1>
		, not valid_for_apply_into<int2>
		, not valid_for_apply_into<int3>
		, not valid_for_apply_into<api1>
		, not valid_for_apply_into<api2>
		, not valid_for_apply_into<con1>
		, not valid_for_apply_into<con2>
		, not valid_for_apply_into<con3>
		, not valid_for_apply_into<con4>
		, not valid_for_apply_into<def1>
		, not valid_for_apply_into<def2>
		;
}

TOK3N_END_NAMESPACE(tests)
