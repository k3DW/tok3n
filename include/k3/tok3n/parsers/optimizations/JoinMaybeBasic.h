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
	using result_type = Output<value_type>;

	static constexpr ParserFamily family = JoinFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return parse<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input)
	{
		using Traits = BasicTraits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return { success, { input.data(), 0 }, input };

		return { success, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return lookahead<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
	{
		using Traits = BasicTraits<Basic<arr>>;

		if (Traits::failure_condition(input))
			return { success, input };

		return { success, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n
