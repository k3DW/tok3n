#pragma once
#include <concepts>
#include <type_traits>

namespace k3::tok3n {

template <class T>
concept CharType = // https://en.cppreference.com/w/cpp/language/types
	std::same_as<std::remove_const_t<T>, signed char>   or
	std::same_as<std::remove_const_t<T>, unsigned char> or
	std::same_as<std::remove_const_t<T>, char>          or
	std::same_as<std::remove_const_t<T>, wchar_t>       or
	std::same_as<std::remove_const_t<T>, char16_t>      or
	std::same_as<std::remove_const_t<T>, char32_t>      or
	std::same_as<std::remove_const_t<T>, char8_t>;

} // namespace k3::tok3n
