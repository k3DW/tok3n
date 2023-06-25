#pragma once
#include <k3/tok3n/types/Input.h>
#include <k3/tok3n/types/Tags.h>
#include <optional>

namespace k3::tok3n {

template <class T>
requires (not std::is_reference_v<T>)
class Result
{
public:
	constexpr Result() = default;

	constexpr Result(FailureTag, Input remaining)
		: mResult(), mRemaining(remaining) {}

	constexpr Result(SuccessTag, T&& t, Input remaining)
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

	constexpr Result(FailureTag, Input remaining)
		: mSuccessful(false), mRemaining(remaining) {}

	constexpr Result(SuccessTag, Input remaining)
		: mSuccessful(true), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mSuccessful; }
	constexpr bool has_value() const noexcept         { return mSuccessful; }

	constexpr Input remaining() const noexcept { return mRemaining; }

private:
	bool mSuccessful;
	Input mRemaining;
};

} // namespace k3::tok3n
