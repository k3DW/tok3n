#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>

namespace k3::tok3n {

template <class P>
struct BasicTraits
{
	// using value_type;
	// static constexpr std::size_t length;
	// static constexpr bool failure_condition(detail::input_span<value_type>);
};

template <class P>
struct BasicBase
{
	using value_type = typename BasicTraits<P>::value_type;
	
	template <detail::equality_comparable_with<value_type> V>
    using result_for = detail::output_span<V>;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		using Traits = BasicTraits<P>;
		if (Traits::failure_condition(input))
			return Result<result_for<V>, V>{ failure, input };
		else
			return Result<result_for<V>, V>{ success, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		using Traits = BasicTraits<P>;
		if (Traits::failure_condition(input))
			return Result<void, V>{ failure, input };
		else
			return Result<void, V>{ success, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace k3::tok3n
