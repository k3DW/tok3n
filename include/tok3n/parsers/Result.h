#pragma once
#include <string_view>
#include <optional>
#include "tok3n/utilities/forward_like.h"

TOK3N_BEGIN_NAMESPACE()

static constexpr struct failure_t final {} failure;
static constexpr struct success_t final {} success;

template <class T>
requires (not std::is_reference_v<T>)
class Result
{
public:
	constexpr Result() = default;

	constexpr Result(failure_t, Input remaining)
		: mResult(), mRemaining(remaining) {}

	constexpr Result(success_t, T&& t, Input remaining)
		: mResult(std::move(t)), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mResult.operator bool(); }
	constexpr bool has_value() const noexcept         { return mResult.has_value(); }

	template <class Self>
	constexpr decltype(auto) value(this Self&& self)
	{
		return forward_like<Self>(self.mResult.value());
	}
	template <class Self>
	constexpr decltype(auto) operator*(this Self&& self)
	{
		return forward_like<Self>(self.mResult.operator*());
	}

	constexpr Input remaining() const noexcept { return mRemaining; }

private:
	std::optional<T> mResult;
	Input mRemaining;
};

template <>
class Result<void>
{
public:
	constexpr Result() = default;

	constexpr Result(failure_t, Input remaining)
		: mSuccessful(false), mRemaining(remaining) {}

	constexpr Result(success_t, Input remaining)
		: mSuccessful(true), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mSuccessful; }
	constexpr bool has_value() const noexcept         { return mSuccessful; }

	constexpr Input remaining() const noexcept { return mRemaining; }

private:
	bool mSuccessful;
	Input mRemaining;
};

TOK3N_END_NAMESPACE()
