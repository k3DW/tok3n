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

#define INTO_CHOICE_MODIFIER_ASSERTER(P)                                                                                            \
	[&]<Parser PP>(PP) {                                                                                                            \
		ASSERT_MODIFIER_NOT_CALLABLE(into_choice<Sink>, (P{}));                                                                     \
		ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P{}, into_choice<Sink>);                                                                \
		ASSERT_MODIFIER_NOT_CALLABLE(into_choice<std::string_view>, (P{}));                                                         \
		ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P{}, into_choice<std::string_view>);                                                    \
		if constexpr (std::same_as<typename PP::result_type, void>)                                                                 \
		{                                                                                                                           \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(into_choice<Sink>, (PP{}, sink_parser),                                                \
				                             into_choice<Sink>, (P{}, sink_parser));                                                \
		}                                                                                                                           \
		else                                                                                                                        \
		{                                                                                                                           \
			DEP_ASSERT_MODIFIER_CALLABLE_R(into_choice<Sink>, (PP{}, sink_parser),                                                  \
												(Choice<Into<PP, Sink>, Into<SinkParser, Sink>>{}),                                 \
				                           into_choice<Sink>, (P{}, sink_parser),                                                   \
												(Choice<Into<P, Sink>, Into<SinkParser, Sink>>{}));                                 \
		}                                                                                                                           \
		if constexpr (std::constructible_from<std::string_view, typename PP::result_type>)                                          \
		{                                                                                                                           \
			DEP_ASSERT_MODIFIER_CALLABLE_R(into_choice<std::string_view>, (PP{}, empty_literal_parser),                             \
												(Choice<Into<PP, std::string_view>, Into<EmptyLiteralParser, std::string_view>>{}), \
				                           into_choice<std::string_view>, (P{}, empty_literal_parser),                              \
												(Choice<Into<P, std::string_view>, Into<EmptyLiteralParser, std::string_view>>{})); \
		}                                                                                                                           \
		else                                                                                                                        \
		{                                                                                                                           \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(into_choice<std::string_view>, (PP{}, empty_literal_parser),                           \
				                             into_choice<std::string_view>, (P{}, empty_literal_parser));                           \
		}                                                                                                                           \
	}(P{});

TEST("into_choice modifier", "modify anything")
{
	DO_TO_SAMPLES_ALL(INTO_CHOICE_MODIFIER_ASSERTER);
}
