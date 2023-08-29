#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticString> class Basic, StaticString str, IsConst<std::size_t> N>
struct Join<Exactly<Basic<str>, N>>
{
	using result_type = Input;

	static constexpr ParserType type = JoinType;

	static constexpr Result<result_type> parse(Input input)
	{
		using Traits = BasicTraits<Basic<str>>;

		const Input original_input = input;
		Input result = { input.data(), 0 };

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return { failure, original_input };
			result = { result.data(), result.size() + Traits::length };
			input.remove_prefix(Traits::length);
		}

		return { success, result, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		using Traits = BasicTraits<Basic<str>>;

		const Input original_input = input;

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return { failure, original_input };
			input.remove_prefix(Traits::length);
		}

		return { success, input };
	}
};

} // namespace k3::tok3n