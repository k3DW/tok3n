#pragma once
#include "framework/Assert.h"
#include "asserts/Concept.h"
#include "asserts/Equality.h"
#include <k3/tok3n/concepts/Parser.h>

template <class F, class... Args>
concept callable = requires(F&& f, Args&&... args) {
	{ static_cast<F&&>(f)(static_cast<Args&&>(args)...) } -> k3::tok3n::Parser;
}; // Adapted from the MSVC STL's std::invocable

template <class LHS, class RHS>
concept modulo_operable = requires(LHS&& lhs, RHS&& rhs) {
	{ static_cast<LHS&&>(lhs) % static_cast<RHS&&>(rhs) } -> k3::tok3n::Parser;
};



#define ASSERT_MODIFIER_CALLABLE_DEP_1(MOD, P, MOD_DISPLAY, P_DISPLAY)             \
	ASSERT_CONCEPT(Modifier, decltype(MOD));                                       \
	ASSERT_CONCEPT(Parser, decltype(P));                                           \
	ASSERT((callable<decltype(MOD), decltype(P)>),                                 \
		"(" #MOD_DISPLAY "(" #P_DISPLAY ")) does not satisfy the Parser concept.")

#define ASSERT_MODIFIER_CALLABLE_DEP_1_R(MOD, P, R, MOD_DISPLAY, P_DISPLAY, R_DISPLAY) \
	ASSERT_MODIFIER_CALLABLE_DEP_1(MOD, P, MOD_DISPLAY, P_DISPLAY);                    \
	ASSERT_CONCEPT(Parser, decltype(R));                                               \
	DEP_ASSERT_PARSER_VALUES_EQ((MOD)(P), R, (MOD_DISPLAY)(P_DISPLAY), R_DISPLAY)

#define ASSERT_MODIFIER_CALLABLE_1(MOD, P)         \
	ASSERT_MODIFIER_CALLABLE_DEP_1(MOD, P, MOD, P)

#define ASSERT_MODIFIER_CALLABLE_1_R(MOD, P, R)            \
	ASSERT_MODIFIER_CALLABLE_DEP_1_R(MOD, P, R, MOD, P, R)

#define ASSERT_MODIFIER_NOT_CALLABLE_1(MOD, P)                                 \
	ASSERT_CONCEPT(Modifier, decltype(MOD));                                   \
	ASSERT_CONCEPT(Parser, decltype(P));                                       \
	ASSERT((not callable<decltype(MOD), decltype(P)>),                         \
		"(" #MOD "(" #P ")) satisfies the Parser concept, but it should not.")



#define ASSERT_MODIFIER_CALLABLE_2(MOD, P1, P2)                              \
	ASSERT_CONCEPT(Modifier, decltype(MOD));                                 \
	ASSERT_CONCEPT(Parser, decltype(P1));                                    \
	ASSERT_CONCEPT(Parser, decltype(P2));                                    \
	ASSERT((callable<decltype(MOD), decltype(P1), decltype(P2)>),            \
		"(" #MOD "(" #P1 ", " #P2 ")) does not satisfy the Parser concept.")

#define ASSERT_MODIFIER_NOT_CALLABLE_2(MOD, P1, P2)                                      \
	ASSERT_CONCEPT(Modifier, decltype(MOD));                                             \
	ASSERT_CONCEPT(Parser, decltype(P1));                                                \
	ASSERT_CONCEPT(Parser, decltype(P2));                                                \
	ASSERT((not callable<decltype(MOD), decltype(P1), decltype(P2)>),                    \
		"(" #MOD "(" #P1 ", " #P2 ")) satisfies the Parser concept, but it should not.")



#define ASSERT_MODIFIER_MODULO_OPERABLE_DEP(P, MOD, P_DISPLAY, MOD_DISPLAY)                        \
	ASSERT_CONCEPT(Parser, decltype(P));                                                           \
	ASSERT_CONCEPT(Modifier, decltype(MOD));                                                       \
	ASSERT((modulo_operable<decltype(P), decltype(MOD)>),                                          \
		"(" #P_DISPLAY " % " #MOD_DISPLAY ") does not satisfy the Parser concept, but it should.")

#define ASSERT_MODIFIER_MODULO_OPERABLE_DEP_R(P, MOD, R, P_DISPLAY, MOD_DISPLAY, R_DISPLAY) \
	ASSERT_MODIFIER_MODULO_OPERABLE_DEP(P, MOD, P_DISPLAY, MOD_DISPLAY);                    \
	ASSERT_CONCEPT(Parser, decltype(R));                                                    \
	DEP_ASSERT_PARSER_VALUES_EQ((P) % (MOD), R, (P_DISPLAY) % (MOD_DISPLAY), R_DISPLAY)

#define ASSERT_MODIFIER_MODULO_OPERABLE(P, MOD)         \
	ASSERT_MODIFIER_MODULO_OPERABLE_DEP(P, MOD, P, MOD)

#define ASSERT_MODIFIER_MODULO_OPERABLE_R(P, MOD, R)            \
	ASSERT_MODIFIER_MODULO_OPERABLE_DEP_R(P, MOD, R, P, MOD, R)

#define ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P, MOD)                                  \
	ASSERT_CONCEPT(Parser, decltype(P));                                             \
	ASSERT_CONCEPT(Modifier, decltype(MOD));                                         \
	ASSERT((not modulo_operable<decltype(P), decltype(MOD)>),                        \
		"(" #P " % " #MOD ") does satisfies the Parser concept, but it should not.")
