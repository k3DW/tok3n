// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("sequence operator");

TEST("sequence operator", "all_of_parser >> all_of_parser")
{
	ASSERT_PARSER_VALUES_EQ(all1 >> all1, all_of_parser<TT("literalliteral")>{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all2, all_of_parser<TT("literally")>{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all3, all_of_parser<TT("literaltest")>{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all1, all_of_parser<TT("lyliteral")>{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all2, all_of_parser<TT("lyly")>{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all3, all_of_parser<TT("lytest")>{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all1, all_of_parser<TT("testliteral")>{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all2, all_of_parser<TT("testly")>{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all3, all_of_parser<TT("testtest")>{});
}



TEST("sequence operator", "sequence_parser >> sequence_parser")
{
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq1, (sequence_parser<All4, Non4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq2, (sequence_parser<Non4, All4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq3, (sequence_parser<All4, Any4, Non5, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq4, (sequence_parser<Non5, All4, Any4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq5, (sequence_parser<Ign1, Ign2, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq2, (sequence_parser<All4, Non4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq1, (sequence_parser<Non4, All4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq3, (sequence_parser<All4, Non4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq1, (sequence_parser<All4, Any4, Non5, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq4, (sequence_parser<All4, Non4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq1, (sequence_parser<Non5, All4, Any4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq5, (sequence_parser<All4, Non4, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq1, (sequence_parser<Ign1, Ign2, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq3, (sequence_parser<Non4, All4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq2, (sequence_parser<All4, Any4, Non5, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq4, (sequence_parser<Non4, All4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq2, (sequence_parser<Non5, All4, Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq5, (sequence_parser<Non4, All4, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq2, (sequence_parser<Ign1, Ign2, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq4, (sequence_parser<All4, Any4, Non5, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq3, (sequence_parser<Non5, All4, Any4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq5, (sequence_parser<All4, Any4, Non5, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq3, (sequence_parser<Ign1, Ign2, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq5, (sequence_parser<Non5, All4, Any4, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq4, (sequence_parser<Ign1, Ign2, Non5, All4, Any4>{}));
}

TEST("sequence operator", "sequence_parser >> {anything}")
{
	ASSERT_PARSER_VALUES_EQ(seq1 >> any1, (sequence_parser<All4, Non4, Any1>{}));
	ASSERT_PARSER_VALUES_EQ(any1 >> seq1, (sequence_parser<Any1, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> any4, (sequence_parser<Non4, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(any4 >> seq2, (sequence_parser<Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> any3, (sequence_parser<All4, Any4, Non5, Any3>{}));
	ASSERT_PARSER_VALUES_EQ(any3 >> seq3, (sequence_parser<Any3, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> any2, (sequence_parser<Non5, All4, Any4, Any2>{}));
	ASSERT_PARSER_VALUES_EQ(any2 >> seq4, (sequence_parser<Any2, Non5, All4, Any4>{}));
}

TEST("sequence operator", "void result_type")
{
	ASSERT_PARSER_VALUES_EQ(ign1 >> ign2, seq5);
	ASSERT_PARSER_VALUES_NE(ign2 >> ign1, seq5);
}

TEST("sequence operator", "non consteval")
{
	(any1 >> any2).parse(TT("abc"));
}



namespace {

template <static_array lhs, static_array rhs>
requires decltype(like_static_arrays(lhs, rhs))::value
constexpr auto combine_strings = []
{
	auto str = lhs.template create_empty_with_size<lhs.size() + rhs.size()>();
	auto it = str.begin();
	for (auto c : lhs)
		*it++ = c;
	for (auto c : rhs)
		*it++ = c;

	return str;
}();

template <parser... LHS, parser RHS>
requires (RHS::family != sequence_family)
consteval auto sequence_combined_left(sequence_parser<LHS...>, RHS)
{
	return sequence_parser<LHS..., RHS>{};
}

template <parser LHS, parser... RHS>
requires (LHS::family != sequence_family)
consteval auto sequence_combined_right(LHS, sequence_parser<RHS...>)
{
	return sequence_parser<LHS, RHS...>{};
}

template <parser... LHS, parser... RHS>
consteval auto sequence_combined_both(sequence_parser<LHS...>, sequence_parser<RHS...>)
{
	return sequence_parser<LHS..., RHS...>{};
}

} // namespace



#define SEQUENCE_OPERATOR_ASSERTER(LHS, RHS)                                                           \
	[]<parser LLHS, parser RRHS>(LLHS, RRHS) {                                                         \
		if constexpr (not std::same_as<typename LLHS::value_type, typename RRHS::value_type>)          \
		{                                                                                              \
			DEP_ASSERT_BINARY_NOT_OPERABLE(>>, LLHS{}, RRHS{}, LHS{}, RHS{});                          \
		}                                                                                              \
		else                                                                                           \
		{                                                                                              \
			DEP_ASSERT_BINARY_OPERABLE(>>, LLHS{}, RRHS{}, LHS{}, RHS{});                              \
			if constexpr (LLHS::family == all_of_family and RRHS::family == all_of_family)             \
			{                                                                                          \
				constexpr auto str = combine_strings<underlying_v<LLHS>, underlying_v<RRHS>>;          \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, all_of_parser<str>{},                    \
											LHS{}  >> RHS{},  all_of_parser<str>{});                   \
			}                                                                                          \
			else if constexpr (LLHS::family == sequence_family and RRHS::family != sequence_family)    \
			{                                                                                          \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_left(LLHS{}, RRHS{}),  \
											LHS{}  >> RHS{},  sequence_combined_left(LHS{},  RHS{}));  \
			}                                                                                          \
			else if constexpr (LLHS::family != sequence_family and RRHS::family == sequence_family)    \
			{                                                                                          \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_right(LLHS{}, RRHS{}), \
											LHS{}  >> RHS{},  sequence_combined_right(LHS{},  RHS{})); \
			}                                                                                          \
			else if constexpr (LLHS::family == sequence_family and RRHS::family == sequence_family)    \
			{                                                                                          \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_both(LLHS{}, RRHS{}),  \
											LHS{}  >> RHS{},  sequence_combined_both(LHS{},  RHS{}));  \
			}                                                                                          \
			else                                                                                       \
			{                                                                                          \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, (sequence_parser<LLHS, RRHS>{}),         \
											LHS{}  >> RHS{},  (sequence_parser<LHS,  RHS>{}));         \
			}                                                                                          \
		}                                                                                              \
	}(LHS{}, RHS{});

#define SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
	(any_of_parser<"abc">) (any_of_parser<"xyz">) (any_of_parser<L"abc">) (any_of_parser<L"xyz">)

TEST("sequence operator", "{anything} >> {anything}")
{
	// Note that all the operations are reimplemented for sequence_checker. This is intentional. That way, there's redundancy in the code.
	// A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.

	// This works just fine, but it takes forever and may crash your computer. User beware.
	// ASSERT_ALL_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER);

	ASSERT_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER, SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES, SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES);
	
	ASSERT_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES);
}
