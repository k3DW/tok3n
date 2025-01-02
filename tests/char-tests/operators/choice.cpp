// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("choice operator");

TEST("choice operator", "any_of_parser | any_of_parser")
{
	ASSERT_PARSER_VALUES_EQ(any1 | any2, any2 | any1);
	ASSERT_PARSER_VALUES_EQ(any1 | any3, any3 | any1);
	ASSERT_PARSER_VALUES_EQ(any2 | any3, any3 | any2);
	ASSERT_PARSER_VALUES_EQ(any1 | any2, any_of_parser<TT("abcd")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | any3, any_of_parser<TT("abcxyz")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | any3, any_of_parser<TT("bcdxyz")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | any1, any1);
	ASSERT_PARSER_VALUES_EQ(any2 | any2, any2);
	ASSERT_PARSER_VALUES_EQ(any3 | any3, any3);
}

TEST("choice operator", "none_of_parser | none_of_parser")
{
	ASSERT_PARSER_VALUES_EQ(none1 | none2, none2 | none1);
	ASSERT_PARSER_VALUES_EQ(none1 | none3, none3 | none1);
	ASSERT_PARSER_VALUES_EQ(none2 | none3, none3 | none2);
	ASSERT_PARSER_VALUES_EQ(none1 | none2, none_of_parser<TT("bc")>{});
	ASSERT_PARSER_VALUES_EQ(none1 | none3, none_of_parser<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(none2 | none3, none_of_parser<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(none1 | none1, none1);
	ASSERT_PARSER_VALUES_EQ(none2 | none2, none2);
	ASSERT_PARSER_VALUES_EQ(none3 | none3, none3);
}

TEST("choice operator", "any_of_parser | none_of_parser, and none_of_parser | any_of_parser")
{
	ASSERT_PARSER_VALUES_EQ(any1 | none1, none1 | any1);
	ASSERT_PARSER_VALUES_EQ(any1 | none2, none2 | any1);
	ASSERT_PARSER_VALUES_EQ(any1 | none3, none3 | any1);
	ASSERT_PARSER_VALUES_EQ(any2 | none1, none1 | any2);
	ASSERT_PARSER_VALUES_EQ(any2 | none2, none2 | any2);
	ASSERT_PARSER_VALUES_EQ(any2 | none3, none3 | any2);
	ASSERT_PARSER_VALUES_EQ(any3 | none1, none1 | any3);
	ASSERT_PARSER_VALUES_EQ(any3 | none2, none2 | any3);
	ASSERT_PARSER_VALUES_EQ(any3 | none3, none3 | any3);
	ASSERT_PARSER_VALUES_EQ(any1 | none1, none_of_parser<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | none2, none_of_parser<TT("d")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | none3, none_of_parser<TT("xyz")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | none1, none_of_parser<TT("a")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | none2, none_of_parser<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | none3, none_of_parser<TT("xyz")>{});
	ASSERT_PARSER_VALUES_EQ(any3 | none1, none_of_parser<TT("abc")>{});
	ASSERT_PARSER_VALUES_EQ(any3 | none2, none_of_parser<TT("bcd")>{});
	ASSERT_PARSER_VALUES_EQ(any3 | none3, none_of_parser<TT("")>{});
}



TEST("choice operator", "choice_parser | choice_parser")
{
	ASSERT_PARSER_VALUES_EQ(cho1 | cho1, cho1);
	ASSERT_PARSER_VALUES_EQ(cho2 | cho2, cho2);
	ASSERT_PARSER_VALUES_EQ(cho3 | cho3, cho3);
	ASSERT_PARSER_VALUES_EQ(cho4 | cho4, cho4);
	ASSERT_PARSER_VALUES_EQ(cho1 | cho2, (choice_parser<All4, Non4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho1, (choice_parser<Non4, All4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho1 | cho3, (choice_parser<All4, Non4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho1, (choice_parser<All4, Any4, Non5, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho1 | cho4, (choice_parser<All4, Non4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho1, (choice_parser<Non5, All4, Any4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho3, (choice_parser<Non4, All4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho2, (choice_parser<All4, Any4, Non5, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho4, (choice_parser<Non4, All4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho2, (choice_parser<Non5, All4, Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho4, (choice_parser<All4, Any4, Non5, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho3, (choice_parser<Non5, All4, Any4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho5 | cho5, cho5);
}

TEST("choice operator", "choice_parser | {anything}, and {anything} | choice_parser")
{
	ASSERT_PARSER_VALUES_EQ(cho1 | any1, (choice_parser<All4, Non4, Any1>{}));
	ASSERT_PARSER_VALUES_EQ(any1 | cho1, (choice_parser<Any1, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | any4, (choice_parser<Non4, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(any4 | cho2, (choice_parser<Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | any3, (choice_parser<All4, Any4, Non5, Any3>{}));
	ASSERT_PARSER_VALUES_EQ(any3 | cho3, (choice_parser<Any3, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | any2, (choice_parser<Non5, All4, Any4, Any2>{}));
	ASSERT_PARSER_VALUES_EQ(any2 | cho4, (choice_parser<Any2, Non5, All4, Any4>{}));
}

TEST("choice operator", "void result_type")
{
	ASSERT_PARSER_VALUES_EQ(ign1 | ign2, cho5);
	ASSERT_PARSER_VALUES_NE(ign2 | ign1, cho5);
}

TEST("choice operator", "non consteval")
{
	(any1 | any2).parse(TT("abc"));
}



#define CHOICE_OPERATOR_ASSERTER(LHS, RHS)                                                           \
	[]<parser LLHS, parser RRHS>(LLHS, RRHS) {                                                       \
		if constexpr (not std::same_as<typename LLHS::value_type, typename RRHS::value_type>)        \
		{                                                                                            \
			DEP_ASSERT_BINARY_NOT_OPERABLE(|, LLHS{}, RRHS{}, LHS{}, RHS{});                         \
		}                                                                                            \
		else                                                                                         \
		{                                                                                            \
			DEP_ASSERT_BINARY_OPERABLE(|, LLHS{}, RRHS{}, LHS{}, RHS{});                             \
			if constexpr (std::same_as<LLHS, RRHS>)                                                  \
			{                                                                                        \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, LLHS{},                                 \
					                        LHS{}  | RHS{},  LHS{});                                 \
			}                                                                                        \
			else if constexpr (LLHS::family == any_of_family and RRHS::family == any_of_family)      \
			{                                                                                        \
				constexpr auto str = set_union<underlying_v<LLHS>, underlying_v<RRHS>>();            \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, any_of_parser<str>{},                   \
					                        LHS{}  | RHS{},  any_of_parser<str>{});                  \
			}                                                                                        \
			else if constexpr (LLHS::family == none_of_family and RRHS::family == none_of_family)    \
			{                                                                                        \
				constexpr auto str = set_intersection<underlying_v<LLHS>, underlying_v<RRHS>>();     \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, none_of_parser<str>{},                  \
					                        LHS{}  | RHS{},  none_of_parser<str>{});                 \
			}                                                                                        \
			else if constexpr (LLHS::family == none_of_family and RRHS::family == any_of_family)     \
			{                                                                                        \
				constexpr auto str = set_difference_left<underlying_v<LLHS>, underlying_v<RRHS>>();  \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, none_of_parser<str>{},                  \
					                        LHS{}  | RHS{},  none_of_parser<str>{});                 \
			}                                                                                        \
			else if constexpr (LLHS::family == any_of_family and RRHS::family == none_of_family)     \
			{                                                                                        \
				constexpr auto str = set_difference_right<underlying_v<LLHS>, underlying_v<RRHS>>(); \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, none_of_parser<str>{},                  \
					                        LHS{}  | RHS{},  none_of_parser<str>{});                 \
			}                                                                                        \
			else if constexpr (LLHS::family == choice_family and RRHS::family != choice_family)      \
			{                                                                                        \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, choice_combined_left(LLHS{}, RRHS{}),   \
					                        LHS{}  | RHS{},  choice_combined_left(LHS{},  RHS{}));   \
			}                                                                                        \
			else if constexpr (LLHS::family != choice_family and RRHS::family == choice_family)      \
			{                                                                                        \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, choice_combined_right(LLHS{}, RRHS{}),  \
					                        LHS{}  | RHS{},  choice_combined_right(LHS{},  RHS{}));  \
			}                                                                                        \
			else if constexpr (LLHS::family == choice_family and RRHS::family == choice_family)      \
			{                                                                                        \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, choice_combined_both(LLHS{}, RRHS{}),   \
					                        LHS{}  | RHS{},  choice_combined_both(LHS{},  RHS{}));   \
			}                                                                                        \
			else                                                                                     \
			{                                                                                        \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, (choice_parser<LLHS, RRHS>{}),          \
					                        LHS{}  | RHS{},  (choice_parser<LHS,  RHS>{}));          \
			}                                                                                        \
		}                                                                                            \
	}(LHS{}, RHS{});

#define CHOICE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
	(any_of_parser<"abc">) (any_of_parser<"xyz">) (any_of_parser<L"abc">) (any_of_parser<L"xyz">)

TEST("choice operator", "{anything} | {anything}")
{
	// Note that all the operations are reimplemented for choice_checker. This is intentional. That way, there's redundancy in the code.
	// A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.

	// This works just fine, but it takes forever and may crash your computer. User beware.
	// ASSERT_ALL_SAMPLES_2(CHOICE_OPERATOR_ASSERTER);

	ASSERT_SAMPLES_2(CHOICE_OPERATOR_ASSERTER, CHOICE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES, CHOICE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES);

	ASSERT_SAMPLES_2(CHOICE_OPERATOR_ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES);
}
