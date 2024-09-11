#pragma once
#include <k3/tok3n/detail/span.h>
#include <k3/tok3n/types/Tags.h>

namespace k3::tok3n::detail {

namespace IsResult::Void
{

	template <class R, class U>
	concept Functionality =
		requires (R r)
		{
			{ static_cast<R>(r).operator bool() } -> std::same_as<bool>;
			{ static_cast<R>(r).has_value() } -> std::same_as<bool>;
			{ static_cast<R>(r).remaining() } -> std::same_as<input_span<U>>;
		};

	template <class R, class U>
	concept Constructible =
		std::constructible_from<R>                        and
		std::constructible_from<R, FailureTag, input_span<U>>  and
		std::constructible_from<R, SuccessTag, input_span<U>>;

}

template <class R, class T, class U>
concept IsResultVoid =
	std::same_as<void, T>                        and
	IsResult::Void::Constructible<R, U>          and
	IsResult::Void::Functionality<R&, U>         and
	IsResult::Void::Functionality<const R&, U>   and
	IsResult::Void::Functionality<R&&, U>        and
	IsResult::Void::Functionality<const R&&, U>;

namespace IsResult::NonVoid
{

	template <class R, class T, class U>
	concept Functionality =
		Void::Functionality<R, U> and
		requires (R r)
		{
			{ static_cast<R>(r).value() } -> std::same_as<T>;
			{ *static_cast<R>(r) } -> std::same_as<T>;
		};

	template <class R, class T, class U>
	concept Constructible =
		std::constructible_from<R>                                        and
		std::constructible_from<R, FailureTag, input_span<U>>                  and
			(std::constructible_from<R, SuccessTag, T&&, input_span<U>> or
			 std::constructible_from<R, SuccessTag, const T&, input_span<U>>);

}

template <class R, class T, class U>
concept IsResultNonVoid =
	not std::same_as<void, T>                                  and
	IsResult::NonVoid::Constructible<R, T, U>                  and
	IsResult::NonVoid::Functionality<R&, T&, U>                and
	IsResult::NonVoid::Functionality<const R&, const T&, U>    and
	IsResult::NonVoid::Functionality<R&&, T&&, U>              and
	IsResult::NonVoid::Functionality<const R&&, const T&&, U>;

} // namespace k3::tok3n::detail

namespace k3::tok3n {

template <class R, class T, class U>
concept IsResult =
	not std::is_reference_v<T>
	and (detail::IsResultVoid<R, T, U> or detail::IsResultNonVoid<R, T, U>);

} // namespace k3::tok3n
