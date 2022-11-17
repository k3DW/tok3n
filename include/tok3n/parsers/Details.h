#pragma once
#include "tok3n/utilities/meta.h"
#include "tok3n/utilities/static_string.h"

#include <array>
#include <optional>
#include <utility>
#include <vector>

TOK3N_BEGIN_NAMESPACE(detail)



using Input = std::string_view;

template <class P>
concept void_result = std::same_as<typename P::result_type, void>;



template <static_string str> concept Literal_able    = is_ascii(str) && str.size() != 0;
template <static_string str> concept SingleChar_able = is_ascii(str) && str.size() != 0 && is_unique_and_sorted(str);

template <class... Ps> concept Choice_able   = (sizeof...(Ps) >= 2) && mp::all_same<typename Ps::result_type...>;
template <class... Ps> using   Choice_result = typename mp::head<Ps...>::result_type;

template <class... Ps> concept Sequence_able         = sizeof...(Ps) >= 2;
template <class... Ps> using   Sequence_filter_types = mp::filter<mp::is_not_type<void>, typename Ps::result_type...>;
template <class... Ps> using   Sequence_result_trait = mp::unwrap_if_single<mp::retarget<Sequence_filter_types<Ps...>, std::tuple>>;

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



template <class Into, class T>     constexpr bool is_intoable_v                          = std::is_constructible_v<Into, T>;
template <class Into, class... Ts> constexpr bool is_intoable_v<Into, std::tuple<Ts...>> = std::is_constructible_v<Into, Ts...>;

template <class P, class T>
concept Into_able = not void_result<P> && is_intoable_v<T, typename P::result_type>;



TOK3N_END_NAMESPACE(detail)
