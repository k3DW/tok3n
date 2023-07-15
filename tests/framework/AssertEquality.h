#pragma once

#define ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                                 \
	do {                                                                              \
		ASSERT_CONCEPT_PARSER(decltype(LHS_VALUE));                                   \
		ASSERT_CONCEPT_PARSER(decltype(RHS_VALUE));                                   \
		ASSERT((std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,                \
				std::remove_cvref_t<decltype(RHS_VALUE)>>),                           \
			"(" #LHS_VALUE ") and (" #RHS_VALUE ") are not the same, but should be"); \
	} while(false)

#define ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE)                                 \
	do {                                                                              \
		ASSERT_CONCEPT_PARSER(decltype(LHS_VALUE));                                   \
		ASSERT_CONCEPT_PARSER(decltype(RHS_VALUE));                                   \
		ASSERT((not std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,            \
				std::remove_cvref_t<decltype(RHS_VALUE)>>),                           \
			"(" #LHS_VALUE ") and (" #RHS_VALUE ") are the same, but should not be"); \
	} while(false)

#define ASSERT_MODIFIER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                               \
	do {                                                                              \
		ASSERT_CONCEPT_MODIFIER(decltype(LHS_VALUE));                                 \
		ASSERT_CONCEPT_MODIFIER(decltype(RHS_VALUE));                                 \
		ASSERT((std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,                \
				std::remove_cvref_t<decltype(RHS_VALUE)>>),                           \
			"(" #LHS_VALUE ") and (" #RHS_VALUE ") are not the same, but should be"); \
	} while(false)

#define ASSERT_MODIFIER_VALUES_NE(LHS_VALUE, RHS_VALUE)                               \
	do {                                                                              \
		ASSERT_CONCEPT_MODIFIER(decltype(LHS_VALUE));                                 \
		ASSERT_CONCEPT_MODIFIER(decltype(RHS_VALUE));                                 \
		ASSERT((not std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,            \
				std::remove_cvref_t<decltype(RHS_VALUE)>>),                           \
			"(" #LHS_VALUE ") and (" #RHS_VALUE ") are the same, but should not be"); \
	} while(false)
