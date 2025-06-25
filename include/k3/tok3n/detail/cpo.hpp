// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_CPO_HPP
#define K3_TOK3N_DETAIL_CPO_HPP

#include <k3/tok3n/detail/type_traits.hpp>

namespace k3::tok3n::detail {

template <class T>
concept span_like = requires (T& t, const T& ct)
	{
		typename T::value_type;
		{ ct.data() } -> pointer_of<typename T::value_type>; // `data()` could return a pointer-to-const or pointer-to-non-const
		{ ct.size() } -> std::same_as<std::size_t>;
		{ ct.empty() } -> std::same_as<bool>;
		t = T{};
		t = T{ ct.data(), ct.size() };
	};

template <class T>
concept indexable = requires (T t, std::size_t i)
	{
		// `static_cast<T>(t)` acts like `std::forward` when `T` is a reference type,
		// but it's a no-op when `T` is not a reference type
		requires
			requires { static_cast<T>(t).at(i); }
			or requires { static_cast<T>(t)[i]; };
	};

template <indexable T>
constexpr decltype(auto) index(T&& t, const std::size_t i)
{
	// Prefer checked indexing when available
	if constexpr (requires { std::forward<T>(t).at(i); })
		return std::forward<T>(t).at(i);
	else
		return std::forward<T>(t)[i];
}

template <class T, class Element>
concept pushable = requires (T& t, Element element)
	{
		// `static_cast<Element>(element)` acts like `std::forward` when `Element` is a reference type,
		// but it's a no-op when `Element` is not a reference type
		requires
			requires { t.push_back(static_cast<Element>(element)); }
			or requires { t.push(static_cast<Element>(element)); }
			or requires { t.insert(static_cast<Element>(element)); };
	};

template <class Element, pushable<Element&&> T>
constexpr decltype(auto) push(T& t, Element&& element)
{
	// Prefer `push_back` if available, then `push`, then `insert`
	if constexpr (requires { t.push_back(std::forward<Element>(element)); })
		return t.push_back(std::forward<Element>(element));
	else if constexpr (requires { t.push(std::forward<Element>(element)); })
		return t.push(std::forward<Element>(element));
	else
		return t.insert(std::forward<Element>(element));
}

template <class T, std::size_t I>
concept gettable = requires (T t)
	{
		// `static_cast<T>(t)` acts like `std::forward` when `T` is a reference type,
		// but it's a no-op when `T` is not a reference type
		[]<class T_>(T_&& t_) {
			using std::get;
			(void)get<I>(std::forward<T_>(t_));
		}(static_cast<T>(t));
	};

template <std::size_t I, gettable<I> T>
constexpr decltype(auto) adl_get(T&& t)
{
	using std::get;
	return get<I>(std::forward<T>(t));
}

template <class T, class U, std::size_t I>
concept emplaceable = requires (T& t, U u) { t.template emplace<I>(static_cast<U>(u)); };

template <std::size_t I, class U, emplaceable<U, I> T>
constexpr decltype(auto) emplace(T& t, U&& u)
{
	return t.template emplace<I>(std::forward<U>(u));
}

template <class T, class Visitor>
concept visitable = requires (T t, Visitor visitor)
	{
		// `static_cast<T>(t)` acts like `std::forward` when `T` is a reference type,
		// but it's a no-op when `T` is not a reference type
		requires
			requires { static_cast<T>(t).visit(static_cast<Visitor>(visitor)); }
			or requires { std::visit(static_cast<Visitor>(visitor), static_cast<T>(t)); };
	};

template <class Visitor, visitable<Visitor&&> T>
constexpr decltype(auto) visit(T&& t, Visitor&& visitor)
{
	// Prefer member `visit` if available, otherwise `std::visit`
	if constexpr (requires { std::forward<T>(t).visit(std::forward<Visitor>(visitor)); })
		return std::forward<T>(t).visit(std::forward<Visitor>(visitor));
	else
		return std::visit(std::forward<Visitor>(visitor), std::forward<T>(t));
}

template <class T, std::size_t I>
using adl_get_t = decltype(adl_get<I>(std::declval<T>()));

template <class T>
concept optional_like = requires (T& t, const T& ct)
	{
		typename T::value_type;
		{ *t } -> std::same_as<typename T::value_type&>;
		{ *ct } -> std::same_as<const typename T::value_type&>;
		{ ct.has_value() } -> std::same_as<bool>;
	};

template <class T>
concept tuple_like = requires (const T& ct)
	{
		std::tuple_size<T>{};
		std::tuple_size<T>::value;
		requires std::tuple_size_v<T> != 0;
		[]<std::size_t... Is>(const T& ct_, std::index_sequence<Is...>) {
			(..., adl_get<Is>(ct_));
		}(ct, std::make_index_sequence<std::tuple_size_v<T>>{});
	};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_CPO_HPP
