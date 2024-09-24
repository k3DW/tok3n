#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <functional>

namespace k3::tok3n::detail {

template <parser P, is_integral_constant FunctionValue>
struct filter_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	requires (
		std::same_as<void, typename P::template result_for<V>>
		? requires { { std::invoke(FunctionValue::value) } -> std::convertible_to<bool>; }
		: requires (const typename P::template result_for<V>& res) { { std::invoke(FunctionValue::value, res) } -> std::convertible_to<bool>; }
	)
	using result_for = typename P::template result_for<V>;

	static constexpr parser_family family = filter_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		auto res = P::parse(input);
		if (not res.has_value())
			return result<result_for<V>, V>{ failure_tag, input };
        
        if constexpr (std::same_as<void, result_for<V>>)
        {
            static_assert(requires { { std::invoke(FunctionValue::value) } -> std::convertible_to<bool>; });
            if (std::invoke(FunctionValue::value))
                return std::move(res);
            else
                return result<result_for<V>, V>{ failure_tag, input };
        }
        else
        {
            static_assert(requires { { std::invoke(FunctionValue::value, std::as_const(*res)) } -> std::convertible_to<bool>; });
            if (std::invoke(FunctionValue::value, std::as_const(*res)))
                return std::move(res);
            else
                return result<result_for<V>, V>{ failure_tag, input };
        }
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n::detail
