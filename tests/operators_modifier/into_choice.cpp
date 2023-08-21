#include "pch.h"

FIXTURE("into_choice modifier");

TEST("into_choice modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(into_choice<Class1>(spacedot, abc), (Choice<Into<SpaceDot, Class1>, Into<ABC, Class1>>{}));
	ASSERT_PARSER_VALUES_EQ(into_choice<Class1>(abc, spacedot), (Choice<Into<ABC, Class1>, Into<SpaceDot, Class1>>{}));

	ASSERT_MODIFIER_NOT_CALLABLE(into_choice<Class1>, (abc, (spacedot >> abc)));
	ASSERT_MODIFIER_CALLABLE(into_choice<Sink>, (abc, (spacedot >> abc)));
}

TEST("into_choice modifier", "infix")
{
	// Infix isn't ever valid with into_choice because Choice parsers must have 2 sub parsers

	ASSERT_MODIFIER_NOT_MODULO_OPERABLE(spacedot, into_choice<Class1>);
	ASSERT_MODIFIER_NOT_MODULO_OPERABLE(spacedot, into_choice<Sink>);
	ASSERT_MODIFIER_NOT_MODULO_OPERABLE((abc >> spacedot), into_choice<Class2>);
	ASSERT_MODIFIER_NOT_MODULO_OPERABLE((abc >> spacedot), into_choice<Sink>);
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

TEST("into_choice modifier", "modify anything")
{
	ASSERT(check_all_samples(into_choice_checker), "check_all_samples(into_choice_checker) failed");
}
