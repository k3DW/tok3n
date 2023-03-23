#pragma once
#include <tok3n/utilities/namespace.h>
#include <tok3n/types/Input.h>
#include <tok3n/types/tags.h>
#include <concepts>

TOK3N_BEGIN_NAMESPACE(detail)

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

	template <class R, class T>
	concept Constructible =
		std::constructible_from<R>                    and
		std::constructible_from<R, failure_t, Input>  and
		std::constructible_from<R, success_t, Input>;

}

template <class R, class T>
concept IsResultVoid =
	std::same_as<void, T>                     and
	IsResult::Void::Constructible<R, T>       and
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
		std::constructible_from<R>                            and
		std::constructible_from<R, failure_t, Input>          and
		std::constructible_from<R, success_t, T&&, Input>     and
		not std::constructible_from<R, success_t, T&, Input>;

}

template <class R, class T>
concept IsResultNonVoid =
	not std::same_as<void, T>                               and
	IsResult::NonVoid::Constructible<R, T>                  and
	IsResult::NonVoid::Functionality<R&, T&>                and
	IsResult::NonVoid::Functionality<const R&, const T&>    and
	IsResult::NonVoid::Functionality<R&&, T&&>              and
	IsResult::NonVoid::Functionality<const R&&, const T&&>;

TOK3N_END_NAMESPACE(detail)

TOK3N_BEGIN_NAMESPACE()

template <class R, class T>
concept IsResult =
	not std::is_reference_v<T>
	and (detail::IsResultVoid<R, T> or detail::IsResultNonVoid<R, T>);

TOK3N_END_NAMESPACE()