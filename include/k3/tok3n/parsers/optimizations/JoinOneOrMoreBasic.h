#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticString> class Basic, StaticString str>
struct Join<OneOrMore<Basic<str>>>
{
	using result_type = Output<char>;

	static constexpr ParserType type = JoinType;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		using Traits = BasicTraits<Basic<str>>;

		if (Traits::failure_condition(input))
			return { failure, input };

		Output<char> result = { input.data(), Traits::length };
		input = input.subspan(Traits::length);

		while (not Traits::failure_condition(input))
		{
			result = { result.data(), result.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return { success, result, input };
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		using Traits = BasicTraits<Basic<str>>;

		if (Traits::failure_condition(input))
			return { failure, input };

		input = input.subspan(Traits::length);

		while (not Traits::failure_condition(input))
		{
			input = input.subspan(Traits::length);
		}

		return { success, input };
	}
};

} // namespace k3::tok3n
