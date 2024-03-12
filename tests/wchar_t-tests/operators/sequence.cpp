#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("sequence operator");

TEST("sequence operator", "AllOf >> AllOf")
{
	ASSERT_PARSER_VALUES_EQ(all1 >> all1, AllOf<L"literalliteral">{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all2, AllOf<L"literally">{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all3, AllOf<L"literaltest">{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all1, AllOf<L"lyliteral">{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all2, AllOf<L"lyly">{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all3, AllOf<L"lytest">{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all1, AllOf<L"testliteral">{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all2, AllOf<L"testly">{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all3, AllOf<L"testtest">{});
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
	for (auto c : lhs)
		*it++ = c;
	for (auto c : rhs)
		*it++ = c;

	return str;
}();

template <Parser... LHS, Parser RHS>
requires (not IsParser<RHS, SequenceFamily>)
consteval auto sequence_combined_left(Sequence<LHS...>, RHS)
{
	return Sequence<LHS..., RHS>{};
}

template <Parser LHS, Parser... RHS>
requires (not IsParser<LHS, SequenceFamily>)
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
