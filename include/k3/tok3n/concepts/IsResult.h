#pragma once
#include <k3/tok3n/types/Input.h>
#include <k3/tok3n/types/Tags.h>
#include <concepts>

namespace k3::tok3n::detail {

namespace IsResult::Void
{

	template <class R>
	concept Functionality =
		requires (R r)
		{
			{ static_cast<R>(r).operator bool() } -> std::same_as<bool>;
			{ static_cast<R>(r).has_value() } -> std::same_as<bool>;
			{ static_cast<R>(r).remaining() } -> std::same_as<Input>;
		};

	template <class R>
	concept Constructible =
		std::constructible_from<R>                     and
		std::constructible_from<R, FailureTag, Input>  and
		std::constructible_from<R, SuccessTag, Input>;

}

template <class R, class T>
concept IsResultVoid =
	std::same_as<void, T>                     and
	IsResult::Void::Constructible<R>          and
	IsResult::Void::Functionality<R&>         and
	IsResult::Void::Functionality<const R&>   and
	IsResult::Void::Functionality<R&&>        and
	IsResult::Void::Functionality<const R&&>;

namespace IsResult::NonVoid
{

	template <class R, class T>
	concept Functionality =
		Void::Functionality<R> and
		requires (R r)
		{
			{ static_cast<R>(r).value() } -> std::same_as<T>;
			{ *static_cast<R>(r) } -> std::same_as<T>;
		};

	template <class R, class T>
	concept Constructible =
		std::constructible_from<R>                                     and
		std::constructible_from<R, FailureTag, Input>                  and
			(std::constructible_from<R, SuccessTag, T&&, Input> or
			 std::constructible_from<R, SuccessTag, const T&, Input>);

}

template <class R, class T>
concept IsResultNonVoid =
	not std::same_as<void, T>                               and
	IsResult::NonVoid::Constructible<R, T>                  and
	IsResult::NonVoid::Functionality<R&, T&>                and
	IsResult::NonVoid::Functionality<const R&, const T&>    and
	IsResult::NonVoid::Functionality<R&&, T&&>              and
	IsResult::NonVoid::Functionality<const R&&, const T&&>;

} // namespace k3::tok3n::detail

namespace k3::tok3n {

template <class R, class T>
concept IsResult =
	not std::is_reference_v<T>
	and (detail::IsResultVoid<R, T> or detail::IsResultNonVoid<R, T>);

} // namespace k3::tok3n
