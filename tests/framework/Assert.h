#pragma once

using namespace k3::tok3n;

// #define DISABLE_STATIC_ASSERT

#ifdef DISABLE_STATIC_ASSERT
#define STATIC_ASSERT(...)
#else
#define STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#endif

#define ASSERT(CONDITION, MESSAGE)             \
	[&]() -> bool {                            \
		STATIC_ASSERT((CONDITION), MESSAGE);   \
		return Assert((CONDITION), (MESSAGE)); \
	}()



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



template <class F, class... Args>
concept callable = requires(F&& f, Args&&... args) {
	{ static_cast<F&&>(f)(static_cast<Args&&>(args)...) } -> Parser;
}; // Adapted from the MSVC STL's std::invocable

template <class LHS, class RHS>
concept modulo_operable = requires(LHS&& lhs, RHS&& rhs) {
	{ static_cast<LHS&&>(lhs) % static_cast<RHS&&>(rhs) } -> Parser;
};

#define ASSERT_MODIFIER_CALLABLE_2(MOD, P1, P2)                                   \
	do {                                                                          \
		ASSERT_CONCEPT_MODIFIER(decltype(MOD));                                   \
		ASSERT_CONCEPT_PARSER(decltype(P1));                                      \
		ASSERT_CONCEPT_PARSER(decltype(P2));                                      \
		ASSERT((callable<decltype(MOD), decltype(P1), decltype(P2)>),             \
			"(" #MOD "(" #P1 ", " #P2 ")) does not satisfy the Parser concept."); \
	} while(false)

#define ASSERT_MODIFIER_NOT_CALLABLE_2(MOD, P1, P2)                                           \
	do {                                                                                      \
		ASSERT_CONCEPT_MODIFIER(decltype(MOD));                                               \
		ASSERT_CONCEPT_PARSER(decltype(P1));                                                  \
		ASSERT_CONCEPT_PARSER(decltype(P2));                                                  \
		ASSERT((not callable<decltype(MOD), decltype(P1), decltype(P2)>),                     \
			"(" #MOD "(" #P1 ", " #P2 ")) satisfies the Parser concept, but it should not."); \
	} while(false)

#define ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P, MOD)                                       \
	do {                                                                                  \
		ASSERT_CONCEPT_PARSER(decltype(P));                                               \
		ASSERT_CONCEPT_MODIFIER(decltype(MOD));                                           \
		ASSERT((not modulo_operable<decltype(P), decltype(MOD)>),                         \
			"(" #P " % " #MOD ") does satisfies the Parser concept, but it should not."); \
	} while(false)



template <template <class...> class ParserFamily, class... Args>
concept constructible_from = requires { typename ParserFamily<Args...>; };

template <template <StaticString> class ParserFamily, StaticString str>
concept basic_constructible_from = requires { typename ParserFamily<str>; };

#define ASSERT_PARSER_CONSTRUCTIBLE(FAMILY, ...) \
	ASSERT((constructible_from<FAMILY __VA_OPT__(,) __VA_ARGS__>), "A " #FAMILY " parser should be constructible from " #__VA_ARGS__)

#define ASSERT_PARSER_NOT_CONSTRUCTIBLE(FAMILY, ...) \
	ASSERT((not constructible_from<FAMILY __VA_OPT__(,) __VA_ARGS__>), "A " #FAMILY " parser should not be constructible from " #__VA_ARGS__)

#define ASSERT_PARSER_BASIC_CONSTRUCTIBLE(FAMILY, STRING) \
	ASSERT((basic_constructible_from<FAMILY, STRING>), "A " #FAMILY " parser should be constructible from " #STRING)

#define ASSERT_PARSER_BASIC_NOT_CONSTRUCTIBLE(FAMILY, STRING) \
	ASSERT((not basic_constructible_from<FAMILY, STRING>), "A " #FAMILY " parser should not be constructible from " #STRING)



#define TOK3N_ASSERT_P(condition, message) \
	do {                                   \
		if constexpr (not (condition))     \
			typename P::__error_with_type; \
	} while(false)

#define TOK3N_ASSERT_P2(condition, message)      \
	do {                                         \
		if constexpr (not (condition))           \
		{                                        \
			typename LHS::__error_with_type_LHS; \
			typename RHS::__error_with_type_RHS; \
		}                                        \
	} while(false)
