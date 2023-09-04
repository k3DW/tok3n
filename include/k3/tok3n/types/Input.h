#pragma once
#include <string_view>

namespace k3::tok3n {

class Input
{
public:
	constexpr Input() = default;

	constexpr Input(std::string_view value)
		: _value(value)
	{}

	template <std::size_t N>
	constexpr Input(const char(&arr)[N])
		: _value(arr)
	{}

	constexpr Input(const char* data, std::size_t size)
		: _value(data, size)
	{}

	constexpr auto data() const { return _value.data(); }
	constexpr auto size() const { return _value.size(); }
	constexpr auto empty() const { return _value.empty(); }
	constexpr auto& front() const { return _value.front(); }

	template <class U>
	constexpr auto starts_with(U u) const { return _value.starts_with(u); }

	constexpr void remove_prefix(std::size_t count) { _value.remove_prefix(count); }

	friend constexpr bool operator==(const Input&, const Input&) = default;

private:
	std::string_view _value;
};

} // namespace k3::tok3n
