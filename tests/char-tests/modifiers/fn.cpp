#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("fn modifier");

TEST("fn modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(tra1, fn<func1>(+abc));
	ASSERT_PARSER_VALUES_EQ(tra2, fn<func2>(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(tra3, fn<func3>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(tra4, fn<func4(3)>(+abc >> ~(abc | qq)));
	ASSERT_PARSER_VALUES_NE(tra4, fn<func4(2)>(+abc >> ~(abc | qq)));
}

TEST("fn modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(tra1, +abc % fn<func1>);
	ASSERT_PARSER_VALUES_EQ(tra2, ~(abc | qq) % fn<func2>);
	ASSERT_PARSER_VALUES_EQ(tra3, (abc >> *qq) % fn<func3>);
	ASSERT_PARSER_VALUES_EQ(tra4, (+abc >> ~(abc | qq)) % fn<func4(3)>);
	ASSERT_PARSER_VALUES_NE(tra4, (+abc >> ~(abc | qq)) % fn<func4(2)>);
}



#define FN_MODIFIER_ASSERTER(P)                                                                             \
	[&]<Parser PP>(PP) {                                                                                    \
		if constexpr (std::same_as<typename PP::result_type, void>)                                         \
		{                                                                                                   \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(fn<sink_func>, (PP{}),                                         \
				                             fn<sink_func>, (P{}));                                         \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, fn<sink_func>,                                    \
				                                    P{},  fn<sink_func>);                                   \
		}                                                                                                   \
		else                                                                                                \
		{                                                                                                   \
			DEP_ASSERT_MODIFIER_CALLABLE_R(fn<sink_func>, (PP{}), (Transform<PP, Const<sink_func>>{}),      \
				                           fn<sink_func>, (P{}),  (Transform<P, Const<sink_func>>{}));      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, fn<sink_func>, (Transform<PP, Const<sink_func>>{}), \
				                                  P{},  fn<sink_func>, (Transform<P, Const<sink_func>>{})); \
		}                                                                                                   \
	}(P{});

TEST("fn modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(FN_MODIFIER_ASSERTER);
}
