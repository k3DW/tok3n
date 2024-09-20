#pragma once
#include <type_traits>

namespace k3::tok3n::detail {

namespace impl {

template <class... Ts>
struct list {};

struct is_not_void
{
	template <class T>
	using fn = std::negation<std::is_void<T>>;
};

} // namespace impl



namespace impl {

template <class Pred, class ListOfDone, class Seq, std::size_t Next, class Head, class... Tail>
struct filter_with_index;

template <class Pred, class... Done, std::size_t... Is, std::size_t Next, class Head>
struct filter_with_index<Pred, list<Done...>, std::index_sequence<Is...>, Next, Head>
{
	using type = std::conditional_t<Pred::template fn<Head>::value,
		list<Done..., Head>,
		list<Done...>
	>;
	using sequence = std::conditional_t<Pred::template fn<Head>::value,
		std::index_sequence<Is..., Next>,
		std::index_sequence<Is..., static_cast<std::size_t>(-1)>
	>;
};

template <class Pred, class... Done, std::size_t... Is, std::size_t Next, class Head, class... Tail>
struct filter_with_index<Pred, list<Done...>, std::index_sequence<Is...>, Next, Head, Tail...>
{
private:
	using trait = std::conditional_t<Pred::template fn<Head>::value,
		filter_with_index<Pred, list<Done..., Head>, std::index_sequence<Is..., Next>, Next + 1, Tail...>,
		filter_with_index<Pred, list<Done...>, std::index_sequence<Is..., static_cast<std::size_t>(-1)>, Next, Tail...>
	>;

public:
	using type = typename trait::type;
	using sequence = typename trait::sequence;
};

} // namespace impl

template <class... Ts>
using filter_out_void = impl::filter_with_index<impl::is_not_void, impl::list<>, std::index_sequence<>, 0, Ts...>;



namespace impl {

template <class ListOfDone, class Seq, class T>
struct index_lookup;

template <class Head, class... Tail, std::size_t I, std::size_t... Is, class T>
struct index_lookup<list<Head, Tail...>, std::index_sequence<I, Is...>, T>
{
	static constexpr std::size_t value = std::conditional_t<std::is_same_v<T, Head>,
		std::integral_constant<std::size_t, I>,
		std::conditional_t<sizeof...(Tail) == 0,
			std::integral_constant<std::size_t, 0>,
			index_lookup<list<Tail...>, std::index_sequence<Is...>, T>
		>
	>::value;
};

template <class Pred, class ListOfDone, class Seq, std::size_t Next, class Head, class... Tail>
struct filter_deduplicate_with_index;

template <class Pred, class... Done, std::size_t... Is, std::size_t Next, class Head>
struct filter_deduplicate_with_index<Pred, list<Done...>, std::index_sequence<Is...>, Next, Head>
{
private:
	static constexpr std::size_t next_index = std::conditional_t<Pred::template fn<Head>::value,
		std::conditional_t<(... or std::is_same_v<Done, Head>),
			index_lookup<list<Done...>, std::index_sequence<Is...>, Head>,
			std::integral_constant<std::size_t, Next>
		>,
		std::integral_constant<std::size_t, static_cast<std::size_t>(-1)>
	>::value;

public:
	using type = std::conditional_t<Pred::template fn<Head>::value and not (... or std::is_same_v<Done, Head>),
		list<Done..., Head>,
		list<Done...>
	>;
	using sequence = std::index_sequence<Is..., next_index>;
};

template <class Pred, class... Done, std::size_t... Is, std::size_t Next, class Head, class... Tail>
struct filter_deduplicate_with_index<Pred, list<Done...>, std::index_sequence<Is...>, Next, Head, Tail...>
{
private:
	static constexpr std::size_t next_index = std::conditional_t<Pred::template fn<Head>::value,
		std::conditional_t<(... or std::is_same_v<Done, Head>),
			index_lookup<list<Done...>, std::index_sequence<Is...>, Head>,
			std::integral_constant<std::size_t, Next>
		>,
		std::integral_constant<std::size_t, static_cast<std::size_t>(-1)>
	>::value;
	using next_sequence = std::index_sequence<Is..., next_index>;

	using trait = std::conditional_t<Pred::template fn<Head>::value and not (... or std::is_same_v<Done, Head>),
		filter_deduplicate_with_index<Pred, list<Done..., Head>, next_sequence, Next + 1, Tail...>,
		filter_deduplicate_with_index<Pred, list<Done...>, next_sequence, Next, Tail...>
	>;

public:
	using type = typename trait::type;
	using sequence = typename trait::sequence;
};

} // namespace impl

template <class... Ts>
using filter_out_void_deduplicate = impl::filter_deduplicate_with_index<impl::is_not_void, impl::list<>, std::index_sequence<>, 0, Ts...>;

} // namespace k3::tok3n::detail
