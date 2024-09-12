#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <utility>
#include <vector>

namespace k3::tok3n {

template <detail::parser P, detail::parser_compatible_with<P> D, detail::integral_constant_of<bool> KeepDelimiters>
struct Delimit
{
	using value_type = typename P::value_type;

	template <detail::input_constructible_for<value_type> R, class V = detail::input_value_t<R>>
	static constexpr bool parsable_range =
		not std::same_as<typename P::template result_for<V>, void>
		and (not std::same_as<typename D::template result_for<V>, void> or not KeepDelimiters::value);

	template <detail::equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<KeepDelimiters::value,
		std::pair<std::vector<typename P::template result_for<V>>, std::vector<typename D::template result_for<V>>>,
		std::vector<typename P::template result_for<V>>
	>;

	static constexpr detail::parser_family family = detail::delimit_family;

	template <detail::input_constructible_for<value_type> R>
	requires (not KeepDelimiters::value) and parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		result_for<V> results;

		auto res = P::parse(input);
		if (not res.has_value())
			return detail::result<result_for<V>, V>{ detail::failure_tag, input };

		while (res)
		{
			input = res.remaining();
			results.emplace_back(std::move(*res));

			auto delimit_result = D::parse(input);
			if (not delimit_result)
				break;

			res = P::parse(delimit_result.remaining());
		}

		return detail::result<result_for<V>, V>{ detail::success_tag, std::move(results), input };
	}

	template <detail::input_constructible_for<value_type> R>
	requires (KeepDelimiters::value) and parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		result_for<V> results;
		auto& [values, delimiters] = results;

		auto res = P::parse(input);
		if (not res.has_value())
			return detail::result<result_for<V>, V>{ detail::failure_tag, input };

		while (res)
		{
			input = res.remaining();
			values.emplace_back(std::move(*res));

			auto delimit_result = D::parse(input);
			if (not delimit_result)
				break;

			res = P::parse(delimit_result.remaining());
			if (res)
				delimiters.emplace_back(std::move(*delimit_result));
		}

		return detail::result<result_for<V>, V>{ detail::success_tag, std::move(results), input };
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		auto res = P::lookahead(input);
		if (not res.has_value())
			return detail::result<void, V>{ detail::failure_tag, input };

		while (res)
		{
			input = res.remaining();

			auto delimit_result = D::lookahead(input);
			if (not delimit_result)
				break;

			res = P::lookahead(delimit_result.remaining());
		}

		return detail::result<void, V>{ detail::success_tag, input };
	}
};

} // namespace k3::tok3n
