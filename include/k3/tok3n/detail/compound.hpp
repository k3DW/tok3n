// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_COMPOUND_HPP
#define K3_TOK3N_DETAIL_COMPOUND_HPP

#include <k3/tok3n/detail/cpo.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>
#include <tuple>
#include <variant>

namespace k3::tok3n::detail {

namespace impl {

template <class list, template <class...> class Other>
struct change_list;

template <template <class...> class list, class... Ts, template <class...> class Other>
struct change_list<list<Ts...>, Other>
{
	using type = Other<Ts...>;
};

template <bool Value, class Type>
struct unwrap_if_single_trait
{
	static constexpr bool unwrapped = Value;
	using type = Type;
};

template <template <class...> class List>
consteval auto unwrap_if_single(List<>) -> unwrap_if_single_trait<true, void>;

template <template <class...> class List, class T>
consteval auto unwrap_if_single(List<T>) -> unwrap_if_single_trait<true, T>;

template <template <class...> class List, class... Ts>
consteval auto unwrap_if_single(List<Ts...>) -> unwrap_if_single_trait<false, List<Ts...>>;

} // namespace impl

template <class List>
using unwrap_if_single = decltype(impl::unwrap_if_single(List{}));

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

namespace impl {

template <bool unwrapped, class P, class V, class Out>
concept compound_executable_unwrapped = unwrapped
	and parsable_into<P, input_span<V>&, Out>;

template <compound_type type, std::size_t I, class Out>
concept choice_element_constraints = (type == compound_type::choice)
	and emplaceable<Out, std::remove_reference_t<get_t<Out&, I>>&&, I>;

template <compound_type type, std::size_t I, class Out>
concept sequence_element_constraints = (type == compound_type::sequence)
	and std::is_move_assignable_v<std::remove_reference_t<get_t<Out&, I>>>;

template <bool unwrapped, compound_type type, std::size_t I, class P, class V, class Out>
concept compound_executable_element = not unwrapped
	and gettable<Out&, I>
	and parsable_into<P, input_span<V>&, get_t<Out&, I>>
	and
	(
		choice_element_constraints<type, I, Out>
		or sequence_element_constraints<type, I, Out>
	);

template <bool unwrapped, compound_type type, std::size_t I, class P, class V, class... Out>
concept compound_executable = (I == static_cast<std::size_t>(-1))
	or impl::compound_executable_unwrapped<unwrapped, P, V, typename std::type_identity<Out...>::type>
	or impl::compound_executable_element<unwrapped, type, I, P, V, typename std::type_identity<Out...>::type>;

} // namespace impl

template <class V, bool unwrapped, class Call, compound_type type>
struct compound_executor
{
	input_span<V> input;

	template <std::size_t I, parser P>
	requires (I == static_cast<std::size_t>(-1))
	constexpr bool exec(P, auto&...)
	{
		static_assert(Call::kind == call_kind::lookahead || std::same_as<void, typename P::template result_for<V>>);
		constexpr auto call = std::conditional_t<Call::kind == call_kind::parse_into, decltype(call_parse), Call>{};
		const result<void, V> res = call(P{}, input);
		input = res.remaining();
		return res.has_value();
	}

	template <std::size_t I, parser P, class Out>
	requires (I != static_cast<std::size_t>(-1))
		and impl::compound_executable<unwrapped, type, I, P, V, Out>
	constexpr bool exec(P, Out& out)
	{
		static_assert(Call::kind == call_kind::parse_into);
		if constexpr (unwrapped)
			return exec_unwrapped(P{}, out);
		else
			return exec_element<I>(P{}, out);
	}

private:
	template <parser P, class Out>
	requires impl::compound_executable_unwrapped<unwrapped, P, V, Out>
	constexpr bool exec_unwrapped(P, Out& out)
	{
		const result<void, V> res = Call{}(P{}, input, out);
		input = res.remaining();
		return res.has_value();
	}

	template <std::size_t I, parser P, class Out>
	requires impl::compound_executable_element<unwrapped, type, I, P, V, Out>
	constexpr bool exec_element(P, Out& out)
	{
		using element_type = std::remove_reference_t<get_t<Out&, I>>;
		element_type element;
		const result<void, V> res = Call{}(P{}, input, element);
		input = res.remaining();
		if (res.has_value())
		{
			if constexpr (type == compound_type::choice)
				emplace<I>(out, std::move(element));
			else if constexpr (type == compound_type::sequence)
				get_<I>(out) = std::move(element);
			else
				static_assert(std::same_as<V, void>, "Unreachable"); // Always false
		}
		return res.has_value();
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_COMPOUND_HPP
