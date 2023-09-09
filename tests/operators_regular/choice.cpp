#include "pch.h"

FIXTURE("choice operator");

TEST("choice operator", "OneChar | OneChar")
{
	ASSERT_PARSER_VALUES_EQ(oc1 | oc2, oc2 | oc1);
	ASSERT_PARSER_VALUES_EQ(oc1 | oc3, oc3 | oc1);
	ASSERT_PARSER_VALUES_EQ(oc2 | oc3, oc3 | oc2);
	ASSERT_PARSER_VALUES_EQ(oc1 | oc2, OneChar<"abcd">{});
	ASSERT_PARSER_VALUES_EQ(oc1 | oc3, OneChar<"abcxyz">{});
	ASSERT_PARSER_VALUES_EQ(oc2 | oc3, OneChar<"bcdxyz">{});
	ASSERT_PARSER_VALUES_EQ(oc1 | oc1, oc1);
	ASSERT_PARSER_VALUES_EQ(oc2 | oc2, oc2);
	ASSERT_PARSER_VALUES_EQ(oc3 | oc3, oc3);
}

TEST("choice operator", "NotChar | NotChar")
{
	ASSERT_PARSER_VALUES_EQ(nc1 | nc2, nc2 | nc1);
	ASSERT_PARSER_VALUES_EQ(nc1 | nc3, nc3 | nc1);
	ASSERT_PARSER_VALUES_EQ(nc2 | nc3, nc3 | nc2);
	ASSERT_PARSER_VALUES_EQ(nc1 | nc2, NotChar<"bc">{});
	ASSERT_PARSER_VALUES_EQ(nc1 | nc3, NotChar<"">{});
	ASSERT_PARSER_VALUES_EQ(nc2 | nc3, NotChar<"">{});
	ASSERT_PARSER_VALUES_EQ(nc1 | nc1, nc1);
	ASSERT_PARSER_VALUES_EQ(nc2 | nc2, nc2);
	ASSERT_PARSER_VALUES_EQ(nc3 | nc3, nc3);
}

TEST("choice operator", "OneChar | NotChar, and NotChar | OneChar")
{
	ASSERT_PARSER_VALUES_EQ(oc1 | nc1, nc1 | oc1);
	ASSERT_PARSER_VALUES_EQ(oc1 | nc2, nc2 | oc1);
	ASSERT_PARSER_VALUES_EQ(oc1 | nc3, nc3 | oc1);
	ASSERT_PARSER_VALUES_EQ(oc2 | nc1, nc1 | oc2);
	ASSERT_PARSER_VALUES_EQ(oc2 | nc2, nc2 | oc2);
	ASSERT_PARSER_VALUES_EQ(oc2 | nc3, nc3 | oc2);
	ASSERT_PARSER_VALUES_EQ(oc3 | nc1, nc1 | oc3);
	ASSERT_PARSER_VALUES_EQ(oc3 | nc2, nc2 | oc3);
	ASSERT_PARSER_VALUES_EQ(oc3 | nc3, nc3 | oc3);
	ASSERT_PARSER_VALUES_EQ(oc1 | nc1, NotChar<"">{});
	ASSERT_PARSER_VALUES_EQ(oc1 | nc2, NotChar<"d">{});
	ASSERT_PARSER_VALUES_EQ(oc1 | nc3, NotChar<"xyz">{});
	ASSERT_PARSER_VALUES_EQ(oc2 | nc1, NotChar<"a">{});
	ASSERT_PARSER_VALUES_EQ(oc2 | nc2, NotChar<"">{});
	ASSERT_PARSER_VALUES_EQ(oc2 | nc3, NotChar<"xyz">{});
	ASSERT_PARSER_VALUES_EQ(oc3 | nc1, NotChar<"abc">{});
	ASSERT_PARSER_VALUES_EQ(oc3 | nc2, NotChar<"bcd">{});
	ASSERT_PARSER_VALUES_EQ(oc3 | nc3, NotChar<"">{});
}



