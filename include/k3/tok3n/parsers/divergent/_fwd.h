#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/detail/has_tuple_size.h>
#include <vector>

namespace k3::tok3n {

namespace detail {

	template <class T> constexpr bool is_joinable_v            = false;
	template <class U> constexpr bool is_joinable_v<Output<U>> = true;

	template <class T> constexpr bool is_joinable_v<const T> = is_joinable_v<T>;
	template <class T> constexpr bool is_joinable_v<T&>      = is_joinable_v<T>;
	template <class T> constexpr bool is_joinable_v<T&&>     = is_joinable_v<T>;

	template <class T, std::size_t N> constexpr bool is_joinable_v<std::array<T, N>>  = is_joinable_v<T>;
	template <class T>                constexpr bool is_joinable_v<std::vector<T>>    = is_joinable_v<T>;
	template <class T>                constexpr bool is_joinable_v<std::optional<T>>  = is_joinable_v<T>;
	template <class... Ts>            constexpr bool is_joinable_v<std::tuple<Ts...>> = (... && is_joinable_v<Ts>);

} // namespace detail



namespace detail {

template <class F, class Tup>
struct ApplyTrait {};

template <class F, template <class...> class List, class... Ts>
requires detail::has_tuple_size<List<Ts...>> and std::invocable<F, Ts...>
struct ApplyTrait<F, List<Ts...>> : std::invoke_result<F, Ts...> {};

template <class F, class Tup>
using ApplyResult = typename ApplyTrait<F, Tup>::type;

template <class F, class Tup>
concept IsApplyable = requires { typename ApplyTrait<F, Tup>::type; };

} // namespace detail



template <Parser P>
struct Join;

template <Parser P, IsConst FunctionValue>
struct Map;

template <Parser P, IsConst FunctionValue>
struct ApplyTransform;

template <Parser P, class T>
struct ApplyInto;

template <class CRTP, class ValueType = char>
struct Custom;

} // namespace k3::tok3n
