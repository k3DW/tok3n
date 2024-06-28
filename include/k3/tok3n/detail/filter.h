#pragma once
#include <k3/tok3n/detail/list.h>
#include <k3/tok3n/detail/type_predicate.h>
#include <tuple>

namespace k3::tok3n::detail {

template <type_predicate Pred, class ListOfDone, class Seq, std::size_t Next, class Head, class... Tail>
struct filter_with_index_impl {};

template <type_predicate Pred, template <class...> class List, class... Done, std::size_t... Is, std::size_t Next, class Head>
struct filter_with_index_impl<Pred, List<Done...>, std::index_sequence<Is...>, Next, Head>
{
	using type = std::conditional_t<Pred::template predicate<Head>::value,
		List<Done..., Head>,
		List<Done...>
	>;

	using sequence = std::conditional_t<Pred::template predicate<Head>::value,
		std::index_sequence<Is..., Next>,
		std::index_sequence<Is..., static_cast<std::size_t>(-1)>
	>;
};

template <type_predicate Pred, template <class...> class List, class... Done, std::size_t... Is, std::size_t Next, class Head, class... Tail>
struct filter_with_index_impl<Pred, List<Done...>, std::index_sequence<Is...>, Next, Head, Tail...>
{
	using trait = std::conditional_t<Pred::template predicate<Head>::value,
		filter_with_index_impl<Pred, List<Done..., Head>, std::index_sequence<Is..., Next>, Next + 1, Tail...>,
		filter_with_index_impl<Pred, List<Done...>, std::index_sequence<Is..., static_cast<std::size_t>(-1)>, Next, Tail...>
	>;

	using type = typename trait::type;
	using sequence = typename trait::sequence;
};

template <type_predicate Pred, class... Ts>
using filter_with_index = filter_with_index_impl<Pred, list<>, std::index_sequence<>, 0, Ts...>;



template <class ListOfDone, class Seq, class T>
struct index_lookup
{
	// Placeholders
	using type = std::integral_constant<std::size_t, static_cast<std::size_t>(-2)>;
	static constexpr std::size_t value = static_cast<std::size_t>(-2);
};

template <template <class...> class List, class Head, class... Tail, std::size_t I, std::size_t... Is, class T>
struct index_lookup<List<Head, Tail...>, std::index_sequence<I, Is...>, T>
{
	using type = std::conditional_t<std::is_same_v<T, Head>,
		std::integral_constant<std::size_t, I>,
		typename index_lookup<List<Tail...>, std::index_sequence<Is...>, T>::type
	>;
	static constexpr std::size_t value = type::value;
};



template <type_predicate Pred, class ListOfDone, class Seq, std::size_t Next, class Head, class... Tail>
struct filter_deduplicate_with_index_impl {};

template <type_predicate Pred, template <class...> class List, class... Done, std::size_t... Is, std::size_t Next, class Head>
struct filter_deduplicate_with_index_impl<Pred, List<Done...>, std::index_sequence<Is...>, Next, Head>
{
	using type = std::conditional_t<Pred::template predicate<Head>::value and not (... or std::is_same_v<Done, Head>),
		List<Done..., Head>,
		List<Done...>
	>;

	using sequence = std::conditional_t<Pred::template predicate<Head>::value,
		std::conditional_t<(... or std::is_same_v<Done, Head>),
			std::index_sequence<Is..., index_lookup<List<Done...>, std::index_sequence<Is...>, Head>::value>,
			std::index_sequence<Is..., Next>
		>,
		std::index_sequence<Is..., static_cast<std::size_t>(-1)>
	>;
};

template <type_predicate Pred, template <class...> class List, class... Done, std::size_t... Is, std::size_t Next, class Head, class... Tail>
struct filter_deduplicate_with_index_impl<Pred, List<Done...>, std::index_sequence<Is...>, Next, Head, Tail...>
{
	using trait = std::conditional_t<Pred::template predicate<Head>::value,
		std::conditional_t<(... or std::is_same_v<Done, Head>),
			filter_deduplicate_with_index_impl<Pred, List<Done...>, std::index_sequence<Is..., index_lookup<List<Done...>, std::index_sequence<Is...>, Head>::value>, Next, Tail...>,
			filter_deduplicate_with_index_impl<Pred, List<Done..., Head>, std::index_sequence<Is..., Next>, Next + 1, Tail...>
		>,
		filter_deduplicate_with_index_impl<Pred, List<Done...>, std::index_sequence<Is..., static_cast<std::size_t>(-1)>, Next, Tail...>
	>;

	using type = typename trait::type;
	using sequence = typename trait::sequence;
};

template <type_predicate Pred, class... Ts>
using filter_deduplicate_with_index = filter_deduplicate_with_index_impl<Pred, list<>, std::index_sequence<>, 0, Ts...>;

} // namespace k3::tok3n::detail
