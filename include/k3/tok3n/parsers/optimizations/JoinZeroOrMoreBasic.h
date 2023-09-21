#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticArray> class Basic, StaticArray arr>
struct Join<ZeroOrMore<Basic<arr>>>
{
	using result_type = Output<char>;

	static constexpr ParserFamily type = JoinType;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		using Traits = BasicTraits<Basic<arr>>;

		Output<char> result = { input.data(), 0 };

		while (not Traits::failure_condition(input))
		{
			result = { result.data(), result.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return { success, result, input };
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
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
