#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, ParserCompatibleWith<P> D, IsConst<bool> KeepDelimiters>
struct Delimit
{
	using value_type = typename P::value_type;

	template <InputConstructibleFor<value_type> R, class V = typename decltype(Input{ std::declval<R>() })::value_type>
	static constexpr bool parsable_range =
		not std::same_as<typename P::template result_for<V>, void>
		and (not std::same_as<typename D::template result_for<V>, void> or not KeepDelimiters::value);

	template <EqualityComparableWith<value_type> V>
	using result_for = std::conditional_t<KeepDelimiters::value,
		std::pair<std::vector<typename P::template result_for<V>>, std::vector<typename D::template result_for<V>>>,
		std::vector<typename P::template result_for<V>>
	>;

	static constexpr ParserFamily family = DelimitFamily;

	template <InputConstructibleFor<value_type> R>
	requires (not KeepDelimiters::value) and parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		result_for<V> results;

		auto result = P::parse(input);
		if (not result.has_value())
			return Result<result_for<V>, V>{ failure, input };

		while (result)
		{
			input = result.remaining();
			results.emplace_back(std::move(*result));

			auto delimit_result = D::parse(input);
			if (not delimit_result)
				break;

			result = P::parse(delimit_result.remaining());
		}

		return Result<result_for<V>, V>{ success, std::move(results), input };
	}

	template <InputConstructibleFor<value_type> R>
	requires (KeepDelimiters::value) and parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		result_for<V> results;
		auto& [values, delimiters] = results;

		auto result = P::parse(input);
		if (not result.has_value())
			return Result<result_for<V>, V>{ failure, input };

		while (result)
		{
			input = result.remaining();
			values.emplace_back(std::move(*result));

			auto delimit_result = D::parse(input);
			if (not delimit_result)
				break;

			result = P::parse(delimit_result.remaining());
			if (result)
				delimiters.emplace_back(std::move(*delimit_result));
		}

		return Result<result_for<V>, V>{ success, std::move(results), input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		auto result = P::lookahead(input);
		if (not result.has_value())
			return Result<void, V>{ failure, input };

		while (result)
		{
			input = result.remaining();

			auto delimit_result = D::lookahead(input);
			if (not delimit_result)
				break;

			result = P::lookahead(delimit_result.remaining());
		}

		return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
