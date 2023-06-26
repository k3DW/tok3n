#pragma once
#include <k3/tok3n/parsers/basic/fwd.h>

namespace k3::tok3n {

template <class P>
struct BasicTraits
{
	// static constexpr std::size_t length;
	// static constexpr bool failure_condition(Input);
};

template <class P>
struct BasicBase
{
	using result_type = Input;

	static constexpr Result<result_type> parse(Input input)
	{
		using Traits = BasicTraits<P>;

		if (Traits::failure_condition(input))
			return { failure, input };
		else
			return { success, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		using Traits = BasicTraits<P>;

		if (Traits::failure_condition(input))
			return { failure, input };
		else
			return { success, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n
