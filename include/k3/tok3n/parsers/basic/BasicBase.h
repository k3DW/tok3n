#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>

namespace k3::tok3n {

template <class P>
struct BasicTraits
{
	// using value_type;
	// static constexpr std::size_t length;
	// static constexpr bool failure_condition(Input<value_type>);
};

template <class P>
struct BasicBase
{
	using value_type = typename BasicTraits<P>::value_type;
	
	template <EqualityComparableWith<value_type> V>
    using result_for = Output<V>;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		using Traits = BasicTraits<P>;

		if (Traits::failure_condition(input))
			return { failure, input };
		else
			return { success, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		using Traits = BasicTraits<P>;

		if (Traits::failure_condition(input))
			return { failure, input };
		else
			return { success, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n
