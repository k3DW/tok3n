#pragma once
#include "tok3n/utilities/meta.h"
#include "tok3n/utilities/static_string.h"
#include "tok3n/types/Input.h"

#include <array>
#include <optional>
#include <utility>
#include <vector>

TOK3N_BEGIN_NAMESPACE(detail)



template <class P>
concept void_result = std::same_as<typename P::result_type, void>;



template <static_string str> concept Literal_able    = is_ascii(str) && str.size() != 0;
template <static_string str> concept SingleChar_able = is_ascii(str) && str.size() != 0 && is_unique_and_sorted(str);

template <class... Ps> concept Choice_able   = (sizeof...(Ps) >= 2) && mp::all_same<typename Ps::result_type...>;
template <class... Ps> using   Choice_result = typename mp::head<Ps...>::result_type;

template <class... Ps> concept Sequence_able         = sizeof...(Ps) >= 2;
template <class... Ps> using   Sequence_result_trait = mp::unwrap_if_single<mp::filter<mp::is_not_type<void>, std::tuple, typename Ps::result_type...>>;

template <class P> concept OneOrMore_able  = not void_result<P>;
template <class P> concept ZeroOrMore_able = not void_result<P>;
template <class P> concept Maybe_able      = not void_result<P>;

template <class P, std::size_t N>
concept Exactly_able = (N != 0) && not void_result<P>;

template <class P, auto function> concept Transform_able   = std::invocable<decltype(function), typename P::result_type&&>;
template <class P, auto function> using   Transform_result = std::invoke_result_t<decltype(function), typename P::result_type&&>;



template <class T> constexpr bool is_joinable_v          = false;
template <class T> constexpr bool is_joinable_v<const T> = is_joinable_v<T>;
template <class T> constexpr bool is_joinable_v<T&>      = is_joinable_v<T>;
template <class T> constexpr bool is_joinable_v<T&&>     = is_joinable_v<T>;

template <>                       constexpr bool is_joinable_v<Input>             = true;
template <class T, std::size_t N> constexpr bool is_joinable_v<std::array<T, N>>  = is_joinable_v<T>;
template <class T>                constexpr bool is_joinable_v<std::vector<T>>    = is_joinable_v<T>;
template <class T>                constexpr bool is_joinable_v<std::optional<T>>  = is_joinable_v<T>;
template <class... Ts>            constexpr bool is_joinable_v<std::tuple<Ts...>> = (... && is_joinable_v<Ts>);

template <class P>
concept Join_able = is_joinable_v<typename P::result_type>;



template <class P, class Delimiter>
concept Delimit_able = not std::same_as<typename P::result_type, void>;



template <class P, class T>
concept Into_able = not void_result<P> && requires { T(std::declval<typename P::result_type>()); };

template <class T>
concept HasTupleSize = requires { std::tuple_size<T>{}; } && (std::tuple_size_v<T> > 0);

template <class P, class T>
concept ApplyInto_able = HasTupleSize<typename P::result_type> && requires { std::make_from_tuple<T>(std::declval<typename P::result_type>()); };

template <class P, auto function>
concept ApplyTransform_able = HasTupleSize<typename P::result_type> && requires { std::apply(function, std::declval<typename P::result_type>()); };

template <class P, auto function>
requires ApplyTransform_able<P, function>
using ApplyTransform_result = decltype(std::apply(function, std::declval<typename P::result_type>()));



TOK3N_END_NAMESPACE(detail)
