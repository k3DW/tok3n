// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_CPO_HPP
#define K3_TOK3N_DETAIL_CPO_HPP

#include <k3/tok3n/detail/type_traits.hpp>

namespace k3::tok3n::detail {

template <class T, std::size_t I>
concept gettable =  std::is_reference_v<T> and
    requires (T t)
	{
		requires
			requires { std::get<I>(static_cast<T>(t)); }
			or requires { get<I>(static_cast<T>(t)); };
	};

namespace impl {

template <std::size_t I>
struct get_cpo {
    explicit constexpr get_cpo() = default;
    template <class T>
    requires gettable<T&&, I>
    constexpr decltype(auto) operator()(T&& t) const
    {
        // Prefer std::get over ADL get
        if constexpr (requires { std::get<I>(std::forward<T>(t)); })
            return std::get<I>(std::forward<T>(t));
        else
            return get<I>(std::forward<T>(t));
    }
};

} // namespace impl

template <std::size_t I>
inline constexpr impl::get_cpo<I> get_{};

template <class T, std::size_t I>
requires gettable<T, I>
using get_t = std::invoke_result_t<impl::get_cpo<I>, T>;



template <class T>
concept span_like = requires (std::remove_cvref_t<T>& t, const std::remove_cvref_t<T>& ct)
	{
		typename std::remove_cvref_t<T>::value_type;
		{ ct.data() } -> pointer_of<typename std::remove_cvref_t<T>::value_type>; // `data()` could return a pointer-to-const or pointer-to-non-const
		{ ct.size() } -> std::same_as<std::size_t>;
		{ ct.empty() } -> std::same_as<bool>;
		t = std::remove_cvref_t<T>{};
		t = std::remove_cvref_t<T>{ ct.data(), ct.size() };
	};

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
			(..., get_<Is>(ct_));
		}(ct, std::make_index_sequence<std::tuple_size_v<T>>{});
	};



template <class T>
concept indexable = std::is_reference_v<T> and
    requires (T t, std::size_t i)
	{
		requires
			requires { static_cast<T>(t).at(i); }
			or requires { static_cast<T>(t)[i]; };
	};

namespace impl {

struct index_cpo {
    explicit constexpr index_cpo() = default;
    template <class T>
    requires indexable<T&&>
    constexpr decltype(auto) operator()(T&& t, const std::size_t i) const
    {
        // Prefer checked indexing when available
        if constexpr (requires { std::forward<T>(t).at(i); })
            return std::forward<T>(t).at(i);
        else
            return std::forward<T>(t)[i];
    }
};

} // namespace impl

inline constexpr impl::index_cpo index{};

template <indexable T>
using index_t = std::invoke_result_t<impl::index_cpo, T, std::size_t>;



template <class T, class Element>
concept pushable = std::is_reference_v<Element> and
    requires (T t, Element element)
	{
		requires
			requires { t.push_back(static_cast<Element>(element)); }
			or requires { t.push(static_cast<Element>(element)); }
			or requires { t.insert(static_cast<Element>(element)); };
	};

namespace impl {

struct push_cpo {
    explicit constexpr push_cpo() = default;
    template <class Element, pushable<Element&&> T>
    constexpr decltype(auto) operator()(T& t, Element&& element) const
    {
        // Prefer `push_back` if available, then `push`, then `insert`
        if constexpr (requires { t.push_back(std::forward<Element>(element)); })
            return t.push_back(std::forward<Element>(element));
        else if constexpr (requires { t.push(std::forward<Element>(element)); })
            return t.push(std::forward<Element>(element));
        else
            return t.insert(std::forward<Element>(element));
    }
};

} // namespace impl

inline constexpr impl::push_cpo push{};



template <class T, class U, std::size_t I>
concept emplaceable = std::is_reference_v<U> and
    requires (T t, U u)
	{
		t.template emplace<I>(static_cast<U>(u));
	};

namespace impl {

template <std::size_t I>
struct emplace_cpo {
    explicit constexpr emplace_cpo() = default;
    template <class T, class U>
    requires emplaceable<T, U&&, I>
    constexpr decltype(auto) operator()(T& t, U&& u) const
    {
        return t.template emplace<I>(std::forward<U>(u));
    }
};

} // namespace impl

template <std::size_t I>
inline constexpr impl::emplace_cpo<I> emplace{};



template <class T, class Visitor>
concept visitable = std::is_reference_v<T> and
    std::is_reference_v<Visitor> and
    requires (T t, Visitor visitor)
	{
        // Prefer member `visit` if available, otherwise `std::visit`
		requires
			requires { static_cast<T>(t).visit(static_cast<Visitor>(visitor)); }
			or requires { std::visit(static_cast<Visitor>(visitor), static_cast<T>(t)); };
	};

namespace impl {

struct visit_cpo {
    explicit constexpr visit_cpo() = default;
    template <class T, class Visitor>
    requires visitable<T&&, Visitor&&>
    constexpr decltype(auto) operator()(T&& t, Visitor&& visitor) const
    {
        // Prefer member `visit` if available, otherwise `std::visit`
        if constexpr (requires { std::forward<T>(t).visit(std::forward<Visitor>(visitor)); })
            return std::forward<T>(t).visit(std::forward<Visitor>(visitor));
        else
            return std::visit(std::forward<Visitor>(visitor), std::forward<T>(t));
    }
};

} // namespace impl

inline constexpr impl::visit_cpo visit{};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_CPO_HPP
