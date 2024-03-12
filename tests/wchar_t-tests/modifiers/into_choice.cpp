#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("into_choice modifier");

TEST("into_choice modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(into_choice<Class1>(spacedot, abc), (Choice<Into<SpaceDot, Class1>, Into<ABC, Class1>>{}));
	ASSERT_PARSER_VALUES_EQ(into_choice<Class1>(abc, spacedot), (Choice<Into<ABC, Class1>, Into<SpaceDot, Class1>>{}));

	ASSERT_MODIFIER_CALLABLE(into_choice<Class1>, (abc, (spacedot >> abc)));
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
	constexpr auto sink_parser = eps<wchar_t> % constant<Sink{}>;
	using SinkParser = std::remove_cvref_t<decltype(sink_parser)>;

	constexpr auto empty_literal_parser = eps<wchar_t>;
	using EmptyAllOfParser = std::remove_cvref_t<decltype(empty_literal_parser)>;
}
