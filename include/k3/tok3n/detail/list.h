#pragma once

namespace k3::tok3n::detail {

template <class... Ts>
struct list {};

template <class List, template <class...> class Other>
struct change_list;

template <template <class...> class List, class... Ts, template <class...> class Other>
struct change_list<List<Ts...>, Other>
{
	using type = Other<Ts...>;
};

} // namespace k3::tok3n::detail
