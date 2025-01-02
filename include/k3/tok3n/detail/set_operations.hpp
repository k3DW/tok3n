// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_SET_OPERATIONS_HPP
#define K3_TOK3N_DETAIL_SET_OPERATIONS_HPP

#include <k3/tok3n/detail/static_array.hpp>

namespace k3::tok3n::detail {

namespace impl {

class counting_insert_iterator
{
public:
	constexpr counting_insert_iterator(std::size_t& count)
		: _count(&count) {}

	constexpr counting_insert_iterator& operator*() { return *this; }
	constexpr counting_insert_iterator& operator++() { return *this; }
	constexpr counting_insert_iterator operator++(int) { return *this; }

	constexpr counting_insert_iterator& operator=(auto&&)
	{
		++*_count;
		return *this;
	}

private:
	std::size_t* _count;
};

enum class set_operation_type
{
	set_union,
	set_intersection,
	set_difference_left,
	set_difference_right,
};

template <set_operation_type type>
struct set_operation
{
	template <class T, std::size_t M, std::size_t N, class It>
	constexpr void operator()(const static_array<T, M>& lhs, const static_array<T, N> rhs, It it)
	{
		using enum set_operation_type;

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

template <set_operation_type Op, static_array str1, static_array str2>
requires (decltype(like_static_arrays(str1, str2))::value)
consteval auto sets_merged_with()
{
	constexpr auto size = []
	{
		std::size_t size_ = 0;
		set_operation<Op>{}(str1, str2, counting_insert_iterator(size_));
		return size_;
	};

	auto str = str1.template create_empty_with_size<size()>();
	set_operation<Op>{}(str1, str2, str.begin());
	return str;
}

} // namespace impl

template <static_array str1, static_array str2>
consteval auto set_union() { return impl::sets_merged_with<impl::set_operation_type::set_union, str1, str2>(); }

template <static_array str1, static_array str2>
consteval auto set_intersection() { return impl::sets_merged_with<impl::set_operation_type::set_intersection, str1, str2>(); }

template <static_array str1, static_array str2>
consteval auto set_difference_left() { return impl::sets_merged_with<impl::set_operation_type::set_difference_left, str1, str2>(); }

template <static_array str1, static_array str2>
consteval auto set_difference_right() { return impl::sets_merged_with<impl::set_operation_type::set_difference_right, str1, str2>(); }

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_SET_OPERATIONS_HPP
