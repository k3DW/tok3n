#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n::detail {

template <class CRTP>
struct Basic
{
	using result_type = Input;

	static constexpr Result<result_type> parse(Input input)
	{
		if (CRTP::_failure_condition(input))
			return { failure, input };
		else
			return { success, { input.data(), CRTP::_length }, { input.data() + CRTP::_length, input.size() - CRTP::_length } };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		if (CRTP::_failure_condition(input))
			return { failure, input };
		else
			return { success, { input.data() + CRTP::_length, input.size() - CRTP::_length } };
	}
};

} // namespace k3::tok3n::detail
