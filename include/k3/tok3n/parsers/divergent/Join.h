#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

namespace detail::executors
{

	template <class ValueType>
	class Join
	{
	public:
		template <class T>
		constexpr Join(const Result<T, ValueType>& t)
		{
			if (this->try_join(*t) && joined == std::nullopt)
			{
				// If the contents are empty, make sure this result is still contiguous
				joined = { t.remaining().data(), 0 };
			}
		}

		constexpr std::optional<Output<ValueType>> get_joined() const
		{
			return joined;
		}

	private:
		// This is the fundamental function of this class,
		// where we check if the next string_view is adjacent in memory to the last one.
		constexpr bool try_join(Output<ValueType> output)
		{
			if (!joined)
			{
				joined = output;
				return true;
			}
			else if (joined->data() + joined->size() == output.data())
			{
				// ^^ If (&joined->back() + 1 == &output.front())
				*joined = { joined->data(), joined->size() + output.size() };
				return true;
			}
			else
			{
				joined = std::nullopt;
				return false;
			}
		}

		template <class T>
		constexpr bool try_join(const std::vector<T>& ts)
		{
			for (auto& t : ts)
			{
				if (not this->try_join(t))
					return false;
			}
			return true;
		}

		template <class T, std::size_t N>
		constexpr bool try_join(const std::array<T, N>& arr)
		{
			for (auto& t : arr)
			{
				if (not this->try_join(t))
					return false;
			}
			return true;
		}

		template <class T>
		constexpr bool try_join(const std::optional<T>& opt)
		{
			return (not opt.has_value()) || this->try_join(*opt);
		}

		template <class T, class... Ts>
		constexpr bool try_join(const std::tuple<T, Ts...>& tup)
		{
			return[this, &tup]<std::size_t... Is>(std::index_sequence<Is...>) -> bool
			{
				return (... && this->try_join(std::get<Is>(tup)));
			}(std::index_sequence_for<T, Ts...>{});
		}

		std::optional<Output<ValueType>> joined;
	};

}

template <Parser P>
requires JoinConstructible<P>
struct Join
{
	using value_type = typename P::value_type;
	using result_type = Output<value_type>;

	static constexpr ParserFamily family = JoinFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return parse<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input)
	{
		auto result = P::parse(input);
		if (result.has_value())
		{
			using Executor = detail::executors::Join<V>;
			std::optional<Output<V>> joined = Executor(result).get_joined();
			if (joined)
				return { success, *joined, result.remaining() };
		}
		return { failure, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return lookahead<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
	{
		return P::lookahead(input);
	}
};

template <Parser P>
requires JoinConstructible<P>
constexpr auto pretty(Join<P>)
{
	return StaticArray("Join<") + pretty(P{}) + StaticArray(">");
}

} // namespace k3::tok3n
