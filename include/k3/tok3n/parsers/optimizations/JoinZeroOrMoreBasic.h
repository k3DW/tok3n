#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticString> class Basic, StaticString str>
struct Join<ZeroOrMore<Basic<str>>>
{
	using result_type = Output;

	static constexpr ParserType type = JoinType;

	static constexpr Result<result_type> parse(Input input)
	{
		using Traits = BasicTraits<Basic<str>>;

		Output result = { input.data(), 0 };

		while (not Traits::failure_condition(input))
		{
			result = { result.data(), result.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return { success, result, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		using Traits = BasicTraits<Basic<str>>;

		while (not Traits::failure_condition(input))
		{
			input = input.subspan(Traits::length);
		}

		return { success, input };
	}
};

} // namespace k3::tok3n
