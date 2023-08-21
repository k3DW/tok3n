#pragma once
#include "framework/Assert.h"
#include "asserts/Concept.h"

template <auto lhs, auto rhs>
concept same_values = std::same_as<std::remove_cvref_t<decltype(lhs)>, std::remove_cvref_t<decltype(rhs)>>;



// Checking in a dependent context, so the error messages are still nice

#define DEP_ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)  \
	ASSERT_CONCEPT(Parser, decltype(LHS_VALUE));                                     \
	ASSERT_CONCEPT(Parser, decltype(RHS_VALUE));                                     \
	ASSERT((same_values<(LHS_VALUE), (RHS_VALUE)>),                                  \
		"`" #LHS_DISPLAY "` and `" #RHS_DISPLAY "` are not the same, but should be")

#define DEP_ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)  \
	ASSERT_CONCEPT(Parser, decltype(LHS_VALUE));                                     \
	ASSERT_CONCEPT(Parser, decltype(RHS_VALUE));                                     \
	ASSERT((not same_values<(LHS_VALUE), (RHS_VALUE)>),                              \
		"`" #LHS_DISPLAY "` and `" #RHS_DISPLAY "` are the same, but should not be")



// Checking in a context where dependent types are not required

#define ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE) \
	DEP_ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE, LHS_VALUE, RHS_VALUE)

#define ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE) \
	DEP_ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE, LHS_VALUE, RHS_VALUE)

#define ASSERT_MODIFIER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                          \
	ASSERT_CONCEPT(Modifier, decltype(LHS_VALUE));                               \
	ASSERT_CONCEPT(Modifier, decltype(RHS_VALUE));                               \
	ASSERT((same_values<(LHS_VALUE), (RHS_VALUE)>),                              \
		"`" #LHS_VALUE "` and `" #RHS_VALUE "` are not the same, but should be")

#define ASSERT_MODIFIER_VALUES_NE(LHS_VALUE, RHS_VALUE)                          \
	ASSERT_CONCEPT(Modifier, decltype(LHS_VALUE));                               \
	ASSERT_CONCEPT(Modifier, decltype(RHS_VALUE));                               \
	ASSERT((not same_values<(LHS_VALUE), (RHS_VALUE)>),                          \
		"`" #LHS_VALUE "` and `" #RHS_VALUE "` are the same, but should not be")
