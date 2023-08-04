#pragma once
#include "framework/Assert.h"
#include "asserts/Concept.h"

// Equality checking in a dependent context, so the error messags are still nice
#define ASSERT_PARSER_VALUES_DEP_EQ(LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)  \
	ASSERT_CONCEPT_PARSER(decltype(LHS_VALUE));                                      \
	ASSERT_CONCEPT_PARSER(decltype(RHS_VALUE));                                      \
	ASSERT((std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,                   \
			std::remove_cvref_t<decltype(RHS_VALUE)>>),                              \
		"(" #LHS_DISPLAY ") and (" #RHS_DISPLAY ") are not the same, but should be")

#define ASSERT_PARSER_VALUES_DEP_NE(LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)  \
	ASSERT_CONCEPT_PARSER(decltype(LHS_VALUE));                                      \
	ASSERT_CONCEPT_PARSER(decltype(RHS_VALUE));                                      \
	ASSERT((not std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,               \
			std::remove_cvref_t<decltype(RHS_VALUE)>>),                              \
		"(" #LHS_DISPLAY ") and (" #RHS_DISPLAY ") are the same, but should not be")

// Equality checking
#define ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                       \
	ASSERT_PARSER_VALUES_DEP_EQ(LHS_VALUE, RHS_VALUE, LHS_VALUE, RHS_VALUE)

#define ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE)                       \
	ASSERT_PARSER_VALUES_DEP_NE(LHS_VALUE, RHS_VALUE, LHS_VALUE, RHS_VALUE)

#define ASSERT_MODIFIER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                          \
	ASSERT_CONCEPT_MODIFIER(decltype(LHS_VALUE));                                \
	ASSERT_CONCEPT_MODIFIER(decltype(RHS_VALUE));                                \
	ASSERT((std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,               \
			std::remove_cvref_t<decltype(RHS_VALUE)>>),                          \
		"(" #LHS_VALUE ") and (" #RHS_VALUE ") are not the same, but should be")

#define ASSERT_MODIFIER_VALUES_NE(LHS_VALUE, RHS_VALUE)                          \
	ASSERT_CONCEPT_MODIFIER(decltype(LHS_VALUE));                                \
	ASSERT_CONCEPT_MODIFIER(decltype(RHS_VALUE));                                \
	ASSERT((not std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,           \
			std::remove_cvref_t<decltype(RHS_VALUE)>>),                          \
		"(" #LHS_VALUE ") and (" #RHS_VALUE ") are the same, but should not be")
