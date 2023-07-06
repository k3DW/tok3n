#include "pch.h"

TEST("choice operator", "OneChar | OneChar")
{
	assert
		, (oc1 | oc2) == (oc2 | oc1)
		, (oc1 | oc3) == (oc3 | oc1)
		, (oc2 | oc3) == (oc3 | oc2)
		, (oc1 | oc2) == OneChar<"abcd">{}
		, (oc1 | oc3) == OneChar<"abcxyz">{}
		, (oc2 | oc3) == OneChar<"bcdxyz">{}
		, (oc1 | oc1) == oc1
		, (oc2 | oc2) == oc2
		, (oc3 | oc3) == oc3
		;
}

TEST("choice operator", "NotChar | NotChar")
{
	assert
		, (nc1 | nc2) == (nc2 | nc1)
		, (nc1 | nc3) == (nc3 | nc1)
		, (nc2 | nc3) == (nc3 | nc2)
		, (nc1 | nc2) == NotChar<"bc">{}
		, (nc1 | nc3) == NotChar<"">{}
		, (nc2 | nc3) == NotChar<"">{}
		, (nc1 | nc1) == nc1
		, (nc2 | nc2) == nc2
		, (nc3 | nc3) == nc3
		;
}

TEST("choice operator", "OneChar | NotChar, and NotChar | OneChar")
{
	assert
		, (oc1 | nc1) == (nc1 | oc1)
		, (oc1 | nc2) == (nc2 | oc1)
		, (oc1 | nc3) == (nc3 | oc1)
		, (oc2 | nc1) == (nc1 | oc2)
		, (oc2 | nc2) == (nc2 | oc2)
		, (oc2 | nc3) == (nc3 | oc2)
		, (oc3 | nc1) == (nc1 | oc3)
		, (oc3 | nc2) == (nc2 | oc3)
		, (oc3 | nc3) == (nc3 | oc3)
		, (oc1 | nc1) == NotChar<"">{}
		, (oc1 | nc2) == NotChar<"d">{}
		, (oc1 | nc3) == NotChar<"xyz">{}
		, (oc2 | nc1) == NotChar<"a">{}
		, (oc2 | nc2) == NotChar<"">{}
		, (oc2 | nc3) == NotChar<"xyz">{}
		, (oc3 | nc1) == NotChar<"abc">{}
		, (oc3 | nc2) == NotChar<"bcd">{}
		, (oc3 | nc3) == NotChar<"">{}
		;
}



TEST("choice operator", "Choice | Choice")
{
	assert
		, (cho1 | cho1) == cho1
		, (cho2 | cho2) == cho2
		, (cho3 | cho3) == cho3
		, (cho4 | cho4) == cho4
		, (cho1 | cho2) == Choice<L4, NC4, NC4, L4>{}
		, (cho2 | cho1) == Choice<NC4, L4, L4, NC4>{}
		, (cho1 | cho3) == Choice<L4, NC4, L4, OC4, NC5>{}
		, (cho3 | cho1) == Choice<L4, OC4, NC5, L4, NC4>{}
		, (cho1 | cho4) == Choice<L4, NC4, NC5, L4, OC4>{}
		, (cho4 | cho1) == Choice<NC5, L4, OC4, L4, NC4>{}
		, (cho2 | cho3) == Choice<NC4, L4, L4, OC4, NC5>{}
		, (cho3 | cho2) == Choice<L4, OC4, NC5, NC4, L4>{}
		, (cho2 | cho4) == Choice<NC4, L4, NC5, L4, OC4>{}
		, (cho4 | cho2) == Choice<NC5, L4, OC4, NC4, L4>{}
		, (cho3 | cho4) == Choice<L4, OC4, NC5, NC5, L4, OC4>{}
		, (cho4 | cho3) == Choice<NC5, L4, OC4, L4, OC4, NC5>{}
		;
}

