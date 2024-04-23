#pragma once

class Class1
{
public:
	explicit constexpr Class1(int value) : value(value) {}

	template <class T>
	explicit constexpr Class1(Output<T> sv)
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
	explicit constexpr Class2(Output<char> sv1, Output<char> sv2)
		: sv1(sv1), sv2(sv2) {}

	template <std::size_t M, std::size_t N>
	explicit constexpr Class2(const char(&sv1)[M], const char(&sv2)[N])
		: sv1(sv1), sv2(sv2) {}

	explicit constexpr Class2(const std::tuple<Output<char>, Output<char>>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	explicit constexpr Class2(Output<wchar_t> sv1, Output<wchar_t> sv2)
		: sv1(sv1), sv2(sv2) {}

	template <std::size_t M, std::size_t N>
	explicit constexpr Class2(const wchar_t(&sv1)[M], const wchar_t(&sv2)[N])
		: sv1(sv1), sv2(sv2) {}

	explicit constexpr Class2(const std::tuple<Output<wchar_t>, Output<wchar_t>>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	explicit constexpr Class2(Output<int> sv1, Output<int> sv2)
		: sv1(sv1), sv2(sv2) {}

	template <std::size_t M, std::size_t N>
	explicit constexpr Class2(const std::array<int, M>& sv1, const std::array<int, N>& sv2)
		: sv1(sv1), sv2(sv2) {}

	explicit constexpr Class2(const std::tuple<Output<int>, Output<int>>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	friend constexpr bool operator==(const Class2&, const Class2&) = default;

private:
	using Variant = std::variant<Output<char>, Output<wchar_t>, Output<int>>;
	Variant sv1;
	Variant sv2;

public:
	explicit constexpr Class2(Variant sv1, Variant sv2)
		: sv1(sv1), sv2(sv2) {}
};

class Class3
{
public:
	friend constexpr bool operator==(const Class3&, const Class3&) = default;
};

class Class4
{
public:
	explicit constexpr Class4(const std::tuple<Output<char>, Output<char>>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	explicit constexpr Class4(const std::tuple<Output<wchar_t>, Output<wchar_t>>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	explicit constexpr Class4(const std::tuple<Output<int>, Output<int>>& tup)
	{
		std::tie(sv1, sv2) = tup;
	}

	explicit constexpr operator Class2() const { return Class2{ sv1, sv2 }; }

private:
	using Variant = std::variant<Output<char>, Output<wchar_t>, Output<int>>;
	Variant sv1;
	Variant sv2;
};

class Class5
{
public:
	explicit constexpr Class5(Output<char> sv1, Output<char> sv2)
		: sv1(sv1), sv2(sv2) {}

	explicit constexpr Class5(Output<wchar_t> sv1, Output<wchar_t> sv2)
		: sv1(sv1), sv2(sv2) {}

	explicit constexpr Class5(Output<int> sv1, Output<int> sv2)
		: sv1(sv1), sv2(sv2) {}

	friend constexpr bool operator==(const Class5&, const Class5&) = default;

private:
	using Variant = std::variant<Output<char>, Output<wchar_t>, Output<int>>;
	Variant sv1;
	Variant sv2;
};

struct Sink
{
	constexpr Sink(auto&&...) {};
};
