#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticArray> class Basic, StaticArray arr>
struct Join<ZeroOrMore<Basic<arr>>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <EqualityComparableWith<value_type> V>
	using result_for = Output<V>;

	static constexpr ParserFamily family = JoinFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		using Traits = BasicTraits<Basic<arr>>;

		Output<value_type> result = { input.data(), 0 };

		while (not Traits::failure_condition(input))
		{
			result = { result.data(), result.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return { success, result, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		using Traits = BasicTraits<Basic<arr>>;

		while (not Traits::failure_condition(input))
		{
			input = input.subspan(Traits::length);
		}

		return { success, input };
	}
};

} // namespace k3::tok3n
