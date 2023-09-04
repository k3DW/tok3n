#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/detail/has_tuple_size.h>
#include <vector>

namespace k3::tok3n {

namespace detail
{

	template <class T> constexpr bool is_joinable_v         = false;
	template <>        constexpr bool is_joinable_v<Output> = true;

	template <class T> constexpr bool is_joinable_v<const T> = is_joinable_v<T>;
	template <class T> constexpr bool is_joinable_v<T&>      = is_joinable_v<T>;
	template <class T> constexpr bool is_joinable_v<T&&>     = is_joinable_v<T>;

	template <class T, std::size_t N> constexpr bool is_joinable_v<std::array<T, N>>  = is_joinable_v<T>;
	template <class T>                constexpr bool is_joinable_v<std::vector<T>>    = is_joinable_v<T>;
	template <class T>                constexpr bool is_joinable_v<std::optional<T>>  = is_joinable_v<T>;
	template <class... Ts>            constexpr bool is_joinable_v<std::tuple<Ts...>> = (... && is_joinable_v<Ts>);

}

template <class P>
concept JoinConstructible =
	Parser<P> and
	detail::is_joinable_v<typename P::result_type>;

template <class P, class FunctionValue>
concept TransformConstructible =
	Parser<P> and
	IsConst<FunctionValue> and
	requires { std::invoke(FunctionValue::value, std::declval<typename P::result_type>()); };

template <class P, class FunctionValue>
concept ApplyTransformConstructible =
	Parser<P> and
	detail::has_tuple_size<typename P::result_type> and
	IsConst<FunctionValue> and
	requires { std::apply(FunctionValue::value, std::declval<typename P::result_type>()); };

template <class P, class T>
concept IntoConstructible =
	Parser<P> and
	not std::same_as<typename P::result_type, void> and
	requires { T(std::declval<typename P::result_type>()); };

template <class P, class T>
concept ApplyIntoConstructible =
	Parser<P> and
	detail::has_tuple_size<typename P::result_type> and
	requires { std::make_from_tuple<T>(std::declval<typename P::result_type>()); };

template <class P, class T>
concept DefaultedConstructible =
	Parser<P> and
	std::is_default_constructible_v<T>;



template <Parser P>
requires JoinConstructible<P>
struct Join;

template <Parser P, IsConst FunctionValue>
requires TransformConstructible<P, FunctionValue>
struct Transform;

template <Parser P, IsConst FunctionValue>
requires ApplyTransformConstructible<P, FunctionValue>
struct ApplyTransform;

template <Parser P, class T>
requires IntoConstructible<P, T>
struct Into;

template <Parser P, class T>
requires ApplyIntoConstructible<P, T>
struct ApplyInto;

template <Parser P, IsConst Value>
struct Constant;

template <Parser P, class T>
requires DefaultedConstructible<P, T>
struct Defaulted;

template <class CRTP>
struct Custom;

} // namespace k3::tok3n
