#pragma once
#include "framework/Assert.h"
#include "asserts/Concept.h"
#include <k3/tok3n/concepts/Parser.h>

template <class F, class... Args>
concept callable = requires(F&& f, Args&&... args) {
	{ static_cast<F&&>(f)(static_cast<Args&&>(args)...) } -> k3::tok3n::Parser;
}; // Adapted from the MSVC STL's std::invocable

template <class LHS, class RHS>
concept modulo_operable = requires(LHS&& lhs, RHS&& rhs) {
	{ static_cast<LHS&&>(lhs) % static_cast<RHS&&>(rhs) } -> k3::tok3n::Parser;
};

#define ASSERT_MODIFIER_CALLABLE_2(MOD, P1, P2)                              \
	ASSERT_CONCEPT_MODIFIER(decltype(MOD));                                  \
	ASSERT_CONCEPT_PARSER(decltype(P1));                                     \
	ASSERT_CONCEPT_PARSER(decltype(P2));                                     \
	ASSERT((callable<decltype(MOD), decltype(P1), decltype(P2)>),            \
		"(" #MOD "(" #P1 ", " #P2 ")) does not satisfy the Parser concept.")

#define ASSERT_MODIFIER_NOT_CALLABLE_2(MOD, P1, P2)                                      \
	ASSERT_CONCEPT_MODIFIER(decltype(MOD));                                              \
	ASSERT_CONCEPT_PARSER(decltype(P1));                                                 \
	ASSERT_CONCEPT_PARSER(decltype(P2));                                                 \
	ASSERT((not callable<decltype(MOD), decltype(P1), decltype(P2)>),                    \
		"(" #MOD "(" #P1 ", " #P2 ")) satisfies the Parser concept, but it should not.")


#define ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P, MOD)                                  \
	ASSERT_CONCEPT_PARSER(decltype(P));                                              \
	ASSERT_CONCEPT_MODIFIER(decltype(MOD));                                          \
	ASSERT((not modulo_operable<decltype(P), decltype(MOD)>),                        \
		"(" #P " % " #MOD ") does satisfies the Parser concept, but it should not.")
