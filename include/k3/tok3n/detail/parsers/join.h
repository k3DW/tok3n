// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <array>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

namespace k3::tok3n::detail {

namespace impl {

template <class ValueType>
class join_executor
{
public:
	template <class T>
	constexpr join_executor(const result<T, ValueType>& t)
	{
		if (this->try_join(*t) && joined == std::nullopt)
		{
			// If the contents are empty, make sure this result is still contiguous
			joined = { t.remaining().data(), 0ull };
		}
	}

	constexpr std::optional<output_span<ValueType>> get_joined() const
	{
		return joined;
	}

private:
	// This is the fundamental function of this class,
	// where we check if the next string_view is adjacent in memory to the last one.
	constexpr bool try_join(output_span<ValueType> output)
	{
		if (output.empty())
		{
			return true;
		}
		else if (!joined)
		{
			joined = output;
			return true;
		}
#if defined(_MSC_VER)
		else if (joined->data() + joined->size() == output.data())
#elif defined(__GNUC__) || defined(__clang__)
		else if
		(
			(
				not std::is_constant_evaluated() or
				__builtin_constant_p(output.data() - joined->data())
			) and
			static_cast<std::ptrdiff_t>(joined->size()) == output.data() - joined->data()
		)
#else
#error
#endif
		{
			// ^^ If (&joined->back() + 1 == &output.front())
			*joined = { joined->data(), joined->size() + output.size() };
			return true;
		}
		else
		{
			joined = std::nullopt;
			return false;
		}
	}

	template <class T>
	constexpr bool try_join(const std::vector<T>& ts)
	{
		for (auto& t : ts)
		{
			if (not this->try_join(t))
				return false;
		}
		return true;
	}

	template <class T, std::size_t N>
	constexpr bool try_join(const std::array<T, N>& arr)
	{
		for (auto& t : arr)
		{
			if (not this->try_join(t))
				return false;
		}
		return true;
	}

	template <class T>
	constexpr bool try_join(const std::optional<T>& opt)
	{
		return (not opt.has_value()) || this->try_join(*opt);
	}

	template <class T, class... Ts>
	constexpr bool try_join(const std::tuple<T, Ts...>& tup)
	{
		return[this, &tup]<std::size_t... Is>(std::index_sequence<Is...>) -> bool
		{
			return (... && this->try_join(std::get<Is>(tup)));
		}(std::index_sequence_for<T, Ts...>{});
	}

	std::optional<output_span<ValueType>> joined;
};

} // namespace impl

template <parser P>
struct join_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = output_span<V>;

	static constexpr parser_family family = join_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		auto res = P::parse(input);
		if (res.has_value())
		{
			using Executor = impl::join_executor<V>;
			std::optional<output_span<V>> joined = Executor(res).get_joined();
			if (joined)
				return result<result_for<V>, V>{ success_tag, std::move(*joined), res.remaining() };
		}
		return result<result_for<V>, V>{ failure_tag, input };
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n::detail
