#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <detail::parser P>
struct Maybe
{
	using value_type = typename P::value_type;

	template <detail::equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::optional<typename P::template result_for<V>>
	>;

	static constexpr detail::parser_family family = detail::maybe_family;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		detail::ResultBuilder<result_for<V>> builder;

		auto result = P::parse(input);
		if (result.has_value())
			builder.emplace(std::move(result));

		return std::move(builder).success(result.remaining());
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		auto result = P::lookahead(input);
		if (result.has_value())
			return Result<void, V>{ success, result.remaining() };
		else
			return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
