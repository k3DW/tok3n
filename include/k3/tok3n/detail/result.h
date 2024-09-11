#pragma once
#include <k3/tok3n/detail/span.h>
#include <optional>

namespace k3::tok3n::detail {

inline constexpr struct failure_tag_t final {} failure_tag;
inline constexpr struct success_tag_t final {} success_tag;

template <class T, class U>
requires (not std::is_reference_v<T>)
class result
{
public:
	using value_type = T;
	using span_type = U;

	constexpr result() = default;

	constexpr result(failure_tag_t, input_span<U> remaining)
		: _result(), _remaining(remaining) {}

	constexpr result(success_tag_t, const T& t, input_span<U> remaining) requires std::constructible_from<T, const T&>
		: _result(t), _remaining(remaining) {}

	constexpr result(success_tag_t, T&& t, input_span<U> remaining) requires std::constructible_from<T, T&&>
		: _result(std::move(t)), _remaining(remaining) {}

	template <class T2>
	constexpr result(const result<T2, U>& other)
		: _result(other._result), _remaining(other._remaining) {}

	template <class T2>
	constexpr result(result<T2, U>&& other)
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

	constexpr input_span<U> remaining() const noexcept { return _remaining; }

private:
	std::optional<T> _result;
	input_span<U> _remaining;

	template <class T2, class U2>
	requires (not std::is_reference_v<T2>)
	friend class result;
};

template <class U>
class result<void, U>
{
public:
	using value_type = void;
	using span_type = U;

	constexpr result() = default;

	constexpr result(failure_tag_t, input_span<U> remaining)
		: _successful(false), _remaining(remaining) {}

	constexpr result(success_tag_t, input_span<U> remaining)
		: _successful(true), _remaining(remaining) {}

	constexpr explicit operator bool() const noexcept { return _successful; }
	constexpr bool has_value() const noexcept         { return _successful; }

	constexpr input_span<U> remaining() const noexcept { return _remaining; }

private:
	bool _successful;
	input_span<U> _remaining;
};



namespace impl {

template <class R>
extern std::false_type is_result_v;
template <class T, class U>
extern std::true_type is_result_v<result<T, U>>;

template <class R>
extern std::bool_constant<is_result_v<R>> is_result_v<const R>;
template <class R>
extern std::bool_constant<is_result_v<R>> is_result_v<R&>;
template <class R>
extern std::bool_constant<is_result_v<R>> is_result_v<R&&>;

} // namespace impl

template <class R, class T, class U>
concept result_of =
	decltype(impl::is_result_v<R>)::value and
	std::same_as<T, typename R::value_type> and
	std::same_as<U, typename R::span_type>;

} // namespace k3::tok3n::detail
