#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticString> class Basic, StaticString str>
struct Join<Maybe<Basic<str>>>
{
	using result_type = Output<char>;

	static constexpr ParserType type = JoinType;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		using Traits = BasicTraits<Basic<str>>;

		if (Traits::failure_condition(input))
			return { success, { input.data(), 0 }, input };

		return { success, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		using Traits = BasicTraits<Basic<str>>;

		if (Traits::failure_condition(input))
			return { success, input };

		return { success, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n
