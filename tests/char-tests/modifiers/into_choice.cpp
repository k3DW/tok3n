#include "pch.h"
#include "char-samples/char-samples.h"

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
	constexpr auto sink_parser = eps<char> % constant<Sink{}>;
	using SinkParser = std::remove_cvref_t<decltype(sink_parser)>;

	constexpr auto empty_literal_parser = eps<char>;
	using EmptyAllOfParser = std::remove_cvref_t<decltype(empty_literal_parser)>;
}

#define INTO_CHOICE_MODIFIER_ASSERTER(P)                                                                                            \
	[&]<Parser PP>(PP) {                                                                                                            \
		ASSERT_MODIFIER_NOT_CALLABLE(into_choice<Sink>, (P{}));                                                                     \
		ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P{}, into_choice<Sink>);                                                                \
		ASSERT_MODIFIER_NOT_CALLABLE(into_choice<Output<char>>, (P{}));                                                             \
		ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P{}, into_choice<Output<char>>);                                                        \
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
		if constexpr (std::constructible_from<Output<char>, typename PP::result_type>)                                              \
		{                                                                                                                           \
			DEP_ASSERT_MODIFIER_CALLABLE_R(into_choice<Output<char>>, (PP{}, empty_literal_parser),                                 \
												(Choice<Into<PP, Output<char>>, Into<EmptyAllOfParser, Output<char>>>{}),         \
				                           into_choice<Output<char>>, (P{}, empty_literal_parser),                                  \
												(Choice<Into<P, Output<char>>, Into<EmptyAllOfParser, Output<char>>>{}));         \
		}                                                                                                                           \
		else                                                                                                                        \
		{                                                                                                                           \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(into_choice<Output<char>>, (PP{}, empty_literal_parser),                               \
				                             into_choice<Output<char>>, (P{}, empty_literal_parser));                               \
		}                                                                                                                           \
	}(P{});

TEST("into_choice modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(INTO_CHOICE_MODIFIER_ASSERTER);
}
