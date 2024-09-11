#pragma once
#include <k3/tok3n/concepts/IsResult.h>
#include <k3/tok3n/detail/type_traits.h>

namespace k3::tok3n::detail {

enum class parser_family
{
	none,

	any_of,
	none_of,
	all_of,
	anything,
	epsilon,
	choice,
	sequence,
	maybe,
	exactly,
	one_or_more,
	zero_or_more,
	delimit,
	ignore,
	complete,
	join,
	map,
	named,
	custom,

	end
};

inline constexpr parser_family any_of_family       = parser_family::any_of;
inline constexpr parser_family none_of_family      = parser_family::none_of;
inline constexpr parser_family all_of_family       = parser_family::all_of;
inline constexpr parser_family anything_family     = parser_family::anything;
inline constexpr parser_family epsilon_family      = parser_family::epsilon;
inline constexpr parser_family choice_family       = parser_family::choice;
inline constexpr parser_family sequence_family     = parser_family::sequence;
inline constexpr parser_family maybe_family        = parser_family::maybe;
inline constexpr parser_family exactly_family      = parser_family::exactly;
inline constexpr parser_family one_or_more_family  = parser_family::one_or_more;
inline constexpr parser_family zero_or_more_family = parser_family::zero_or_more;
inline constexpr parser_family delimit_family      = parser_family::delimit;
inline constexpr parser_family ignore_family       = parser_family::ignore;
inline constexpr parser_family complete_family     = parser_family::complete;
inline constexpr parser_family named_family        = parser_family::join;
inline constexpr parser_family join_family         = parser_family::map;
inline constexpr parser_family map_family          = parser_family::named;
inline constexpr parser_family custom_family       = parser_family::custom;



namespace impl {

template <template <class...> class A>
struct template_template_parameter_checker {};

} // namespace impl
    
template <class P_raw, class P = std::remove_reference_t<P_raw>>
concept parser =
    std::same_as<P, std::remove_reference_t<P_raw>> and // The 2nd parameter must only ever be defaulted
	enum_within_bounds<parser_family, static_cast<parser_family>(P::family), parser_family::none, parser_family::end> and
	std::is_empty_v<P> and
	implicitly_default_constructible<P> and
	requires { typename P::value_type; } and
	requires { impl::template_template_parameter_checker<P::template result_for>{}; };
    
template <class P, class V>
concept parser_for =
	parser<P> and
	equality_comparable_with<V, typename P::value_type> and
	requires (Input<V> input)
	{
		typename P::template result_for<V>;
		P::parse(input);
		P::lookahead(input);
		{ P::parse(input) } -> k3::tok3n::IsResult<typename P::template result_for<V>, V>;
		{ P::lookahead(input) } -> k3::tok3n::IsResult<void, V>;
	};

template <class P1, class P2>
concept parser_compatible_with = 
	parser<P1> and
	parser<P2> and
	std::same_as<typename P1::value_type, typename P2::value_type>;

} // namespace k3::tok3n::detail
