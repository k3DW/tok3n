#include "pch.h"
#include "wchar_t-tests/samples.h"

FIXTURE("choice operator");

TEST("choice operator", "AnyOf | AnyOf")
{
	ASSERT_PARSER_VALUES_EQ(any1 | any2, any2 | any1);
	ASSERT_PARSER_VALUES_EQ(any1 | any3, any3 | any1);
	ASSERT_PARSER_VALUES_EQ(any2 | any3, any3 | any2);
	ASSERT_PARSER_VALUES_EQ(any1 | any2, AnyOf<TT("abcd")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | any3, AnyOf<TT("abcxyz")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | any3, AnyOf<TT("bcdxyz")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | any1, any1);
	ASSERT_PARSER_VALUES_EQ(any2 | any2, any2);
	ASSERT_PARSER_VALUES_EQ(any3 | any3, any3);
}

TEST("choice operator", "NoneOf | NoneOf")
{
	ASSERT_PARSER_VALUES_EQ(none1 | none2, none2 | none1);
	ASSERT_PARSER_VALUES_EQ(none1 | none3, none3 | none1);
	ASSERT_PARSER_VALUES_EQ(none2 | none3, none3 | none2);
	ASSERT_PARSER_VALUES_EQ(none1 | none2, NoneOf<TT("bc")>{});
	ASSERT_PARSER_VALUES_EQ(none1 | none3, NoneOf<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(none2 | none3, NoneOf<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(none1 | none1, none1);
	ASSERT_PARSER_VALUES_EQ(none2 | none2, none2);
	ASSERT_PARSER_VALUES_EQ(none3 | none3, none3);
}

TEST("choice operator", "AnyOf | NoneOf, and NoneOf | AnyOf")
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
	ASSERT_PARSER_VALUES_EQ(any1 | none1, NoneOf<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | none2, NoneOf<TT("d")>{});
	ASSERT_PARSER_VALUES_EQ(any1 | none3, NoneOf<TT("xyz")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | none1, NoneOf<TT("a")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | none2, NoneOf<TT("")>{});
	ASSERT_PARSER_VALUES_EQ(any2 | none3, NoneOf<TT("xyz")>{});
	ASSERT_PARSER_VALUES_EQ(any3 | none1, NoneOf<TT("abc")>{});
	ASSERT_PARSER_VALUES_EQ(any3 | none2, NoneOf<TT("bcd")>{});
	ASSERT_PARSER_VALUES_EQ(any3 | none3, NoneOf<TT("")>{});
}



TEST("choice operator", "Choice | Choice")
{
	ASSERT_PARSER_VALUES_EQ(cho1 | cho1, cho1);
	ASSERT_PARSER_VALUES_EQ(cho2 | cho2, cho2);
	ASSERT_PARSER_VALUES_EQ(cho3 | cho3, cho3);
	ASSERT_PARSER_VALUES_EQ(cho4 | cho4, cho4);
	ASSERT_PARSER_VALUES_EQ(cho1 | cho2, (Choice<All4, Non4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho1, (Choice<Non4, All4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho1 | cho3, (Choice<All4, Non4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho1, (Choice<All4, Any4, Non5, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho1 | cho4, (Choice<All4, Non4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho1, (Choice<Non5, All4, Any4, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho3, (Choice<Non4, All4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho2, (Choice<All4, Any4, Non5, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | cho4, (Choice<Non4, All4, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho2, (Choice<Non5, All4, Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | cho4, (Choice<All4, Any4, Non5, Non5, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | cho3, (Choice<Non5, All4, Any4, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho5 | cho5, cho5);
}

TEST("choice operator", "Choice | {anything}, and {anything} | Choice")
{
	ASSERT_PARSER_VALUES_EQ(cho1 | any1, (Choice<All4, Non4, Any1>{}));
	ASSERT_PARSER_VALUES_EQ(any1 | cho1, (Choice<Any1, All4, Non4>{}));
	ASSERT_PARSER_VALUES_EQ(cho2 | any4, (Choice<Non4, All4, Any4>{}));
	ASSERT_PARSER_VALUES_EQ(any4 | cho2, (Choice<Any4, Non4, All4>{}));
	ASSERT_PARSER_VALUES_EQ(cho3 | any3, (Choice<All4, Any4, Non5, Any3>{}));
	ASSERT_PARSER_VALUES_EQ(any3 | cho3, (Choice<Any3, All4, Any4, Non5>{}));
	ASSERT_PARSER_VALUES_EQ(cho4 | any2, (Choice<Non5, All4, Any4, Any2>{}));
	ASSERT_PARSER_VALUES_EQ(any2 | cho4, (Choice<Any2, Non5, All4, Any4>{}));
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
	auto do_if = [&func](auto val, OpType test_type)
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

template <StaticArray lhs, StaticArray rhs>
concept usable_in_set_operations = LikeStaticArrays<lhs, rhs> and detail::SortedAndUniqued<lhs> and detail::SortedAndUniqued<rhs>;

template <StaticArray lhs, StaticArray rhs, OpType type>
requires usable_in_set_operations<lhs, rhs>
constexpr auto set_operation_general()
{
	constexpr std::size_t length = []()
	{
		std::size_t count = 0;
		set_operation_impl<lhs, rhs, type>([&count](auto) { ++count; });
		return count;
	}();

	auto str = lhs.template create_empty_with_size<length>();
	set_operation_impl<lhs, rhs, type>([it = str.begin()](auto val) mutable { *it++ = val; });
	return str;
}

template <StaticArray lhs, StaticArray rhs>
requires usable_in_set_operations<lhs, rhs>
constexpr auto set_union_string = set_operation_general<lhs, rhs, OpType::set_union>();

template <StaticArray lhs, StaticArray rhs>
requires usable_in_set_operations<lhs, rhs>
constexpr auto set_intersection_string = set_operation_general<lhs, rhs, OpType::set_intersection>();

template <StaticArray lhs, StaticArray rhs>
requires usable_in_set_operations<lhs, rhs>
constexpr auto set_difference_left_string = set_operation_general<lhs, rhs, OpType::set_difference_left>();

template <StaticArray lhs, StaticArray rhs>
requires usable_in_set_operations<lhs, rhs>
constexpr auto set_difference_right_string = set_operation_general<lhs, rhs, OpType::set_difference_right>();

template <Parser... LHS, Parser RHS>
requires (RHS::family != ChoiceFamily)
consteval auto choice_combined_left(Choice<LHS...>, RHS)
{
	return Choice<LHS..., RHS>{};
}

template <Parser LHS, Parser... RHS>
requires (LHS::family != ChoiceFamily)
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
