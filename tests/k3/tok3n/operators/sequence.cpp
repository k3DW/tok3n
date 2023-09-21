#include "pch.h"

FIXTURE("sequence operator");

TEST("sequence operator", "AllOf >> AllOf")
{
	ASSERT_PARSER_VALUES_EQ(all1 >> all1, AllOf<"literalliteral">{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all2, AllOf<"literally">{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all3, AllOf<"literaltest">{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all1, AllOf<"lyliteral">{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all2, AllOf<"lyly">{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all3, AllOf<"lytest">{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all1, AllOf<"testliteral">{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all2, AllOf<"testly">{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all3, AllOf<"testtest">{});
}



TEST("sequence operator", "Sequence >> Sequence")
{
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq1, (Sequence<All4, Non4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq2, (Sequence<Non4, All4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq3, (Sequence<All4, Any4, Non5, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq4, (Sequence<Non5, All4, Any4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq5, (Sequence<Ign1, Ign2, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq2, (Sequence<All4, Non4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq1, (Sequence<Non4, All4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq3, (Sequence<All4, Non4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq1, (Sequence<All4, Any4, Non5, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq4, (Sequence<All4, Non4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq1, (Sequence<Non5, All4, Any4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq1 >> seq5, (Sequence<All4, Non4, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq1, (Sequence<Ign1, Ign2, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq3, (Sequence<Non4, All4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq2, (Sequence<All4, Any4, Non5, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq4, (Sequence<Non4, All4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq2, (Sequence<Non5, All4, Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> seq5, (Sequence<Non4, All4, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq2, (Sequence<Ign1, Ign2, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq4, (Sequence<All4, Any4, Non5, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq3, (Sequence<Non5, All4, Any4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> seq5, (Sequence<All4, Any4, Non5, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq3, (Sequence<Ign1, Ign2, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> seq5, (Sequence<Non5, All4, Any4, Ign1, Ign2>{}));
	ASSERT_PARSER_VALUES_EQ(seq5 >> seq4, (Sequence<Ign1, Ign2, Non5, All4, Any4>{}));
}

TEST("sequence operator", "Sequence >> {anything}")
{
	ASSERT_PARSER_VALUES_EQ(seq1 >> any1, (Sequence<All4, Non4, Any1>{}));
	ASSERT_PARSER_VALUES_EQ(any1 >> seq1, (Sequence<Any1, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(seq2 >> any4, (Sequence<Non4, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(any4 >> seq2, (Sequence<Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(seq3 >> any3, (Sequence<All4, Any4, Non5, Any3>{}));
	ASSERT_PARSER_VALUES_EQ(any3 >> seq3, (Sequence<Any3, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(seq4 >> any2, (Sequence<Non5, All4, Any4, Any2>{}));
	ASSERT_PARSER_VALUES_EQ(any2 >> seq4, (Sequence<Any2, Non5, All4, Any4>{}));
}

TEST("sequence operator", "void result_type")
{
	ASSERT_PARSER_VALUES_EQ(ign1 >> ign2, seq5);
	ASSERT_PARSER_VALUES_NE(ign2 >> ign1, seq5);
}



namespace {

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs>
constexpr auto combine_strings = []
{
	auto str = lhs.create_empty_with_size<lhs.size() + rhs.size()>;
	auto it = str.begin();
	for (char c : lhs)
		*it++ = c;
	for (char c : rhs)
		*it++ = c;

	return str;
}();

template <Parser... LHS, Parser RHS>
requires (not IsParser<RHS, SequenceType>)
consteval auto sequence_combined_left(Sequence<LHS...>, RHS)
{
	return Sequence<LHS..., RHS>{};
}

template <Parser LHS, Parser... RHS>
requires (not IsParser<LHS, SequenceType>)
consteval auto sequence_combined_right(LHS, Sequence<RHS...>)
{
	return Sequence<LHS, RHS...>{};
}

template <Parser... LHS, Parser... RHS>
consteval auto sequence_combined_both(Sequence<LHS...>, Sequence<RHS...>)
{
	return Sequence<LHS..., RHS...>{};
}

} // namespace



#define SEQUENCE_OPERATOR_ASSERTER(LHS, RHS)                                                          \
	[&]<Parser LLHS, Parser RRHS>(LLHS, RRHS) {                                                       \
		DEP_ASSERT_BINARY_OPERABLE(>>, LLHS{}, RRHS{}, LHS{}, RHS{});                                 \
		if constexpr (LLHS::type == AllOfType and RRHS::type == AllOfType)                            \
		{                                                                                             \
			constexpr auto str = combine_strings<underlying::string<LLHS>, underlying::string<RRHS>>; \
			DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, AllOf<str>{},                               \
					                    LHS{}  >> RHS{},  AllOf<str>{});                              \
		}                                                                                             \
		else if constexpr (LLHS::type == SequenceType and RRHS::type != SequenceType)                 \
		{                                                                                             \
			DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_left(LLHS{}, RRHS{}),     \
					                    LHS{}  >> RHS{},  sequence_combined_left(LHS{},  RHS{}));     \
		}                                                                                             \
		else if constexpr (LLHS::type != SequenceType and RRHS::type == SequenceType)                 \
		{                                                                                             \
			DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_right(LLHS{}, RRHS{}),    \
					                    LHS{}  >> RHS{},  sequence_combined_right(LHS{},  RHS{}));    \
		}                                                                                             \
		else if constexpr (LLHS::type == SequenceType and RRHS::type == SequenceType)                 \
		{                                                                                             \
			DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_both(LLHS{}, RRHS{}),     \
					                    LHS{}  >> RHS{},  sequence_combined_both(LHS{},  RHS{}));     \
		}                                                                                             \
		else                                                                                          \
		{                                                                                             \
			DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, (Sequence<LLHS, RRHS>{}),                   \
					                    LHS{}  >> RHS{},  (Sequence<LHS,  RHS>{}));                   \
		}                                                                                             \
	}(LHS{}, RHS{});

TEST("sequence operator", "{anything} >> {anything}")
{
	// Note that all the operations are reimplemented for sequence_checker. This is intentional. That way, there's redundancy in the code.
	// A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.

	// This works just fine, but it takes forever and may crash your computer. User beware.
	//ASSERT_ALL_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER);
}