TEST("choice operator", "Choice | Choice")
{
	ASSERT_PARSER_VALUES_EQ(cho1 | cho1, cho1);
	ASSERT_PARSER_VALUES_EQ(cho2 | cho2, cho2);
	ASSERT_PARSER_VALUES_EQ(cho3 | cho3, cho3);
	ASSERT_PARSER_VALUES_EQ(cho4 | cho4, cho4);
	ASSERT_PARSER_VALUES_EQ(cho1 | cho2, (Choice<L4, NC4, NC4, L4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho1, (Choice<NC4, L4, L4, NC4>{}));
	ASSERT_PARSER_VALUES_EQ(cho1 | cho3, (Choice<L4, NC4, L4, OC4, NC5>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho1, (Choice<L4, OC4, NC5, L4, NC4>{}));
	ASSERT_PARSER_VALUES_EQ(cho1 | cho4, (Choice<L4, NC4, NC5, L4, OC4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho1, (Choice<NC5, L4, OC4, L4, NC4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho3, (Choice<NC4, L4, L4, OC4, NC5>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho2, (Choice<L4, OC4, NC5, NC4, L4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho4, (Choice<NC4, L4, NC5, L4, OC4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho2, (Choice<NC5, L4, OC4, NC4, L4>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho4, (Choice<L4, OC4, NC5, NC5, L4, OC4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho3, (Choice<NC5, L4, OC4, L4, OC4, NC5>{}));
	ASSERT_PARSER_VALUES_EQ(cho5 | cho5, cho5);
}

TEST("choice operator", "Choice | {anything}, and {anything} | Choice")
{
	ASSERT_PARSER_VALUES_EQ(cho1 | oc1, (Choice<L4, NC4, OC1>{}));
	ASSERT_PARSER_VALUES_EQ(oc1 | cho1, (Choice<OC1, L4, NC4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | oc4, (Choice<NC4, L4, OC4>{}));
	ASSERT_PARSER_VALUES_EQ(oc4 | cho2, (Choice<OC4, NC4, L4>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | oc3, (Choice<L4, OC4, NC5, OC3>{}));
	ASSERT_PARSER_VALUES_EQ(oc3 | cho3, (Choice<OC3, L4, OC4, NC5>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | oc2, (Choice<NC5, L4, OC4, OC2>{}));
	ASSERT_PARSER_VALUES_EQ(oc2 | cho4, (Choice<OC2, NC5, L4, OC4>{}));
}

TEST("choice operator", "void result_type")
{
	ASSERT_PARSER_VALUES_EQ(ign1 | ign2, cho5);
	ASSERT_PARSER_VALUES_NE(ign2 | ign1, cho5);
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

template <StaticArray lhs, StaticArray rhs, OpType type>
requires LikeStaticArrays<lhs, rhs>
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

template <StaticArray lhs, StaticArray rhs, OpType type>
requires LikeStaticArrays<lhs, rhs>
constexpr auto set_operation_general()
{
	constexpr std::size_t length = []()
	{
		std::size_t count = 0;
		set_operation_impl<lhs, rhs, type>([&count](char) { ++count; });
		return count;
	}();

	auto str = lhs.create_empty_with_size<length>;
	set_operation_impl<lhs, rhs, type>([it = str.begin()](char val) mutable { *it++ = val; });
	return str;
}

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs> and (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
constexpr auto set_union_string = set_operation_general<lhs, rhs, OpType::set_union>();

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs> and (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
constexpr auto set_intersection_string = set_operation_general<lhs, rhs, OpType::set_intersection>();

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs> and (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
constexpr auto set_difference_left_string = set_operation_general<lhs, rhs, OpType::set_difference_left>();

template <StaticArray lhs, StaticArray rhs>
requires LikeStaticArrays<lhs, rhs> and (is_sorted_and_uniqued(lhs)) and (is_sorted_and_uniqued(rhs))
constexpr auto set_difference_right_string = set_operation_general<lhs, rhs, OpType::set_difference_right>();

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



#define CHOICE_OPERATOR_ASSERTER(LHS, RHS)                                                                            \
	[&]<Parser LLHS, Parser RRHS>(LLHS, RRHS) {                                                                       \
		if constexpr (not std::same_as<typename LLHS::result_type, typename RRHS::result_type>)                       \
		{                                                                                                             \
			DEP_ASSERT_BINARY_NOT_OPERABLE(|, LLHS{}, RRHS{}, LHS{}, RHS{});                                          \
		}                                                                                                             \
		else                                                                                                          \
		{                                                                                                             \
			DEP_ASSERT_BINARY_OPERABLE(|, LLHS{}, RRHS{}, LHS{}, RHS{});                                              \
			if constexpr (std::same_as<LLHS, RRHS>)                                                                   \
			{                                                                                                         \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, LLHS{},                                                  \
					                        LHS{}  | RHS{},  LHS{});                                                  \
			}                                                                                                         \
			else if constexpr (LLHS::type == OneCharType and RRHS::type == OneCharType)                               \
			{                                                                                                         \
				constexpr auto str = set_union_string<underlying::string<LLHS>, underlying::string<RRHS>>;            \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, OneChar<str>{},                                          \
					                        LHS{}  | RHS{},  OneChar<str>{});                                         \
			}                                                                                                         \
			else if constexpr (LLHS::type == NotCharType and RRHS::type == NotCharType)                               \
			{                                                                                                         \
				constexpr auto str = set_intersection_string<underlying::string<LLHS>, underlying::string<RRHS>>;     \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, NotChar<str>{},                                          \
					                        LHS{}  | RHS{},  NotChar<str>{});                                         \
			}                                                                                                         \
			else if constexpr (LLHS::type == NotCharType and RRHS::type == OneCharType)                               \
			{                                                                                                         \
				constexpr auto str = set_difference_left_string<underlying::string<LLHS>, underlying::string<RRHS>>;  \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, NotChar<str>{},                                          \
					                        LHS{}  | RHS{},  NotChar<str>{});                                         \
			}                                                                                                         \
			else if constexpr (LLHS::type == OneCharType and RRHS::type == NotCharType)                               \
			{                                                                                                         \
				constexpr auto str = set_difference_right_string<underlying::string<LLHS>, underlying::string<RRHS>>; \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, NotChar<str>{},                                          \
					                        LHS{}  | RHS{},  NotChar<str>{});                                         \
			}                                                                                                         \
			else if constexpr (LLHS::type == ChoiceType and RRHS::type != ChoiceType)                                 \
			{                                                                                                         \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, choice_combined_left(LLHS{}, RRHS{}),                    \
					                        LHS{}  | RHS{},  choice_combined_left(LHS{},  RHS{}));                    \
			}                                                                                                         \
			else if constexpr (LLHS::type != ChoiceType and RRHS::type == ChoiceType)                                 \
			{                                                                                                         \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, choice_combined_right(LLHS{}, RRHS{}),                   \
					                        LHS{}  | RHS{},  choice_combined_right(LHS{},  RHS{}));                   \
			}                                                                                                         \
			else if constexpr (LLHS::type == ChoiceType and RRHS::type == ChoiceType)                                 \
			{                                                                                                         \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, choice_combined_both(LLHS{}, RRHS{}),                    \
					                        LHS{}  | RHS{},  choice_combined_both(LHS{},  RHS{}));                    \
			}                                                                                                         \
			else                                                                                                      \
			{                                                                                                         \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} | RRHS{}, (Choice<LLHS, RRHS>{}),                                  \
					                        LHS{}  | RHS{},  (Choice<LHS,  RHS>{}));                                  \
			}                                                                                                         \
		}                                                                                                             \
	}(LHS{}, RHS{});


TEST("choice operator", "{anything} | {anything}")
{
	// Note that all the operations are reimplemented for choice_checker. This is intentional. That way, there's redundancy in the code.
	// A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.

	// This works just fine, but it takes forever and may crash your computer. User beware.
	//ASSERT_ALL_SAMPLES_2(CHOICE_OPERATOR_ASSERTER);
}
