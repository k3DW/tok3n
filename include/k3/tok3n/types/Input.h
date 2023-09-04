#pragma once
#include <algorithm>
#include <span>
#include <string_view>

namespace k3::tok3n {

template <class T>
class Input
{
public:
	constexpr Input() = default;

	constexpr Input(std::span<const T> value)
		: _value(value)
	{}

	constexpr Input(std::string_view value)
		: _value(value.data(), value.size())
	{}

	template <std::size_t N>
	constexpr Input(const char(&arr)[N]) requires std::same_as<T, char>
		: _value(arr, N - 1)
	{}

	constexpr Input(const T* data, std::size_t size)
		: _value(data, size)
	{}

	constexpr const T* data() const { return _value.data(); }
	constexpr std::size_t size() const { return _value.size(); }
	constexpr bool empty() const { return _value.empty(); }
	constexpr const T& front() const { return _value.front(); }

	constexpr Input first(std::size_t count) const { return { _value.first(count) }; }
	constexpr Input subspan(std::size_t offset, std::size_t count = std::dynamic_extent) const { return { _value.subspan(offset, count) }; }

	friend constexpr bool operator==(const Input& lhs, const Input& rhs)
	{
		return std::ranges::equal(lhs._value, rhs._value);
	}

private:
	std::span<const T> _value;
};

} // namespace k3::tok3n
