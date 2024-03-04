#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("apply_into modifier");

TEST("apply_into modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(api1, apply_into<Class2>(abc >> spacedot));
	ASSERT_PARSER_VALUES_EQ(api2, apply_into<Class5>(spacedot >> abc));
}

TEST("apply_into modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(api1, (abc >> spacedot) % apply_into<Class2>);
	ASSERT_PARSER_VALUES_EQ(api2, (spacedot >> abc) % apply_into<Class5>);
}



#define APPLY_INTO_MODIFIER_ASSERTER(P)                                                            \
	[&]<Parser PP>(PP) {                                                                           \
		if constexpr (detail::has_tuple_size<typename PP::result_type>)                            \
		{                                                                                          \
			DEP_ASSERT_MODIFIER_CALLABLE_R(apply_into<Sink>, (PP{}), (ApplyInto<PP, Sink>{}),      \
				                           apply_into<Sink>, (P{}),  (ApplyInto<P, Sink>{}));      \
			DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, apply_into<Sink>, (ApplyInto<PP, Sink>{}), \
				                                  P{},  apply_into<Sink>, (ApplyInto<P, Sink>{})); \
		}                                                                                          \
		else                                                                                       \
		{                                                                                          \
			DEP_ASSERT_MODIFIER_NOT_CALLABLE(apply_into<Sink>, (PP{}),                             \
				                             apply_into<Sink>, (P{}));                             \
			DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, apply_into<Sink>,                        \
				                                    P{},  apply_into<Sink>);                       \
		}                                                                                          \
	}(P{});

TEST("apply_into modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(APPLY_INTO_MODIFIER_ASSERTER);
}
