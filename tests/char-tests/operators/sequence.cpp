#include "samples.h"

using namespace k3::tok3n;

FIXTURE("sequence operator");

TEST("sequence operator", "AllOf >> AllOf")
{
	ASSERT_PARSER_VALUES_EQ(all1 >> all1, AllOf<TT("literalliteral")>{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all2, AllOf<TT("literally")>{});
	ASSERT_PARSER_VALUES_EQ(all1 >> all3, AllOf<TT("literaltest")>{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all1, AllOf<TT("lyliteral")>{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all2, AllOf<TT("lyly")>{});
	ASSERT_PARSER_VALUES_EQ(all2 >> all3, AllOf<TT("lytest")>{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all1, AllOf<TT("testliteral")>{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all2, AllOf<TT("testly")>{});
	ASSERT_PARSER_VALUES_EQ(all3 >> all3, AllOf<TT("testtest")>{});
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

TEST("sequence operator", "non consteval")
{
	(any1 >> any2).parse(TT("abc"));
}



namespace {

template <detail::static_array lhs, detail::static_array rhs>
requires decltype(detail::like_static_arrays(lhs, rhs))::value
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

template <detail::parser... LHS, detail::parser RHS>
requires (RHS::family != detail::sequence_family)
consteval auto sequence_combined_left(Sequence<LHS...>, RHS)
{
	return Sequence<LHS..., RHS>{};
}

template <detail::parser LHS, detail::parser... RHS>
requires (LHS::family != detail::sequence_family)
consteval auto sequence_combined_right(LHS, Sequence<RHS...>)
{
	return Sequence<LHS, RHS...>{};
}

template <detail::parser... LHS, detail::parser... RHS>
consteval auto sequence_combined_both(Sequence<LHS...>, Sequence<RHS...>)
{
	return Sequence<LHS..., RHS...>{};
}

} // namespace



#define SEQUENCE_OPERATOR_ASSERTER(LHS, RHS)                                                                        \
	[]<detail::parser LLHS, detail::parser RRHS>(LLHS, RRHS) {                                                      \
		if constexpr (not std::same_as<typename LLHS::value_type, typename RRHS::value_type>)                       \
		{                                                                                                           \
			DEP_ASSERT_BINARY_NOT_OPERABLE(>>, LLHS{}, RRHS{}, LHS{}, RHS{});                                       \
		}                                                                                                           \
		else                                                                                                        \
		{                                                                                                           \
			DEP_ASSERT_BINARY_OPERABLE(>>, LLHS{}, RRHS{}, LHS{}, RHS{});                                           \
			if constexpr (LLHS::family == detail::all_of_family and RRHS::family == detail::all_of_family)          \
			{                                                                                                       \
				constexpr auto str = combine_strings<underlying_v<LLHS>, underlying_v<RRHS>>;                       \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, AllOf<str>{},                                         \
											LHS{}  >> RHS{},  AllOf<str>{});                                        \
			}                                                                                                       \
			else if constexpr (LLHS::family == detail::sequence_family and RRHS::family != detail::sequence_family) \
			{                                                                                                       \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_left(LLHS{}, RRHS{}),               \
											LHS{}  >> RHS{},  sequence_combined_left(LHS{},  RHS{}));               \
			}                                                                                                       \
			else if constexpr (LLHS::family != detail::sequence_family and RRHS::family == detail::sequence_family) \
			{                                                                                                       \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_right(LLHS{}, RRHS{}),              \
											LHS{}  >> RHS{},  sequence_combined_right(LHS{},  RHS{}));              \
			}                                                                                                       \
			else if constexpr (LLHS::family == detail::sequence_family and RRHS::family == detail::sequence_family) \
			{                                                                                                       \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, sequence_combined_both(LLHS{}, RRHS{}),               \
											LHS{}  >> RHS{},  sequence_combined_both(LHS{},  RHS{}));               \
			}                                                                                                       \
			else                                                                                                    \
			{                                                                                                       \
				DEP_ASSERT_PARSER_VALUES_EQ(LLHS{} >> RRHS{}, (Sequence<LLHS, RRHS>{}),                             \
											LHS{}  >> RHS{},  (Sequence<LHS,  RHS>{}));                             \
			}                                                                                                       \
		}                                                                                                           \
	}(LHS{}, RHS{});

#define SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
	(AnyOf<"abc">) (AnyOf<"xyz">) (AnyOf<L"abc">) (AnyOf<L"xyz">)

TEST("sequence operator", "{anything} >> {anything}")
{
	// Note that all the operations are reimplemented for sequence_checker. This is intentional. That way, there's redundancy in the code.
	// A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.

	// This works just fine, but it takes forever and may crash your computer. User beware.
	// ASSERT_ALL_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER);

	ASSERT_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER, SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES, SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES);
	
	ASSERT_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES);
}
