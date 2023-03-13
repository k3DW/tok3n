#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(modifier::ApplyTransform)

using namespace samples::all;

void prefix()
{
	assert
		, apt1 == apply<func3_apply>(abc >> *qq)
		, apt2 == apply<func4_apply(3)>(+abc >> ~(abc | qq))
		, apt2 != apply<func4_apply(2)>(+abc >> ~(abc | qq))
		;
}

void infix()
{
	assert
		, apt1 == (abc >> *qq) % apply<func3_apply>
		, apt2 == (+abc >> ~(abc | qq)) % apply<func4_apply(3)>
		, apt2 != (+abc >> ~(abc | qq)) % apply<func4_apply(2)>
		;
}



template <Parser auto p>
concept valid_for_apply_transform = traits::operators::valid_modulo<p, apply<sink_func>>;

void apply_transform_anything()
{
	assert
		, not valid_for_apply_transform<oc1>
		, not valid_for_apply_transform<oc2>
		, not valid_for_apply_transform<oc3>
		, not valid_for_apply_transform<nc1>
		, not valid_for_apply_transform<nc2>
		, not valid_for_apply_transform<nc3>
		, not valid_for_apply_transform<l1>
		, not valid_for_apply_transform<l2>
		, not valid_for_apply_transform<l3>
		, not valid_for_apply_transform<oc4>
		, not valid_for_apply_transform<nc4>
		, not valid_for_apply_transform<nc5>
		, not valid_for_apply_transform<l4>
		, not valid_for_apply_transform<qq>
		, not valid_for_apply_transform<abc>
		, not valid_for_apply_transform<comma>
		, not valid_for_apply_transform<spacedot>
		, not valid_for_apply_transform<cho1>
		, not valid_for_apply_transform<cho2>
		, not valid_for_apply_transform<cho3>
		, not valid_for_apply_transform<cho4>
		, seq1 % apply<sink_func> == ApplyTransform<Seq1, sink_func>{}
		, seq2 % apply<sink_func> == ApplyTransform<Seq2, sink_func>{}
		, seq3 % apply<sink_func> == ApplyTransform<Seq3, sink_func>{}
		, seq4 % apply<sink_func> == ApplyTransform<Seq4, sink_func>{}
		, not valid_for_apply_transform<may1>
		, not valid_for_apply_transform<may2>
		, not valid_for_apply_transform<may3>
		, not valid_for_apply_transform<may4>
		, exa1 % apply<sink_func> == ApplyTransform<Exa1, sink_func>{}
		, exa2 % apply<sink_func> == ApplyTransform<Exa2, sink_func>{}
		, exa3 % apply<sink_func> == ApplyTransform<Exa3, sink_func>{}
		, exa4 % apply<sink_func> == ApplyTransform<Exa4, sink_func>{}
		, not valid_for_apply_transform<oom1>
		, not valid_for_apply_transform<oom2>
		, not valid_for_apply_transform<oom3>
		, not valid_for_apply_transform<oom4>
		, not valid_for_apply_transform<zom1>
		, not valid_for_apply_transform<zom2>
		, not valid_for_apply_transform<zom3>
		, not valid_for_apply_transform<zom4>
		, not valid_for_apply_transform<ign1>
		, not valid_for_apply_transform<ign2>
		, not valid_for_apply_transform<ign3>
		, not valid_for_apply_transform<ign4>
		, not valid_for_apply_transform<ign5>
		, not valid_for_apply_transform<del1>
		, not valid_for_apply_transform<del2>
		, not valid_for_apply_transform<del3>
		, not valid_for_apply_transform<del4>
		, not valid_for_apply_transform<del5>
		, not valid_for_apply_transform<del6>
		, not valid_for_apply_transform<del7>
		, not valid_for_apply_transform<del8>
		, not valid_for_apply_transform<com1>
		, not valid_for_apply_transform<com2>
		, not valid_for_apply_transform<com3>
		, com4 % apply<sink_func> == ApplyTransform<Com4, sink_func>{}
		, not valid_for_apply_transform<com5>
		, not valid_for_apply_transform<com6>
		, not valid_for_apply_transform<com7>
		, not valid_for_apply_transform<tra1>
		, not valid_for_apply_transform<tra2>
		, not valid_for_apply_transform<tra3>
		, not valid_for_apply_transform<tra4>
		, not valid_for_apply_transform<apt1>
		, not valid_for_apply_transform<apt2>
		, not valid_for_apply_transform<int1>
		, not valid_for_apply_transform<int2>
		, not valid_for_apply_transform<int3>
		, not valid_for_apply_transform<api1>
		, not valid_for_apply_transform<api2>
		, not valid_for_apply_transform<con1>
		, not valid_for_apply_transform<con2>
		, not valid_for_apply_transform<con3>
		, not valid_for_apply_transform<con4>
		, not valid_for_apply_transform<def1>
		, not valid_for_apply_transform<def2>
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::ApplyTransform)
#endif
