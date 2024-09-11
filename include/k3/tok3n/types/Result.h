#pragma once
#include <k3/tok3n/detail/span.h>
#include <k3/tok3n/types/Tags.h>
#include <optional>

namespace k3::tok3n {

template <class T, class U>
requires (not std::is_reference_v<T>)
class Result
{
public:
	constexpr Result() = default;

	constexpr Result(FailureTag, detail::input_span<U> remaining)
		: _result(), _remaining(remaining) {}

	constexpr Result(SuccessTag, const T& t, detail::input_span<U> remaining) requires std::constructible_from<T, const T&>
		: _result(t), _remaining(remaining) {}

	constexpr Result(SuccessTag, T&& t, detail::input_span<U> remaining) requires std::constructible_from<T, T&&>
		: _result(std::move(t)), _remaining(remaining) {}

	template <class T2>
	constexpr Result(const Result<T2, U>& other)
		: _result(other._result), _remaining(other._remaining) {}

	template <class T2>
	constexpr Result(Result<T2, U>&& other)
		: _result(std::move(other)._result), _remaining(other._remaining) {}

	constexpr explicit operator bool() const noexcept { return _result.operator bool(); }
	constexpr bool has_value() const noexcept         { return _result.has_value(); }

	constexpr T&        value() &       { return _result.value(); }
	constexpr const T&  value() const&  { return _result.value(); }
	constexpr T&&       value() &&      { return std::move(_result).value(); }
	constexpr const T&& value() const&& { return std::move(_result).value(); }

	constexpr T&        operator*() &       { return *_result; }
	constexpr const T&  operator*() const&  { return *_result; }
	constexpr T&&       operator*() &&      { return *std::move(_result); }
	constexpr const T&& operator*() const&& { return *std::move(_result); }

	constexpr detail::input_span<U> remaining() const noexcept { return _remaining; }

private:
	std::optional<T> _result;
	detail::input_span<U> _remaining;

	template <class T2, class U2>
	requires (not std::is_reference_v<T2>)
	friend class Result;
};

template <class U>
class Result<void, U>
{
public:
	constexpr Result() = default;

	constexpr Result(FailureTag, detail::input_span<U> remaining)
		: _successful(false), _remaining(remaining) {}

	constexpr Result(SuccessTag, detail::input_span<U> remaining)
		: _successful(true), _remaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return _successful; }
	constexpr bool has_value() const noexcept         { return _successful; }

	constexpr detail::input_span<U> remaining() const noexcept { return _remaining; }

private:
	bool _successful;
	detail::input_span<U> _remaining;
};

} // namespace k3::tok3n
