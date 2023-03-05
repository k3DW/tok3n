#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(modifier::IntoChoice)

using namespace samples::all;

template <class T, auto... args>
constexpr bool valid_for_into_choice = traits::operators::valid_function_call<into_choice<T>, args...>;

void prefix()
{
	assert
		, into_choice<Class1>(spacedot, abc) == Choice<Into<SpaceDot, Class1>, Into<ABC, Class1>>{}
		, into_choice<Class1>(abc, spacedot) == Choice<Into<ABC, Class1>, Into<SpaceDot, Class1>>{}
		, not valid_for_into_choice<Class1, abc, (spacedot >> abc)>
		, valid_for_into_choice<Sink, abc, (spacedot >> abc)>
		;
}

void infix()
{
	// Infix isn't ever valid with into_choice because Choice parsers must have 2 sub parsers
	using traits::operators::valid_modulo;

	assert
		, not valid_modulo<spacedot, into_choice<Class1>>
		, not valid_modulo<spacedot, into_choice<Sink>>
		, not valid_modulo<(abc >> spacedot), into_choice<Class2>>
		, not valid_modulo<(abc >> spacedot), into_choice<Sink>>
		;
}



void into_anything()
{
	constexpr auto sink_parser = "0"_one % constant<Sink{}>;
	using SinkParser = std::remove_cvref_t<decltype(sink_parser)>;

	assert
		, into_choice<Sink>(oc1, sink_parser) == Choice<Into<OC1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(oc2, sink_parser) == Choice<Into<OC2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(oc3, sink_parser) == Choice<Into<OC3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(nc1, sink_parser) == Choice<Into<NC1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(nc2, sink_parser) == Choice<Into<NC2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(nc3, sink_parser) == Choice<Into<NC3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(l1, sink_parser) == Choice<Into<L1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(l2, sink_parser) == Choice<Into<L2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(l3, sink_parser) == Choice<Into<L3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(oc4, sink_parser) == Choice<Into<OC4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(nc4, sink_parser) == Choice<Into<NC4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(nc5, sink_parser) == Choice<Into<NC5, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(l4, sink_parser) == Choice<Into<L4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(qq, sink_parser) == Choice<Into<QQ, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(abc, sink_parser) == Choice<Into<ABC, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(comma, sink_parser) == Choice<Into<Comma, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(spacedot, sink_parser) == Choice<Into<SpaceDot, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(cho1, sink_parser) == Choice<Into<Cho1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(cho2, sink_parser) == Choice<Into<Cho2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(cho3, sink_parser) == Choice<Into<Cho3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(cho4, sink_parser) == Choice<Into<Cho4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(seq1, sink_parser) == Choice<Into<Seq1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(seq2, sink_parser) == Choice<Into<Seq2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(seq3, sink_parser) == Choice<Into<Seq3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(seq4, sink_parser) == Choice<Into<Seq4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(may1, sink_parser) == Choice<Into<May1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(may2, sink_parser) == Choice<Into<May2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(may3, sink_parser) == Choice<Into<May3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(may4, sink_parser) == Choice<Into<May4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(exa1, sink_parser) == Choice<Into<Exa1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(exa2, sink_parser) == Choice<Into<Exa2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(exa3, sink_parser) == Choice<Into<Exa3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(exa4, sink_parser) == Choice<Into<Exa4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(oom1, sink_parser) == Choice<Into<Oom1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(oom2, sink_parser) == Choice<Into<Oom2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(oom3, sink_parser) == Choice<Into<Oom3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(oom4, sink_parser) == Choice<Into<Oom4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(zom1, sink_parser) == Choice<Into<Zom1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(zom2, sink_parser) == Choice<Into<Zom2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(zom3, sink_parser) == Choice<Into<Zom3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(zom4, sink_parser) == Choice<Into<Zom4, Sink>, Into<SinkParser, Sink>>{}
		, not valid_for_into_choice<Sink, ign1, sink_parser>
		, not valid_for_into_choice<Sink, ign2, sink_parser>
		, not valid_for_into_choice<Sink, ign3, sink_parser>
		, not valid_for_into_choice<Sink, ign4, sink_parser>
		, not valid_for_into_choice<Sink, ign5, sink_parser>
		, into_choice<Sink>(del1, sink_parser) == Choice<Into<Del1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(del2, sink_parser) == Choice<Into<Del2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(del3, sink_parser) == Choice<Into<Del3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(del4, sink_parser) == Choice<Into<Del4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(del5, sink_parser) == Choice<Into<Del5, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(del6, sink_parser) == Choice<Into<Del6, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(del7, sink_parser) == Choice<Into<Del7, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(del8, sink_parser) == Choice<Into<Del8, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(com1, sink_parser) == Choice<Into<Com1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(com2, sink_parser) == Choice<Into<Com2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(com3, sink_parser) == Choice<Into<Com3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(com4, sink_parser) == Choice<Into<Com4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(com5, sink_parser) == Choice<Into<Com5, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(com6, sink_parser) == Choice<Into<Com6, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(com7, sink_parser) == Choice<Into<Com7, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(tra1, sink_parser) == Choice<Into<Tra1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(tra2, sink_parser) == Choice<Into<Tra2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(tra3, sink_parser) == Choice<Into<Tra3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(tra4, sink_parser) == Choice<Into<Tra4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(int1, sink_parser) == Choice<Into<Int1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(int2, sink_parser) == Choice<Into<Int2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(int3, sink_parser) == Choice<Into<Int3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(api1, sink_parser) == Choice<Into<Api1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(api2, sink_parser) == Choice<Into<Api2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(con1, sink_parser) == Choice<Into<Con1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(con2, sink_parser) == Choice<Into<Con2, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(con3, sink_parser) == Choice<Into<Con3, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(con4, sink_parser) == Choice<Into<Con4, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(def1, sink_parser) == Choice<Into<Def1, Sink>, Into<SinkParser, Sink>>{}
		, into_choice<Sink>(def2, sink_parser) == Choice<Into<Def2, Sink>, Into<SinkParser, Sink>>{}
		;
}

TOK3N_END_NAMESPACE_TESTS(modifier::IntoChoice)
#endif
