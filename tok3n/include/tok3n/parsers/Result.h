#pragma once
#include <string_view>
#include <optional>

BEGIN_NAMESPACE_TOK3N()

static constexpr struct failure_t final {} failure;
static constexpr struct success_t final {} success;

template <class T>
class Result
{
public:
	constexpr Result() = default;

	constexpr Result(failure_t, std::string_view remaining)
		: mResult(), mRemaining(remaining) {}

	constexpr Result(success_t, const T& t, std::string_view remaining)
		: mResult(t), mRemaining(remaining) {}

	constexpr Result(success_t, T&& t, std::string_view remaining)
		: mResult(std::move(t)), mRemaining(remaining) {}

	template <std::convertible_to<T> U>
	constexpr Result(success_t, U&& u, std::string_view remaining)
		: mResult(std::forward<U>(u)), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mResult.operator bool(); }
	constexpr bool has_value() const noexcept         { return mResult.has_value(); }

	constexpr const T& value() const&     { return mResult.value(); }
	constexpr const T& operator*() const& { return *mResult; }

	constexpr std::string_view remaining() const noexcept { return mRemaining; }

private:
	std::optional<T> mResult;
	std::string_view mRemaining;
};

template <>
class Result<void>
{
public:
	constexpr Result() = default;

	constexpr Result(failure_t, std::string_view remaining)
		: mSuccessful(false), mRemaining(remaining) {}

	constexpr Result(success_t, std::string_view remaining)
		: mSuccessful(true), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mSuccessful; }
	constexpr bool has_value() const noexcept         { return mSuccessful; }

	constexpr std::string_view remaining() const noexcept { return mRemaining; }

private:
	bool mSuccessful;
	std::string_view mRemaining;
};

END_NAMESPACE_TOK3N()
