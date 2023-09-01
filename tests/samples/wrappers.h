#pragma once
#include <type_traits>

template <class T>
class MoveOnlyWrapper
{
public:
	template <class... Args>
	constexpr MoveOnlyWrapper(Args&&... args)
		: _value(std::forward<Args>(args)...)
	{}

	static constexpr auto make = []<class... Args>(Args&&... args) -> MoveOnlyWrapper
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

private:
	T _value;
};

template <class T>
class CopyOnlyWrapper
{
public:
	template <class... Args>
	constexpr CopyOnlyWrapper(Args&&... args)
		: _value(std::forward<Args>(args)...)
	{}

	static constexpr auto make = []<class... Args>(Args&&... args) -> CopyOnlyWrapper
	{
		return CopyOnlyWrapper(std::forward<Args>(args)...);
	};

	CopyOnlyWrapper(const CopyOnlyWrapper&) = default;
	CopyOnlyWrapper& operator=(const CopyOnlyWrapper&) = default;

	CopyOnlyWrapper(CopyOnlyWrapper&&) = delete;
	CopyOnlyWrapper& operator=(CopyOnlyWrapper&&) = delete;
	~CopyOnlyWrapper() = default;

	constexpr T& value() { return _value; }
	constexpr const T& value() const { return _value; }

private:
	T _value;
};
