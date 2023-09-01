#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticString> class Basic, StaticString str>
struct Join<OneOrMore<Basic<str>>>
{
	using result_type = Input;

	static constexpr ParserType type = JoinType;

	static constexpr Result<result_type> parse(Input input)
	{
		using Traits = BasicTraits<Basic<str>>;

		if (Traits::failure_condition(input))
			return { failure, input };

		Input result = { input.data(), Traits::length };
		input.remove_prefix(Traits::length);

		while (not Traits::failure_condition(input))
		{
			result = { result.data(), result.size() + Traits::length };
			input.remove_prefix(Traits::length);
		}

		return { success, result, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		using Traits = BasicTraits<Basic<str>>;

		if (Traits::failure_condition(input))
			return { failure, input };

		input.remove_prefix(Traits::length);

		while (not Traits::failure_condition(input))
		{
			input.remove_prefix(Traits::length);
		}

		return { success, input };
	}
};

} // namespace k3::tok3n
