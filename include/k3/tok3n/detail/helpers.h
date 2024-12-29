// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <tuple>
#include <variant>

namespace k3::tok3n::detail {

template <class T>
struct empty_if_void
{
    T value{};
};
template <>
struct empty_if_void<void> {};

template <class T>
class result_builder : empty_if_void<T>
{
	static constexpr bool is_void = std::same_as<T, void>;

public:
	constexpr result_builder() = default;

	template <class U>
	constexpr void assign(result<T, U>&& res)
	{
		if constexpr (not is_void)
			this->value = *std::move(res);
	}

	template <class U>
	constexpr void assign(const result<T, U>& res)
	{
		if constexpr (not is_void)
			this->value = *res;
	}

	template <class T2, class U>
	constexpr void array_assign(std::size_t index, result<T2, U>&& res)
	{
		if constexpr (not is_void)
			this->value[index] = *std::move(res);
	}

	template <std::size_t I, class T2, class U>
	constexpr void get_assign(result<T2, U>&& res)
	{
		if constexpr (not is_void)
			std::get<I>(this->value) = *std::move(res);
	}

	template <class T2, class U>
	constexpr void emplace(result<T2, U>&& res)
	{
		if constexpr (not is_void)
			this->value.emplace(*std::move(res));
	}

	template <std::size_t I, class T2, class U>
	constexpr void emplace(result<T2, U>&& res)
	{
		if constexpr (not is_void)
			this->value.template emplace<I>(*std::move(res));
	}

	template <class T2, class U>
    constexpr void insert_back(result<T2, U>&& res)
    {
        if constexpr (not is_void)
            this->value.insert(this->value.end(), *std::move(res));
    }

	template <class T2, class U>
	constexpr void insert_back_first(result<T2, U>&& res)
	{
		if constexpr (not is_void)
            this->value.first.insert(this->value.first.end(), *std::move(res));
	}

	template <class T2, class U>
	constexpr void insert_back_second(result<T2, U>&& res)
	{
		if constexpr (not is_void)
            this->value.second.insert(this->value.second.end(), *std::move(res));
	}

	template <class U>
	constexpr result<T, U> build(input_span<U> input) &&
	{
		if constexpr (not is_void)
			return { success_tag, std::move(this->value), input };
		else
			return { success_tag, input };
	}
};



enum class call_kind
{
	parse,
	parse_into,
	lookahead,
};

struct call_parse_t
{
	static constexpr call_kind kind = call_kind::parse;
	template <parser P, class R>
	constexpr auto operator()(P, R&& r) const
	{
		return P::parse(std::forward<R>(r));
	}
};
inline constexpr call_parse_t call_parse{};

struct call_parse_into_t
{
	static constexpr call_kind kind = call_kind::parse_into;
	template <parser P, class R, class Out>
	constexpr auto operator()(P, R&& r, Out& out) const
	{
		return P::parse(std::forward<R>(r), out);
	}
};
inline constexpr call_parse_into_t call_parse_into{};

struct call_lookahead_t
{
	static constexpr call_kind kind = call_kind::lookahead;
	template <parser P, class R>
	constexpr auto operator()(P, R&& r) const
	{
		return P::lookahead(std::forward<R>(r));
	}
};
inline constexpr call_lookahead_t call_lookahead{};



namespace impl {

template <class list, template <class...> class Other>
struct change_list;

template <template <class...> class list, class... Ts, template <class...> class Other>
struct change_list<list<Ts...>, Other>
{
	using type = Other<Ts...>;
};

} // namespace impl

template <template <class...> class algorithm, template <class...> class container, class V, parser... Ps>
struct compound_trait
{
private:
	using filtered = algorithm<typename Ps::template result_for<V>...>;

	using unwrapped_trait = unwrap_if_single<typename filtered::type>;

public:
	using sequence = typename filtered::sequence;

	static constexpr bool unwrapped = unwrapped_trait::unwrapped;

	using result_for =
		typename std::conditional_t<unwrapped,
			unwrapped_trait,
			impl::change_list<typename unwrapped_trait::type, container>
		>::type;
};

enum class compound_type
{
	choice,
	sequence,
};

template <class V, bool unwrapped, class Call, compound_type type>
struct compound_executor
{
	input_span<V> input;

	template <std::size_t I, parser P, class... Out>
	requires (sizeof...(Out) <= 1)
	constexpr bool exec(P, [[maybe_unused]] Out&... out)
	{
		constexpr auto call = Call{};

		if constexpr (I == static_cast<std::size_t>(-1))
		{
			static_assert(Call::kind == call_kind::lookahead || std::same_as<void, typename P::template result_for<V>>);
			constexpr auto inner_call = std::conditional_t<Call::kind == call_kind::parse_into, decltype(call_parse), Call>{};
			const result<void, V> res = inner_call(P{}, input);
			input = res.remaining();
			return res.has_value();
		}
		else if constexpr (unwrapped)
		{
			const result<void, V> res = call(P{}, input, out...);
			input = res.remaining();
			return res.has_value();
		}
		else
		{
			using element_type = std::remove_cvref_t<decltype(std::get<I>(out...))>;
			element_type element;
			const result<void, V> res = call(P{}, input, element);
			input = res.remaining();
			if (res.has_value())
			{
				if constexpr (type == compound_type::choice)
					(..., out.template emplace<I>(std::move(element)));
				else if constexpr (type == compound_type::sequence)
					(..., (std::get<I>(out) = std::move(element)));
				else
					static_assert(std::same_as<V, void>, "Unreachable"); // Always false
			}
			return res.has_value();
		}
	}
};

} // namespace k3::tok3n::detail
