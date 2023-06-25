#include "pch.h"

namespace k3::tok3n::tests {

using namespace traits::operators;

inline void prefix()
{
	assert
		, into_choice<Class1>(spacedot, abc) == Choice<Into<SpaceDot, Class1>, Into<ABC, Class1>>{}
		, into_choice<Class1>(abc, spacedot) == Choice<Into<ABC, Class1>, Into<SpaceDot, Class1>>{}
		, not valid_function_call<into_choice<Class1>, abc, (spacedot >> abc)>
		, valid_function_call<into_choice<Sink>, abc, (spacedot >> abc)>
		;
}

inline void infix()
{
	// Infix isn't ever valid with into_choice because Choice parsers must have 2 sub parsers

	assert
		, not valid_modulo<spacedot, into_choice<Class1>>
		, not valid_modulo<spacedot, into_choice<Sink>>
		, not valid_modulo<(abc >> spacedot), into_choice<Class2>>
		, not valid_modulo<(abc >> spacedot), into_choice<Sink>>
		;
}



namespace
{
	constexpr auto sink_parser = ""_lit % constant < Sink{} > ;
	using SinkParser = std::remove_cvref_t<decltype(sink_parser)>;

	constexpr auto empty_literal_parser = ""_lit;
	using EmptyLiteralParser = std::remove_cvref_t<decltype(empty_literal_parser)>;
}

constexpr auto into_choice_checker = []<Parser P>(P) -> bool
{
	TOK3N_ASSERT_P( not requires { into_choice<Sink>(P{}); },  "into_choice<Sink> prefix operator compiles with 1 parser, but it shouldn't" );
	TOK3N_ASSERT_P( not requires { P{} % into_choice<Sink>; }, "into_choice<Sink> infix operator compiles with 1 parser, but it shouldn't" );
	
	if constexpr (std::same_as<typename P::result_type, void>)
	{
		TOK3N_ASSERT_P( not requires { into_choice<Sink>(P{}, sink_parser); },
			"into_choice<Sink> prefix operator compiles with 2 parsers, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P( requires { into_choice<Sink>(P{}, sink_parser); },
			"into_choice<Sink> prefix operator doesn't compile with 2 parsers, but it should" );
		TOK3N_ASSERT_P( into_choice<Sink>(P{}, sink_parser) == (Choice<Into<P, Sink>, Into<SinkParser, Sink>>{}),
			"into_choice<Sink> prefix operator of any other parser should give the complicated parser above" );
	}
	
	if constexpr (std::constructible_from<std::string_view, typename P::result_type>)
	{
		TOK3N_ASSERT_P( requires { into_choice<std::string_view>(P{}, empty_literal_parser); },
			"into_choice<std::string_view> prefix operator doesn't compile with these 2 parsers, but it shouldn't" );
		TOK3N_ASSERT_P( into_choice<std::string_view>(P{}, empty_literal_parser) == (Choice<Into<P, std::string_view>, Into<EmptyLiteralParser, std::string_view>>{}),
			"into_choice<std::string_view> prefix operator of any other parser should give the complicated parser above" );
	}
	else
	{
		TOK3N_ASSERT_P( not requires { into_choice<std::string_view>(P{}, empty_literal_parser); },
			"into_choice<std::string_view> prefix operator compiles with these 2 parsers, but it shouldn't" );
	}

	return true;
};

inline void into_choice_anything()
{
	assert
		, check_all_samples(into_choice_checker)
		;
}

} // namespace k3::tok3n::tests