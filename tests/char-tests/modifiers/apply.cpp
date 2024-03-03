#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("apply modifier");

TEST("apply modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(apt1, apply<func3_apply>(abc >> *qq));
	ASSERT_PARSER_VALUES_EQ(apt2, apply<func4_apply(3)>(+abc >> ~(abc | qq)));
	ASSERT_PARSER_VALUES_NE(apt2, apply<func4_apply(2)>(+abc >> ~(abc | qq)));
}

TEST("apply modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(apt1, (abc >> *qq) % apply<func3_apply>);
	ASSERT_PARSER_VALUES_EQ(apt2, (+abc >> ~(abc | qq)) % apply<func4_apply(3)>);
	ASSERT_PARSER_VALUES_NE(apt2, (+abc >> ~(abc | qq)) % apply<func4_apply(2)>);
}



#define APPLY_MODIFIER_ASSERTER(P)                                                                                  \
	[&]<Parser PP>(PP) {                                                                                            \
		if constexpr (detail::has_tuple_size<typename PP::result_type>)                                             \
		{                                                                                                           \
			DEP_ASSERT_MODIFIER_CALLABLE_R(apply<sink_func>, (PP{}), (ApplyTransform<PP, Const<sink_func>>{}),      \
				                           apply<sink_func>, (P{}),  (ApplyTransform<P, Const<sink_func>>{}));      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, apply<sink_func>, (ApplyTransform<PP, Const<sink_func>>{}), \
				                                  P{},  apply<sink_func>, (ApplyTransform<P, Const<sink_func>>{})); \
		}                                                                                                           \
		else                                                                                                        \
		{                                                                                                           \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(apply<sink_func>, (PP{}),                                              \
				                             apply<sink_func>, (P{}));                                              \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, apply<sink_func>,                                         \
				                                    P{},  apply<sink_func>);                                        \
		}                                                                                                           \
	}(P{});

TEST("apply modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(APPLY_MODIFIER_ASSERTER);
}
