#pragma once
#include <algorithm>
#include <span>
#include <string_view>

namespace k3::tok3n {

class Output
{
public:
	constexpr Output() = default;

	constexpr Output(std::string_view value)
		: _value(value.data(), value.size())
	{}

	template <std::size_t N>
	constexpr Output(const char(&arr)[N])
		: _value(arr, N - 1)
	{}

	constexpr Output(const char* data)
		: _value(data)
	{}

	constexpr Output(const char* data, std::size_t size)
		: _value(data, size)
	{}

	constexpr const char* data() const { return _value.data(); }
	constexpr std::size_t size() const { return _value.size(); }
	constexpr const char& front() const { return _value.front(); }
	constexpr auto begin() const { return _value.begin(); }
	constexpr auto end() const { return _value.end(); }

	friend constexpr bool operator==(const Output& lhs, const Output& rhs)
	{
		return std::ranges::equal(lhs._value, rhs._value);
	}

private:
	std::string_view _value;
};

} // namespace k3::tok3n
