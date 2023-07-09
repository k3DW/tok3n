#pragma once

using namespace k3::tok3n;

struct assert_t final {};

consteval assert_t operator,(assert_t self, bool b)
{
	if (!b)
		throw;
	return self;
}

constexpr auto assert = assert_t{};



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



#define ASSERT_PARSER_CONCEPT(P)                         \
	ASSERT(Parser<P>,                                    \
		"(" #P ") does not satisfy the Parser concept.")

#define ASSERT_MODIFIER_CONCEPT(M)                         \
	ASSERT(Modifier<M>,                                    \
		"(" #M ") does not satisfy the Modifier concept.")

#define ASSERT_IS_PARSER(P, PARSER_TYPE, ...)                                         \
	do {                                                                              \
		ASSERT_PARSER_CONCEPT(P);                                                     \
		ASSERT(P::type == PARSER_TYPE,                                                \
			"(" #P "::type) does not equal " #PARSER_TYPE);                           \
		ASSERT((std::same_as<typename P::result_type, __VA_ARGS__>),                  \
			"(" #P "::result_type) is not " #__VA_ARGS__);                            \
		ASSERT((IsParser<P, PARSER_TYPE, __VA_ARGS__>),                               \
			"IsParser<" #P ", " #PARSER_TYPE ", " #__VA_ARGS__ "> is not satisfied"); \
	} while(false)



#define ASSERT_PARSER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                                 \
	do {                                                                              \
		ASSERT_PARSER_CONCEPT(decltype(LHS_VALUE));                                   \
		ASSERT_PARSER_CONCEPT(decltype(RHS_VALUE));                                   \
		ASSERT((std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,                \
				std::remove_cvref_t<decltype(RHS_VALUE)>>),                           \
			"(" #LHS_VALUE ") and (" #RHS_VALUE ") are not the same, but should be"); \
	} while(false)

#define ASSERT_PARSER_VALUES_NE(LHS_VALUE, RHS_VALUE)                                 \
	do {                                                                              \
		ASSERT_PARSER_CONCEPT(decltype(LHS_VALUE));                                   \
		ASSERT_PARSER_CONCEPT(decltype(RHS_VALUE));                                   \
		ASSERT((not std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,            \
				std::remove_cvref_t<decltype(RHS_VALUE)>>),                           \
			"(" #LHS_VALUE ") and (" #RHS_VALUE ") are the same, but should not be"); \
	} while(false)

#define ASSERT_MODIFIER_VALUES_EQ(LHS_VALUE, RHS_VALUE)                               \
	do {                                                                              \
		ASSERT_MODIFIER_CONCEPT(decltype(LHS_VALUE));                                 \
		ASSERT_MODIFIER_CONCEPT(decltype(RHS_VALUE));                                 \
		ASSERT((std::same_as<std::remove_cvref_t<decltype(LHS_VALUE)>,                \
				std::remove_cvref_t<decltype(RHS_VALUE)>>),                           \
			"(" #LHS_VALUE ") and (" #RHS_VALUE ") are not the same, but should be"); \
	} while(false)

#define ASSERT_MODIFIER_VALUES_NE(LHS_VALUE, RHS_VALUE)                               \
	do {                                                                              \
		ASSERT_MODIFIER_CONCEPT(decltype(LHS_VALUE));                                 \
		ASSERT_MODIFIER_CONCEPT(decltype(RHS_VALUE));                                 \
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
		ASSERT_MODIFIER_CONCEPT(decltype(MOD));                                   \
		ASSERT_PARSER_CONCEPT(decltype(P1));                                      \
		ASSERT_PARSER_CONCEPT(decltype(P2));                                      \
		ASSERT((callable<decltype(MOD), decltype(P1), decltype(P2)>),             \
			"(" #MOD "(" #P1 ", " #P2 ")) does not satisfy the Parser concept."); \
	} while(false)

#define ASSERT_MODIFIER_NOT_CALLABLE_2(MOD, P1, P2)                                           \
	do {                                                                                      \
		ASSERT_MODIFIER_CONCEPT(decltype(MOD));                                               \
		ASSERT_PARSER_CONCEPT(decltype(P1));                                                  \
		ASSERT_PARSER_CONCEPT(decltype(P2));                                                  \
		ASSERT((not callable<decltype(MOD), decltype(P1), decltype(P2)>),                     \
			"(" #MOD "(" #P1 ", " #P2 ")) satisfies the Parser concept, but it should not."); \
	} while(false)

#define ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P, MOD)                                       \
	do {                                                                                  \
		ASSERT_PARSER_CONCEPT(decltype(P));                                               \
		ASSERT_MODIFIER_CONCEPT(decltype(MOD));                                           \
		ASSERT((not modulo_operable<decltype(P), decltype(MOD)>),                         \
			"(" #P " % " #MOD ") does satisfies the Parser concept, but it should not."); \
	} while(false)



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