TEST("choice operator", "Choice | {anything}, and {anything} | Choice")
{
	assert
		, (cho1 | oc1) == Choice<L4, NC4, OC1>{}
		, (oc1 | cho1) == Choice<OC1, L4, NC4>{}
		, (cho2 | oc4) == Choice<NC4, L4, OC4>{}
		, (oc4 | cho2) == Choice<OC4, NC4, L4>{}
		, (cho3 | oc3) == Choice<L4, OC4, NC5, OC3>{}
		, (oc3 | cho3) == Choice<OC3, L4, OC4, NC5>{}
		, (cho4 | oc2) == Choice<NC5, L4, OC4, OC2>{}
		, (oc2 | cho4) == Choice<OC2, NC5, L4, OC4>{}
		;
}

TEST("choice operator", "void result_type")
{
	constexpr auto void_choice = (ign1 | ign2);

	assert
		, void_choice == Choice<Ign1, Ign2>{}
		, std::same_as<decltype(void_choice)::result_type, void>
		, parse(void_choice, "abcabcabcdabcd").success("abcabcdabcd")
		;
}



namespace {

enum class OpType
{
	set_union            = 0b0001,
	set_intersection     = 0b0010,
	set_difference_left  = 0b0100,
	set_difference_right = 0b1000,
};

constexpr OpType operator|(OpType lhs, OpType rhs)
{
	return OpType{ static_cast<int>(lhs) | static_cast<int>(rhs) };
}

constexpr bool operator&(OpType lhs, OpType rhs)
{
	return 0 != (static_cast<int>(lhs) & static_cast<int>(rhs));
}

template <StaticString lhs, StaticString rhs, OpType type>
constexpr auto set_operation_impl(auto func)
{
	auto do_if = [&func](char val, OpType test_type)
	{
		if (type & test_type)
			func(val);
	};

	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();
	auto lhs_end = lhs.end();
	auto rhs_end = rhs.end();

	while (lhs_it != lhs_end or rhs_it != rhs_end)
	{
		if (lhs_it == lhs_end)
			do_if(*rhs_it++, OpType::set_union | OpType::set_difference_right);

		else if (rhs_it == rhs_end)
			do_if(*lhs_it++, OpType::set_union | OpType::set_difference_left);

		else if (*lhs_it < *rhs_it)
			do_if(*lhs_it++, OpType::set_union | OpType::set_difference_left);

		else if (*rhs_it < *lhs_it)
			do_if(*rhs_it++, OpType::set_union | OpType::set_difference_right);

		else
		{
			do_if(*lhs_it++, OpType::set_union | OpType::set_intersection);
			++rhs_it;
		}
	}
}

template <StaticString lhs, StaticString rhs, OpType type>
constexpr auto set_operation_general()
{
	constexpr std::size_t length = []()
	{
		std::size_t count = 0;
		set_operation_impl<lhs, rhs, type>([&count](char) { ++count; });
		return count;
	}();

	StaticString<length> str;
	set_operation_impl<lhs, rhs, type>([it = str.begin()](char val) mutable { *it++ = val; });
	return str;
}

template <StaticString lhs, StaticString rhs>
requires (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
consteval auto set_union_string(OneChar<lhs>, OneChar<rhs>)
{
	return set_operation_general<lhs, rhs, OpType::set_union>();
}

template <StaticString lhs, StaticString rhs>
requires (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
consteval auto set_intersection_string(NotChar<lhs>, NotChar<rhs>)
{
	return set_operation_general<lhs, rhs, OpType::set_intersection>();
}

template <StaticString lhs, StaticString rhs>
requires (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
consteval auto set_difference_left_string(NotChar<lhs>, OneChar<rhs>)
{
	return set_operation_general<lhs, rhs, OpType::set_difference_left>();
}

template <StaticString lhs, StaticString rhs>
requires (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
consteval auto set_difference_right_string(OneChar<lhs>, NotChar<rhs>)
{
	return set_operation_general<lhs, rhs, OpType::set_difference_right>();
}

template <Parser... LHS, Parser RHS>
requires (not IsParser<RHS, ChoiceType>)
consteval auto choice_combined_left(Choice<LHS...>, RHS)
{
	return Choice<LHS..., RHS>{};
}

template <Parser LHS, Parser... RHS>
requires (not IsParser<LHS, ChoiceType>)
consteval auto choice_combined_right(LHS, Choice<RHS...>)
{
	return Choice<LHS, RHS...>{};
}

template <Parser... LHS, Parser... RHS>
consteval auto choice_combined_both(Choice<LHS...>, Choice<RHS...>)
{
	return Choice<LHS..., RHS...>{};
}

} // namespace



constexpr auto choice_checker = []<Parser LHS, Parser RHS>(LHS, RHS) -> bool
{
	if constexpr (not std::same_as<typename LHS::result_type, typename RHS::result_type>)
	{
		TOK3N_ASSERT_P2( not requires { LHS{} | RHS{}; }, "choice operator compiles, but it shouldn't" );
	}
	else
	{
		TOK3N_ASSERT_P2( requires { LHS{} | RHS{}; },               "choice operator doesn't compile, but it should" );
		TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> Parser; }, "choice operator compiles, but doesn't give a Parser" );

		if constexpr (std::same_as<LHS, RHS>)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<LHS>; }, "choice operator on 2 of the same parsers should give that parser" );


		else if constexpr (LHS::type == OneCharType and RHS::type == OneCharType)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<OneChar<set_union_string(LHS{}, RHS{})>>; }, "choice operator on 2 OneChar parsers should give a OneChar parser with the set union of the 2 input strings" );
		
		else if constexpr (LHS::type == NotCharType and RHS::type == NotCharType)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<NotChar<set_intersection_string(LHS{}, RHS{})>>; }, "choice operator on 2 NotChar parsers should give a OneChar parser with the set intersection of the 2 input strings" );
		
		else if constexpr (LHS::type == NotCharType and RHS::type == OneCharType)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<NotChar<set_difference_left_string(LHS{}, RHS{})>>; }, "choice operator on a NotChar and OneChar parser should give a NotChar parser with the set difference of the left and right input strings, in that order" );
		
		else if constexpr (LHS::type == OneCharType and RHS::type == NotCharType)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<NotChar<set_difference_right_string(LHS{}, RHS{})>>; }, "choice operator on a OneChar and NotChar parser should give a NotChar parser with the set difference of the right and left input strings, in that order" );


		else if constexpr (LHS::type == ChoiceType and RHS::type != ChoiceType)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<decltype(choice_combined_left(LHS{}, RHS{}))>; }, "choice operator on a Choice<Ps...> and non-Choice parser should give a Choice<Ps..., non-Choice>" );

		else if constexpr (LHS::type != ChoiceType and RHS::type == ChoiceType)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<decltype(choice_combined_right(LHS{}, RHS{}))>; }, "choice operator on a non-Choice and Choice<Ps...> parser should give a Choice<non-Choice, Ps...>" );

		else if constexpr (LHS::type == ChoiceType and RHS::type == ChoiceType)
			TOK3N_ASSERT_P2( requires { { LHS{} | RHS{} } -> std::same_as<decltype(choice_combined_both(LHS{}, RHS{}))>; }, "choice operator on 2 Choice parsers, Choice<As...> and Choice<Bs...>, should give a Choice parser of the combined parser arguments, Choice<As..., Bs...>" );

		else
			TOK3N_ASSERT_P2( (requires { { LHS{} | RHS{} } -> std::same_as<Choice<LHS, RHS>>; }), "choice operator on any parsers not satisfying the above conditions should just give a Choice of the 2 inputs" );
	}

	return true;
};

TEST("choice operator", "{anything} | {anything}")
{
	// Note that all the operations are reimplemented for choice_checker. This is intentional. That way, there's redundancy in the code.
	// A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.
	assert
		, check_all_sample_pairs(choice_checker)
		;
}
