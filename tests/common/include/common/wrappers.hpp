// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_WRAPPERS_HPP
#define K3_TOK3N_TESTS_COMMON_WRAPPERS_HPP

#include <utility>

template <class T>
class MoveOnlyWrapper
{
public:
	template <class... Args>
	constexpr MoveOnlyWrapper(Args&&... args)
		: _value(std::forward<Args>(args)...)
	{}

	static constexpr auto make = []<class... Args>(Args&&... args)
	{
		return MoveOnlyWrapper(std::forward<Args>(args)...);
	};

	MoveOnlyWrapper(const MoveOnlyWrapper&) = delete;
	MoveOnlyWrapper& operator=(const MoveOnlyWrapper&) = delete;

	MoveOnlyWrapper(MoveOnlyWrapper&&) = default;
	MoveOnlyWrapper& operator=(MoveOnlyWrapper&&) = default;
	~MoveOnlyWrapper() = default;

	constexpr T& value() { return _value; }
	constexpr const T& value() const { return _value; }

	friend constexpr bool operator==(const MoveOnlyWrapper&, const MoveOnlyWrapper&) = default;

private:
	T _value;
};

#endif // K3_TOK3N_TESTS_COMMON_WRAPPERS_HPP
