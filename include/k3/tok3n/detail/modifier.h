#pragma once
#include <k3/tok3n/detail/type_traits.h>

namespace k3::tok3n::detail {

enum class modifier_family
{
	none,

	apply_into,
	apply,
	complete,
	constant,
	defaulted,
	delimit_keep,
	delimit,
	exactly,
	ignore,
	into,
	join,
	map,
	multi,
	name,
	sub,

	end
};



struct modifier_base {};

template <class M>
concept modifier =
	enum_within_bounds<modifier_family, static_cast<modifier_family>(M::family), modifier_family::none, modifier_family::end> and
    std::derived_from<M, modifier_base> and
	std::is_empty_v<M>;

} // namespace k3::tok3n::detail
