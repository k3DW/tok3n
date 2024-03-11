#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
struct Maybe
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::optional<typename P::template result_for<V>>;

	static constexpr ParserFamily family = MaybeFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"Maybe's child parser's result for the given value cannot be void.");

		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::move(*result), result.remaining() };
		else
			return { success, result_for<value_type>{ std::nullopt }, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"Maybe's child parser's result for the given value cannot be void.");

		auto result = P::lookahead(input);
		if (result.has_value())
			return { success, result.remaining() };
		else
			return { success, input };
	}
};

} // namespace k3::tok3n
