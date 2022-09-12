#pragma once
#include <string_view>
#include <optional>

namespace k3::parser
{

static constexpr struct failure_t final {} failure;
static constexpr struct success_t final {} success;

template <class T>
class NewResult
{
public:
	using type = T;

	constexpr NewResult() = default;

	constexpr NewResult(failure_t, std::string_view remaining)
		: mResult(), mRemaining(remaining) {}

	constexpr NewResult(success_t, const T& t, std::string_view remaining)
		: mResult(t), mRemaining(remaining) {}

	constexpr NewResult(success_t, T&& t, std::string_view remaining)
		: mResult(std::move(t)), mRemaining(remaining) {}

	template <std::convertible_to<T> U>
	constexpr NewResult(success_t, U&& u, std::string_view remaining)
		: mResult(std::forward<U>(u)), mRemaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return mResult.operator bool(); }
	constexpr bool has_value() const noexcept         { return mResult.has_value(); }

	constexpr const T& value() const& { return mResult.value(); }

	constexpr std::string_view remaining() const noexcept { return mRemaining; }

private:
	std::optional<T> mResult;
	std::string_view mRemaining;
};

}
