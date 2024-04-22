#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticArray> class Basic, StaticArray arr>
struct Join<Maybe<Basic<arr>>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <EqualityComparableWith<value_type> V>
	using result_for = Output<V>;

	static constexpr ParserFamily family = JoinFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		using Traits = BasicTraits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return { success, { input.data(), 0 }, input };

		return { success, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		using Traits = BasicTraits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return { success, input };

		return { success, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n
