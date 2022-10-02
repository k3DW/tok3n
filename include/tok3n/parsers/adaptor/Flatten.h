#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

class FlattenExecutor
{
public:
	template <class T>
	constexpr FlattenExecutor(T&& t)
	{
		valid = try_push(std::forward<T>(t));
	}

	constexpr Input flattened() const
	{
		if (not valid)
			throw;
		
		else if (vec.empty())
			return "";
		else
			return { &vec.front().front(), &vec.back().back() + 1 };
	}

private:
	constexpr bool try_push(Input input)
	{
		if (vec.empty() || (&vec.back().back() + 1 == &input.front()))
		{
			vec.push_back(input);
			return true;
		}
		else
			return false;
	}
	
	template <class T>
	constexpr bool try_push(const std::vector<T>& ts)
	{
		for (auto& t : ts)
		{
			if (not try_push(t))
				return false;
		}
		return true;
	}

	template <class T>
	constexpr bool try_push(const std::optional<T>& opt)
	{
		return (not opt.has_value()) || try_push(*opt);
	}

	template <class T, class... Ts>
	constexpr bool try_push(const std::tuple<T, Ts...>& tup)
	{
		return [this, &tup]<std::size_t... Is>(std::index_sequence<Is...>) -> bool
		{
			return (... && try_push(std::get<Is>(tup)));
		}(std::index_sequence_for<T, Ts...>{});
	}

	std::vector<Input> vec;
	bool valid;
};

template <Parser P>
requires Flattenable<typename P::result_type>
struct Flatten
{
	using result_type = Input;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, FlattenExecutor(*result).flattened(), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()
