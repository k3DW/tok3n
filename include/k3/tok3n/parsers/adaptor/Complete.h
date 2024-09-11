#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/detail/parser.h>

namespace k3::tok3n {

template <detail::parser P>
struct Complete
{
	using value_type = typename P::value_type;
	
	template <detail::equality_comparable_with<value_type> V>
	using result_for = typename P::template result_for<V>;

	static constexpr detail::parser_family family = detail::complete_family;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		auto result = P::parse(input);
		if (not result.has_value() or not result.remaining().empty())
			return Result<result_for<V>, V>{ failure, input };
		else
			return result;
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		auto result = P::lookahead(input);
		if (not result.has_value() or not result.remaining().empty())
			return Result<void, V>{ failure, input };
		else
			return result;
	}
};

} // namespace k3::tok3n
