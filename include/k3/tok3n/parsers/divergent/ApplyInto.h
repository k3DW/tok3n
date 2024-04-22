#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, class T>
struct ApplyInto
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = T;

	static constexpr ParserFamily family = ApplyIntoFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		static_assert(detail::has_tuple_size<typename P::template result_for<value_type>>,
			"ApplyInto's child parser's result type for the given value must have tuple_size.");
		static_assert(requires { std::make_from_tuple<T>(std::declval<typename P::template result_for<value_type>>()); },
			"ApplyInto's \"into type\" must be constructible from tuple from the child parser's result type for the given value.");

		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::make_from_tuple<result_for<value_type>>(std::move(*result)), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		static_assert(detail::has_tuple_size<typename P::template result_for<value_type>>,
			"ApplyInto's child parser's result type for the given value must have tuple_size.");
		static_assert(requires { std::make_from_tuple<T>(std::declval<typename P::template result_for<value_type>>()); },
			"ApplyInto's \"into type\" must be constructible from tuple from the child parser's result type for the given value.");
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
