#pragma once
#include "framework/Assert.h"
#include "asserts/Concept.h"
#include "asserts/Equality.h"
#include <k3/tok3n/concepts/Parser.h>

template <auto f, auto... args>
concept callable = requires {
	{ f(args...) } -> k3::tok3n::Parser;
};

template <auto lhs, auto rhs>
concept modulo_operable = requires {
	{ lhs % rhs } -> k3::tok3n::Parser;
};

template <auto... ps>
concept all_satisfy_parser = (... && k3::tok3n::Parser<decltype(ps)>);

#define IDENTITY(...) __VA_ARGS__



// Checking in a dependent context, so the error messages are still nice

#define DEP_ASSERT_MODIFIER_CALLABLE(MOD_VALUE, P_VALUES, MOD_DISPLAY, P_DISPLAYS) \
	ASSERT_CONCEPT(Modifier, decltype(MOD_VALUE));                                 \
	ASSERT((all_satisfy_parser<IDENTITY P_VALUES>),                                \
		"`" #P_VALUES "` do not all satisfy the Parser concept.");                 \
	ASSERT((callable<MOD_VALUE, IDENTITY P_VALUES>),                               \
		"`" #MOD_DISPLAY #P_DISPLAYS "` does not satisfy the Parser concept.")

#define DEP_ASSERT_MODIFIER_NOT_CALLABLE(MOD_VALUE, P_VALUES, MOD_DISPLAY, P_DISPLAYS)     \
	ASSERT_CONCEPT(Modifier, decltype(MOD_VALUE));                                         \
	ASSERT((all_satisfy_parser<IDENTITY P_VALUES>),                                \
		"`" #P_VALUES "` do not all satisfy the Parser concept.");                 \
	ASSERT((not callable<MOD_VALUE, IDENTITY P_VALUES>),                                   \
		"`" #MOD_DISPLAY #P_DISPLAYS "` satisfies the Parser concept, but it should not.")

#define DEP_ASSERT_MODIFIER_CALLABLE_R(MOD_VALUE, P_VALUES, R_VALUE, MOD_DISPLAY, P_DISPLAYS, R_DISPLAY) \
	DEP_ASSERT_MODIFIER_CALLABLE(MOD_VALUE, P_VALUES, MOD_DISPLAY, P_DISPLAYS);                          \
	ASSERT_CONCEPT(Parser, decltype(R_VALUE));                                                           \
	DEP_ASSERT_PARSER_VALUES_EQ((MOD_VALUE)P_VALUES, R_VALUE, (MOD_DISPLAY)P_DISPLAYS, R_DISPLAY)



#define DEP_ASSERT_MODIFIER_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_DISPLAY, MOD_DISPLAY)            \
	ASSERT_CONCEPT(Parser, decltype(P_VALUE));                                                     \
	ASSERT_CONCEPT(Modifier, decltype(MOD_VALUE));                                                 \
	ASSERT((modulo_operable<P_VALUE, MOD_VALUE>),                                                  \
		"`" #P_DISPLAY " % " #MOD_DISPLAY "` does not satisfy the Parser concept, but it should.")

#define DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_DISPLAY, MOD_DISPLAY)          \
	ASSERT_CONCEPT(Parser, decltype(P_VALUE));                                                       \
	ASSERT_CONCEPT(Modifier, decltype(MOD_VALUE));                                                   \
	ASSERT((not modulo_operable<P_VALUE, MOD_VALUE>),                                                \
		"`" #P_DISPLAY " % " #MOD_DISPLAY "` does satisfies the Parser concept, but it should not.")

#define DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(P_VALUE, MOD_VALUE, R_VALUE, P_DISPLAY, MOD_DISPLAY, R_DISPLAY) \
	DEP_ASSERT_MODIFIER_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_DISPLAY, MOD_DISPLAY);                          \
	ASSERT_CONCEPT(Parser, decltype(R_VALUE));                                                                \
	DEP_ASSERT_PARSER_VALUES_EQ((P_VALUE) % (MOD_VALUE), R_VALUE, (P_DISPLAY) % (MOD_DISPLAY), R_DISPLAY)



// Checking in a context where dependent types are not required

#define ASSERT_MODIFIER_CALLABLE(MOD_VALUE, P_VALUES) \
	DEP_ASSERT_MODIFIER_CALLABLE(MOD_VALUE, P_VALUES, MOD_VALUE, P_VALUES)

#define ASSERT_MODIFIER_NOT_CALLABLE(MOD_VALUE, P_VALUES) \
	DEP_ASSERT_MODIFIER_NOT_CALLABLE(MOD_VALUE, P_VALUES, MOD_VALUE, P_VALUES)

#define ASSERT_MODIFIER_CALLABLE_R(MOD_VALUE, P_VALUES, R_VALUE) \
	DEP_ASSERT_MODIFIER_CALLABLE_R(MOD_VALUE, P_VALUES, R_VALUE, MOD_VALUE, P_VALUES, R_VALUE)



#define ASSERT_MODIFIER_MODULO_OPERABLE(P_VALUE, MOD_VALUE) \
	DEP_ASSERT_MODIFIER_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_VALUE, MOD_VALUE)

#define ASSERT_MODIFIER_MODULO_OPERABLE_R(P_VALUE, MOD_VALUE, R_VALUE) \
	DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(P_VALUE, MOD_VALUE, R_VALUE, P_VALUE, MOD_VALUE, R_VALUE)

#define ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P_VALUE, MOD_VALUE) \
	DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_VALUE, MOD_VALUE)
