#pragma once
#include <tok3n/concepts/Parser.h>
#include <array>
#include <vector>
#include <optional>
#include <tuple>

TOK3N_BEGIN_NAMESPACE(constructible)

namespace detail
{

	template <class T> constexpr bool is_joinable_v        = false;
	template <>        constexpr bool is_joinable_v<Input> = true;

	template <class T> constexpr bool is_joinable_v<const T> = is_joinable_v<T>;
	template <class T> constexpr bool is_joinable_v<T&>      = is_joinable_v<T>;
	template <class T> constexpr bool is_joinable_v<T&&>     = is_joinable_v<T>;

	template <class T, std::size_t N> constexpr bool is_joinable_v<std::array<T, N>>  = is_joinable_v<T>;
	template <class T>                constexpr bool is_joinable_v<std::vector<T>>    = is_joinable_v<T>;
	template <class T>                constexpr bool is_joinable_v<std::optional<T>>  = is_joinable_v<T>;
	template <class... Ts>            constexpr bool is_joinable_v<std::tuple<Ts...>> = (... && is_joinable_v<Ts>);

}

template <class P>
concept Join =
	Parser<P> and
	detail::is_joinable_v<typename P::result_type>;



namespace detail
{

	template <class T>
	concept has_tuple_size = requires { std::tuple_size<T>{}; } && (std::tuple_size_v<T> > 0);

}

template <class P, auto function>
concept Transform =
	Parser<P> and
	requires { std::invoke(function, std::declval<typename P::result_type>()); };

template <class P, auto function>
concept ApplyTransform =
	Parser<P> and
	detail::has_tuple_size<typename P::result_type> and
	requires { std::apply(function, std::declval<typename P::result_type>()); };

template <class P, class T>
concept Into =
	Parser<P> and
	not std::same_as<typename P::result_type, void> and
	requires { T(std::declval<typename P::result_type>()); };

template <class P, class T>
concept ApplyInto =
	Parser<P> and
	detail::has_tuple_size<typename P::result_type> and
	requires { std::make_from_tuple<T>(std::declval<typename P::result_type>()); };

TOK3N_END_NAMESPACE(constructible)
