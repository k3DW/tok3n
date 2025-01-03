// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_ASSERTS_OPERATION_HPP
#define K3_TOK3N_TESTS_COMMON_ASSERTS_OPERATION_HPP

#include "framework/Assert.hpp"
#include "common/asserts/Concept.hpp"
#include "common/asserts/Equality.hpp"
#include <k3/tok3n/detail/parser.hpp>

template <auto f, auto... args>
concept callable = requires {
	{ f(args...) } -> k3::tok3n::detail::parser;
};

template <auto lhs, auto rhs>
concept modulo_operable = requires {
	{ lhs % rhs } -> k3::tok3n::detail::parser;
};

template <auto... ps>
concept all_satisfy_parser = (... && k3::tok3n::detail::parser<decltype(ps)>);



// Checking in a dependent context, so the error messages are still nice
// This wouldn't be needed if we had CWG2518 or P2593

#define DEP_ASSERT_MODIFIER_CALLABLE(MOD_VALUE, P_VALUES, MOD_DISPLAY, P_DISPLAYS)     \
	ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(MOD_VALUE));                  \
	ASSERT((all_satisfy_parser<IDENTITY P_VALUES>),                                    \
		"`" STR(P_VALUES) "` do not all satisfy the parser concept.");                 \
	ASSERT((callable<MOD_VALUE, IDENTITY P_VALUES>),                                   \
		"`" STR(MOD_DISPLAY) STR(P_DISPLAYS) "` does not satisfy the Parser concept.")

#define DEP_ASSERT_MODIFIER_NOT_CALLABLE(MOD_VALUE, P_VALUES, MOD_DISPLAY, P_DISPLAYS)             \
	ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(MOD_VALUE));                              \
	ASSERT((all_satisfy_parser<IDENTITY P_VALUES>),                                                \
		"`" STR(P_VALUES) "` do not all satisfy the parser concept.");                             \
	ASSERT((not callable<MOD_VALUE, IDENTITY P_VALUES>),                                           \
		"`" STR(MOD_DISPLAY) STR(P_DISPLAYS) "` satisfies the Parser concept, but it should not.")

#define DEP_ASSERT_MODIFIER_CALLABLE_R(MOD_VALUE, P_VALUES, R_VALUE, MOD_DISPLAY, P_DISPLAYS, R_DISPLAY)  \
	DEP_ASSERT_MODIFIER_CALLABLE(MOD_VALUE, P_VALUES, MOD_DISPLAY, P_DISPLAYS);                           \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(R_VALUE));                                         \
	DEP_ASSERT_PARSER_VALUES_EQ(MOD_VALUE P_VALUES, R_VALUE, MOD_DISPLAY P_DISPLAYS, R_DISPLAY)



#define DEP_ASSERT_MODIFIER_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_DISPLAY, MOD_DISPLAY)                    \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(P_VALUE));                                          \
	ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(MOD_VALUE));                                      \
	ASSERT((modulo_operable<P_VALUE, MOD_VALUE>),                                                          \
		"`" STR(P_DISPLAY) " % " STR(MOD_DISPLAY) "` does not satisfy the Parser concept, but it should.")

#define DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_DISPLAY, MOD_DISPLAY)                  \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(P_VALUE));                                            \
	ASSERT_CONCEPT(k3::tok3n::detail::modifier, decltype(MOD_VALUE));                                        \
	ASSERT((not modulo_operable<P_VALUE, MOD_VALUE>),                                                        \
		"`" STR(P_DISPLAY) " % " STR(MOD_DISPLAY) "` does satisfies the Parser concept, but it should not.")

#define DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(P_VALUE, MOD_VALUE, R_VALUE, P_DISPLAY, MOD_DISPLAY, R_DISPLAY) \
	DEP_ASSERT_MODIFIER_MODULO_OPERABLE(P_VALUE, MOD_VALUE, P_DISPLAY, MOD_DISPLAY);                          \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(R_VALUE));                                             \
	DEP_ASSERT_PARSER_VALUES_EQ(P_VALUE % MOD_VALUE, R_VALUE, P_DISPLAY % MOD_DISPLAY, R_DISPLAY)



#define DEP_ASSERT_UNARY_OPERABLE(OPERATOR, P_VALUE, P_DISPLAY)                                                        \
	ASSERT((requires { OPERATOR (P_VALUE); }), "`" STR(OPERATOR) STR(P_DISPLAY) "` does not compile, but it should."); \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(OPERATOR P_VALUE))

#define DEP_ASSERT_UNARY_NOT_OPERABLE(OPERATOR, P_VALUE, P_DISPLAY) \
	ASSERT((not requires { OPERATOR (P_VALUE); }), "`" STR(OPERATOR) STR(P_DISPLAY) "` compiles, but it should not.")

#define DEP_ASSERT_BINARY_OPERABLE(OPERATOR, LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)               \
	ASSERT((requires { (LHS_VALUE) OPERATOR (RHS_VALUE); }),                                               \
		"`" STR(LHS_DISPLAY) " " STR(OPERATOR) " " STR(RHS_DISPLAY) "` does not compile, but it should."); \
	ASSERT_CONCEPT(k3::tok3n::detail::parser, decltype(LHS_VALUE OPERATOR RHS_VALUE))

#define DEP_ASSERT_BINARY_NOT_OPERABLE(OPERATOR, LHS_VALUE, RHS_VALUE, LHS_DISPLAY, RHS_DISPLAY)      \
	ASSERT((not requires { (LHS_VALUE) OPERATOR (RHS_VALUE); }),                                      \
		"`" STR(LHS_DISPLAY) " " STR(OPERATOR) " " STR(RHS_DISPLAY) "` compiles, but it should not.")



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

#endif // K3_TOK3N_TESTS_COMMON_ASSERTS_OPERATION_HPP
