#pragma once
#include <k3/tok3n/types/Span.h>
#include <k3/tok3n/types/Tags.h>
#include <optional>

namespace k3::tok3n {

template <class T, class U>
requires (not std::is_reference_v<T>)
class Result
{
public:
	constexpr Result() = default;

	constexpr Result(FailureTag, Input<U> remaining)
		: mResult(), mRemaining(remaining) {}

	constexpr Result(SuccessTag, const T& t, Input<U> remaining) requires std::constructible_from<T, const T&>
		: mResult(t), mRemaining(remaining) {}

	constexpr Result(SuccessTag, T&& t, Input<U> remaining) requires std::constructible_from<T, T&&>
		: mResult(std::move(t)), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mResult.operator bool(); }
	constexpr bool has_value() const noexcept         { return mResult.has_value(); }

	constexpr T&        value() &       { return mResult.value(); }
	constexpr const T&  value() const&  { return mResult.value(); }
	constexpr T&&       value() &&      { return std::move(mResult).value(); }
	constexpr const T&& value() const&& { return std::move(mResult).value(); }

	constexpr T&        operator*() &       { return *mResult; }
	constexpr const T&  operator*() const&  { return *mResult; }
	constexpr T&&       operator*() &&      { return *std::move(mResult); }
	constexpr const T&& operator*() const&& { return *std::move(mResult); }

	constexpr Input<U> remaining() const noexcept { return mRemaining; }

private:
	std::optional<T> mResult;
	Input<U> mRemaining;
};

template <class U>
class Result<void, U>
{
public:
	constexpr Result() = default;

	constexpr Result(FailureTag, Input<U> remaining)
		: mSuccessful(false), mRemaining(remaining) {}

	constexpr Result(SuccessTag, Input<U> remaining)
		: mSuccessful(true), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mSuccessful; }
	constexpr bool has_value() const noexcept         { return mSuccessful; }

	constexpr Input<U> remaining() const noexcept { return mRemaining; }

private:
	bool mSuccessful;
	Input<U> mRemaining;
};

} // namespace k3::tok3n
