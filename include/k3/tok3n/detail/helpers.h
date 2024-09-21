#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n::detail {

template <class T>
struct empty_if_void
{
    T value{};
};
template <>
struct empty_if_void<void> {};

template <class T>
class result_builder : empty_if_void<T>
{
	static constexpr bool is_void = std::same_as<T, void>;

public:
	constexpr result_builder() = default;

	template <class U>
	constexpr void assign(result<T, U>&& res)
	{
		if constexpr (not is_void)
			this->value = *std::move(res);
	}

	template <class U>
	constexpr void assign(const result<T, U>& res)
	{
		if constexpr (not is_void)
			this->value = *res;
	}

	template <class T2, class U>
	constexpr void array_assign(std::size_t index, result<T2, U>&& res)
	{
		if constexpr (not is_void)
			this->value[index] = *std::move(res);
	}

	template <std::size_t I, class T2, class U>
	constexpr void get_assign(result<T2, U>&& res)
	{
		if constexpr (not is_void)
			std::get<I>(this->value) = *std::move(res);
	}

	template <class T2, class U>
	constexpr void emplace(result<T2, U>&& res)
	{
		if constexpr (not is_void)
			this->value.emplace(*std::move(res));
	}

	template <std::size_t I, class T2, class U>
	constexpr void emplace(result<T2, U>&& res)
	{
		if constexpr (not is_void)
			this->value.template emplace<I>(*std::move(res));
	}

	template <class T2, class U>
    constexpr void insert_back(result<T2, U>&& res)
    {
        if constexpr (not is_void)
            this->value.insert(this->value.end(), *std::move(res));
    }

	template <class T2, class U>
	constexpr void insert_back_first(result<T2, U>&& res)
	{
		if constexpr (not is_void)
            this->value.first.insert(this->value.first.end(), *std::move(res));
	}

	template <class T2, class U>
	constexpr void insert_back_second(result<T2, U>&& res)
	{
		if constexpr (not is_void)
            this->value.second.insert(this->value.second.end(), *std::move(res));
	}

	template <class U>
	constexpr result<T, U> build(input_span<U> input) &&
	{
		if constexpr (not is_void)
			return { success_tag, std::move(this->value), input };
		else
			return { success_tag, input };
	}
};



namespace impl {

template <class list, template <class...> class Other>
struct change_list;

template <template <class...> class list, class... Ts, template <class...> class Other>
struct change_list<list<Ts...>, Other>
{
	using type = Other<Ts...>;
};

} // namespace impl

template <template <class...> class algorithm, template <class...> class container, class V, parser... Ps>
struct compound_trait
{
private:
	using filtered = algorithm<typename Ps::template result_for<V>...>;

	using unwrapped_trait = unwrap_if_single<typename filtered::type>;

public:
	using sequence = typename filtered::sequence;

	static constexpr bool unwrapped = unwrapped_trait::unwrapped;

	using result_for =
		typename std::conditional_t<unwrapped,
			unwrapped_trait,
			impl::change_list<typename unwrapped_trait::type, container>
		>::type;
};



namespace impl {

enum class compound_type
{
	choice,
	sequence,
};

template <class ResultType, class ValueType, bool unwrapped, compound_type type>
struct compound_executor
{
	input_span<ValueType> input;
	result_builder<ResultType> builder;

	template <parser P, std::size_t I = static_cast<std::size_t>(-1)>
	constexpr bool execute()
	{
		if constexpr (I == static_cast<std::size_t>(-1))
			return execute_lookahead<P>();
		else
			return execute_element<P, I>();
	}

private:
	template <parser P>
	constexpr bool execute_lookahead()
	{
		auto res = P::lookahead(input);
		input = res.remaining();
		return res.has_value();
	}

	template <parser P, std::size_t I>
	constexpr bool execute_element()
	{
		auto res = P::parse(input);
		if (not res.has_value())
			return false;

		input = res.remaining();
		if constexpr (unwrapped)
		{
			if constexpr (std::is_move_assignable_v<ResultType>)
				builder.assign(std::move(res));
			else
				builder.assign(res);
		}
		else
		{
			if constexpr (type == compound_type::choice)
				builder.template emplace<I>(std::move(res));
			else if constexpr (type == compound_type::sequence)
				builder.template get_assign<I>(std::move(res));
			else
				static_assert(std::same_as<ValueType, void>); // always false
		}
		return true;
	}
};

template <class ResultType, class ValueType, bool unwrapped>
using choice_executor = compound_executor<ResultType, ValueType, unwrapped, compound_type::choice>;

template <class ResultType, class ValueType, bool unwrapped>
using sequence_executor = compound_executor<ResultType, ValueType, unwrapped, compound_type::sequence>;

} // namespace impl

} // namespace k3::tok3n::detail
