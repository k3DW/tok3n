#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(regular::Not)

using namespace samples::all;

void not_OneChar()
{
	assert
		, !oc1 == nc1
		, !oc2 == nc2
		, !oc3 == nc3
		, !!oc1 == oc1
		, !!oc2 == oc2
		, !!oc3 == oc3
		;
}

void not_NotChar()
{
	assert
		, !nc1 == oc1
		, !nc2 == oc2
		, !nc3 == oc3
		, !!nc1 == nc1
		, !!nc2 == nc2
		, !!nc3 == nc3
		;
}



template <Parser auto parser>
concept valid_not_operator = traits::operators::valid_bang<parser>;

void not_anything()
{
	assert
		, !oc1 == NotChar<"abc">{}
		, !oc2 == NotChar<"bcd">{}
		, !oc3 == NotChar<"xyz">{}
		, !nc1 == OneChar<"abc">{}
		, !nc2 == OneChar<"bcd">{}
		, !nc3 == OneChar<"xyz">{}
		, not valid_not_operator<l1>
		, not valid_not_operator<l2>
		, not valid_not_operator<l3>
		, !oc4 == NotChar<"cd">{}
		, !nc4 == OneChar<"cd">{}
		, !nc5 == OneChar<"z">{}
		, not valid_not_operator<l4>
		, not valid_not_operator<qq>
		, not valid_not_operator<abc>
		, !comma == NotChar<",">{}
		, !spacedot == NotChar<" .">{}
		, not valid_not_operator<cho1>
		, not valid_not_operator<cho2>
		, not valid_not_operator<cho3>
		, not valid_not_operator<cho4>
		, not valid_not_operator<seq1>
		, not valid_not_operator<seq2>
		, not valid_not_operator<seq3>
		, not valid_not_operator<seq4>
		, not valid_not_operator<may1>
		, not valid_not_operator<may2>
		, not valid_not_operator<may3>
		, not valid_not_operator<may4>
		, not valid_not_operator<exa1>
		, not valid_not_operator<exa2>
		, not valid_not_operator<exa3>
		, not valid_not_operator<exa4>
		, not valid_not_operator<oom1>
		, not valid_not_operator<oom2>
		, not valid_not_operator<oom3>
		, not valid_not_operator<oom4>
		, not valid_not_operator<zom1>
		, not valid_not_operator<zom2>
		, not valid_not_operator<zom3>
		, not valid_not_operator<zom4>
		, not valid_not_operator<ign1>
		, not valid_not_operator<ign2>
		, not valid_not_operator<ign3>
		, not valid_not_operator<ign4>
		, not valid_not_operator<ign5>
		, not valid_not_operator<del1>
		, not valid_not_operator<del2>
		, not valid_not_operator<del3>
		, not valid_not_operator<del4>
		, not valid_not_operator<del5>
		, not valid_not_operator<del6>
		, not valid_not_operator<del7>
		, not valid_not_operator<del8>
		, not valid_not_operator<com1>
		, not valid_not_operator<com2>
		, not valid_not_operator<com3>
		, not valid_not_operator<com4>
		, not valid_not_operator<com5>
		, not valid_not_operator<com6>
		, not valid_not_operator<com7>
		, not valid_not_operator<tra1>
		, not valid_not_operator<tra2>
		, not valid_not_operator<tra3>
		, not valid_not_operator<tra4>
		, not valid_not_operator<int1>
		, not valid_not_operator<int2>
		, not valid_not_operator<int3>
		, not valid_not_operator<api1>
		, not valid_not_operator<api2>
		, not valid_not_operator<con1>
		, not valid_not_operator<con2>
		, not valid_not_operator<con3>
		, not valid_not_operator<con4>
		, not valid_not_operator<def1>
		, not valid_not_operator<def2>
		;
}

TOK3N_END_NAMESPACE_TESTS(regular::Not)
#endif
