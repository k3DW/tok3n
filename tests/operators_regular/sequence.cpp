#include "pch.h"

TEST("sequence operator", "Literal >> Literal")
{
	assert
		, (l1 >> l1) == Literal<"literalliteral">{}
		, (l1 >> l2) == Literal<"literally">{}
		, (l1 >> l3) == Literal<"literaltest">{}
		, (l2 >> l1) == Literal<"lyliteral">{}
		, (l2 >> l2) == Literal<"lyly">{}
		, (l2 >> l3) == Literal<"lytest">{}
		, (l3 >> l1) == Literal<"testliteral">{}
		, (l3 >> l2) == Literal<"testly">{}
		, (l3 >> l3) == Literal<"testtest">{}
		;
}



TEST("sequence operator", "Sequence >> Sequence")
{
	assert
		, (seq1 >> seq1) == Sequence<L4, NC4, L4, NC4>{}
	, (seq2 >> seq2) == Sequence<NC4, L4, NC4, L4>{}
	, (seq3 >> seq3) == Sequence<L4, OC4, NC5, L4, OC4, NC5>{}
	, (seq4 >> seq4) == Sequence<NC5, L4, OC4, NC5, L4, OC4>{}
	, (seq1 >> seq2) == Sequence<L4, NC4, NC4, L4>{}
	, (seq2 >> seq1) == Sequence<NC4, L4, L4, NC4>{}
	, (seq1 >> seq3) == Sequence<L4, NC4, L4, OC4, NC5>{}
	, (seq3 >> seq1) == Sequence<L4, OC4, NC5, L4, NC4>{}
	, (seq1 >> seq4) == Sequence<L4, NC4, NC5, L4, OC4>{}
	, (seq4 >> seq1) == Sequence<NC5, L4, OC4, L4, NC4>{}
	, (seq2 >> seq3) == Sequence<NC4, L4, L4, OC4, NC5>{}
	, (seq3 >> seq2) == Sequence<L4, OC4, NC5, NC4, L4>{}
	, (seq2 >> seq4) == Sequence<NC4, L4, NC5, L4, OC4>{}
	, (seq4 >> seq2) == Sequence<NC5, L4, OC4, NC4, L4>{}
	, (seq3 >> seq4) == Sequence<L4, OC4, NC5, NC5, L4, OC4>{}
	, (seq4 >> seq3) == Sequence<NC5, L4, OC4, L4, OC4, NC5>{}
	;
}

TEST("sequence operator", "Sequence >> {anything}")
{
	assert
		, (seq1 >> oc1) == Sequence<L4, NC4, OC1>{}
		, (oc1 >> seq1) == Sequence<OC1, L4, NC4>{}
		, (seq2 >> oc4) == Sequence<NC4, L4, OC4>{}
		, (oc4 >> seq2) == Sequence<OC4, NC4, L4>{}
		, (seq3 >> oc3) == Sequence<L4, OC4, NC5, OC3>{}
		, (oc3 >> seq3) == Sequence<OC3, L4, OC4, NC5>{}
		, (seq4 >> oc2) == Sequence<NC5, L4, OC4, OC2>{}
		, (oc2 >> seq4) == Sequence<OC2, NC5, L4, OC4>{}
		;
}

TEST("sequence operator", "void result_type")
{
	constexpr auto void_sequence = (ign1 >> ign2);

	assert
		, void_sequence == Sequence<Ign1, Ign2>{}
		, std::same_as<decltype(void_sequence)::result_type, void>
		, parse(void_sequence, "abcabcabcdabcd").success("dabcd")
		;
}



namespace {

template <StaticString lhs, StaticString rhs>
consteval auto combine_strings(Literal<lhs>, Literal<rhs>)
{
	StaticString<lhs.size() + rhs.size()> str;
	auto it = str.begin();
	for (char c : lhs)
		*it++ = c;
	for (char c : rhs)
		*it++ = c;

	return str;
}

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



constexpr auto sequence_checker = []<Parser LHS, Parser RHS>(LHS, RHS) -> bool
{
	TOK3N_ASSERT_P2( requires { LHS{} >> RHS{}; }, "sequence operator doesn't compile, but it should" );

	if constexpr (LHS::type == LiteralType and RHS::type == LiteralType)
		TOK3N_ASSERT_P2( requires { { LHS{} >> RHS{} } -> std::same_as<Literal<combine_strings(LHS{}, RHS{})>>; }, "sequence operator on 2 Literal parsers should give a Literal parser with the concatenation of both strings" );

	else if constexpr (LHS::type == SequenceType and RHS::type != SequenceType)
		TOK3N_ASSERT_P2( requires { { LHS{} >> RHS{} } -> std::same_as<decltype(sequence_combined_left(LHS{}, RHS{}))>; }, "sequence operator on a Sequence<Ps...> and non-Sequence parser should give a Sequence<Ps..., non-Sequence>" );

	else if constexpr (LHS::type != SequenceType and RHS::type == SequenceType)
		TOK3N_ASSERT_P2( requires { { LHS{} >> RHS{} } -> std::same_as<decltype(sequence_combined_right(LHS{}, RHS{}))>; }, "sequence operator on a non-Sequence and Sequence<Ps...> parser should give a Sequence<non-Sequence, Ps...>" );

	else if constexpr (LHS::type == SequenceType and RHS::type == SequenceType)
		TOK3N_ASSERT_P2( requires { { LHS{} >> RHS{} } -> std::same_as<decltype(sequence_combined_both(LHS{}, RHS{}))>; }, "sequence operator on 2 Sequence parsers, Sequence<As...> and Sequence<Bs...>, should give a Sequence parser of the combined parser arguments, Sequence<As..., Bs...>" );

	else
		TOK3N_ASSERT_P2( (requires { { LHS{} >> RHS{} } -> std::same_as<Sequence<LHS, RHS>>; }), "sequence operator on any parsers not satisfying the above conditions should just give a Sequence of the 2 inputs");

	return true;
};

TEST("sequence operator", "{anything} >> {anything}")
{
	// Note that all the operations are reimplemented for sequence_checker. This is intentional. That way, there's redundancy in the code.
	// A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.
	assert
		, check_all_sample_pairs(sequence_checker)
		;
}
