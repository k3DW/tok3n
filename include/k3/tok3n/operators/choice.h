#pragma once
#include <k3/tok3n/parsers/basic/AnyOf.h>
#include <k3/tok3n/parsers/basic/NoneOf.h>
#include <k3/tok3n/parsers/compound/Choice.h>

namespace k3::tok3n::operators_impl {

class CountingInsertIterator
{
public:
	constexpr CountingInsertIterator(std::size_t& count)
		: _count(&count) {}

	constexpr CountingInsertIterator& operator*() { return *this; }
	constexpr CountingInsertIterator& operator++() { return *this; }
	constexpr CountingInsertIterator operator++(int) { return *this; }

	constexpr CountingInsertIterator& operator=(auto&&)
	{
		++*_count;
		return *this;
	}

private:
	std::size_t* _count;
};

enum class SetOperationType
{
	set_union,
	set_intersection,
	set_difference_left,
	set_difference_right,
};

template <SetOperationType type>
struct SetOperation
{
	template <class T, std::size_t M, std::size_t N, class It>
	constexpr void operator()(const k3::tok3n::detail::static_array<T, M>& lhs, const k3::tok3n::detail::static_array<T, N> rhs, It it)
	{
		using enum SetOperationType;

		auto do_if = [&]<class U>(U&& u, bool cond)
		{
			if (cond)
				*it++ = std::forward<U>(u);
		};

		auto lhs_it = lhs.begin();
		auto rhs_it = rhs.begin();
		auto lhs_end = lhs.end();
		auto rhs_end = rhs.end();
		while (lhs_it != lhs_end || rhs_it != rhs_end)
		{
			if (lhs_it == lhs_end)
				do_if(*rhs_it++, type == set_union || type == set_difference_right);
			else if (rhs_it == rhs_end)
				do_if(*lhs_it++, type == set_union || type == set_difference_left);
			else if (*lhs_it < *rhs_it)
				do_if(*lhs_it++, type == set_union || type == set_difference_left);
			else if (*rhs_it < *lhs_it)
				do_if(*rhs_it++, type == set_union || type == set_difference_right);
			else
			{
				do_if(*lhs_it++, type == set_union || type == set_intersection);
				++rhs_it;
			}
		}
	}
};

using SetUnion           = SetOperation<SetOperationType::set_union>;
using SetIntersection    = SetOperation<SetOperationType::set_intersection>;
using SetDifferenceLeft  = SetOperation<SetOperationType::set_difference_left>;
using SetDifferenceRight = SetOperation<SetOperationType::set_difference_right>;

template <class Op, k3::tok3n::detail::static_array str1, k3::tok3n::detail::static_array str2>
requires decltype(detail::like_static_arrays(str1, str2))::value
consteval auto merged_with()
{
	constexpr auto size = []
	{
		std::size_t size = 0;
		Op{}(str1, str2, CountingInsertIterator(size));
		return size;
	};

	auto str = str1.template create_empty_with_size<size()>();
	Op{}(str1, str2, str.begin());
	return str;
}

template <k3::tok3n::detail::static_array arr>
consteval auto choice(AnyOf<arr>, AnyOf<arr>) // (P | P) == P
{
	return AnyOf<arr>{};
}

template <k3::tok3n::detail::static_array arr>
consteval auto choice(NoneOf<arr>, NoneOf<arr>) // (P | P) == P
{
	return NoneOf<arr>{};
}

template <k3::tok3n::detail::static_array arr>
consteval auto choice(AnyOf<arr>, NoneOf<arr>) // Anything
{
	return NoneOf<arr.template create_empty_with_size<0>()>{};
}

template <k3::tok3n::detail::static_array arr>
consteval auto choice(NoneOf<arr>, AnyOf<arr>) // Anything
{
	return NoneOf<arr.template create_empty_with_size<0>()>{};
}

template <k3::tok3n::detail::static_array lhs, k3::tok3n::detail::static_array rhs>
requires decltype(detail::like_static_arrays(lhs, rhs))::value
consteval auto choice(AnyOf<lhs>, AnyOf<rhs>) //  "ab" |  "bc" == "abc"    <- set_union
{
	return AnyOf<merged_with<SetUnion, lhs, rhs>()>{};
}

template <k3::tok3n::detail::static_array lhs, k3::tok3n::detail::static_array rhs>
requires decltype(detail::like_static_arrays(lhs, rhs))::value
consteval auto choice(NoneOf<lhs>, NoneOf<rhs>) // !"ab" | !"bc" == "b"      <- set_intersection
{
	return NoneOf<merged_with<SetIntersection, lhs, rhs>()>{};
}

template <k3::tok3n::detail::static_array lhs, k3::tok3n::detail::static_array rhs>
requires decltype(detail::like_static_arrays(lhs, rhs))::value
consteval auto choice(AnyOf<lhs>, NoneOf<rhs>) //  "ab" | !"bc" == "c"      <- set_difference
{
	return NoneOf<merged_with<SetDifferenceRight, lhs, rhs>()>{};
}

template <k3::tok3n::detail::static_array lhs, k3::tok3n::detail::static_array rhs>
requires decltype(detail::like_static_arrays(lhs, rhs))::value
consteval auto choice(NoneOf<lhs>, AnyOf<rhs>) // !"ab" |  "bc" == "a"      <- set_difference
{
	return NoneOf<merged_with<SetDifferenceLeft, lhs, rhs>()>{};
}

template <k3::tok3n::detail::parser... P1s, k3::tok3n::detail::parser... P2s>
requires k3::tok3n::detail::parser_compatible_with<Choice<P1s...>, Choice<P2s...>>
consteval auto choice(Choice<P1s...>, Choice<P2s...>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
{
	return Choice<P1s..., P2s...>{};
}

template <k3::tok3n::detail::parser... Ps>
consteval auto choice(Choice<Ps...>, Choice<Ps...>) // (P | P) == P
{
	return Choice<Ps...>{};
}

template <k3::tok3n::detail::parser P2, k3::tok3n::detail::parser_compatible_with<P2>... P1s>
consteval auto choice(Choice<P1s...>, P2) // (P1 | P2) | P3 == (P1 | P2 | P3)
{
	return Choice<P1s..., P2>{};
}

template <k3::tok3n::detail::parser P1, k3::tok3n::detail::parser_compatible_with<P1>... P2s>
consteval auto choice(P1, Choice<P2s...>) // P1 | (P2 | P3) == (P1 | P2 | P3)
{
	return Choice<P1, P2s...>{};
}

template <k3::tok3n::detail::parser P1, k3::tok3n::detail::parser_compatible_with<P1> P2>
consteval auto choice(P1, P2) // default
{
	return Choice<P1, P2>{};
}

template <k3::tok3n::detail::parser P>
consteval auto choice(P, P) // (P | P) == P
{
	return P{};
}

} // namespace k3::tok3n::operators_impl

namespace k3::tok3n {

template <k3::tok3n::detail::parser P1, k3::tok3n::detail::parser_compatible_with<P1> P2>
constexpr auto operator|(P1, P2)
{
	return operators_impl::choice(P1{}, P2{});
}

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::operator|;

} // namespace k3::tok3n::operators
