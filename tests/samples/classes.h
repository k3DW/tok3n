#pragma once
#include <k3/tok3n.h>

TOK3N_BEGIN_NAMESPACE(tests)

class Class1
{
public:
	explicit constexpr Class1(int value) : value(value) {}

	explicit constexpr Class1(std::string_view sv)
	{
		if (sv.size() == 1)
		{
			switch (sv.front())
			{
				break; case ' ': value = 0;
				break; case '.': value = 1;
				break; default:  value = 2;
			}
		}
		else
			value = 3;
	}

	friend constexpr bool operator==(const Class1&, const Class1&) = default;

private:
	int value;
};

class Class2
{
public:
	explicit constexpr Class2(std::string_view sv1, std::string_view sv2)
		: sv1(sv1), sv2(sv2) {}

	explicit constexpr Class2(const std::tuple<std::string_view, std::string_view>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	friend constexpr bool operator==(const Class2&, const Class2&) = default;

private:
	std::string_view sv1;
	std::string_view sv2;
};

class Class3
{
public:
	friend constexpr bool operator==(const Class3&, const Class3&) = default;
};

class Class4
{
public:
	explicit constexpr Class4(const std::tuple<std::string_view, std::string_view>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	explicit constexpr operator Class2() const { return Class2{ sv1, sv2 }; }

private:
	std::string_view sv1;
	std::string_view sv2;
};

class Class5
{
public:
	explicit constexpr Class5(std::string_view sv1, std::string_view sv2)
		: sv1(sv1), sv2(sv2) {}

	friend constexpr bool operator==(const Class5&, const Class5&) = default;

private:
	std::string_view sv1;
	std::string_view sv2;
};

struct Sink
{
	constexpr Sink(auto&&...) {};
};

TOK3N_END_NAMESPACE(tests)