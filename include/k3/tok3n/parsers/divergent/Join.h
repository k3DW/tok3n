#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

namespace detail::executors
{

	class Join
	{
	public:
		template <class T>
		constexpr Join(const Result<T>& t)
		{
			if (this->try_join(*t) && joined == std::nullopt)
			{
				// If the contents are empty, make sure this result is still contiguous
				joined = { t.remaining().data(), 0 };
			}
		}

		constexpr std::optional<Input> get_joined() const
		{
			return joined;
		}

	private:
		// This is the fundamental function of this class,
		// where we check if the next string_view is adjacent in memory to the last one.
		constexpr bool try_join(Input input)
		{
			if (!joined)
			{
				joined = input;
				return true;
			}
			else if (joined->data() + joined->size() == input.data())
			{
				// ^^ If (&joined->back() + 1 == &input.front())
				*joined = { joined->data(), joined->size() + input.size() };
				return true;
			}
			else
				return false;
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

		std::optional<Input> joined;
	};

}

template <Parser P>
requires JoinConstructible<P>
struct Join
{
	using result_type = Input;

	static constexpr ParserType type = JoinType;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
		{
			using Executor = detail::executors::Join;
			std::optional<Input> joined = Executor(result).get_joined();
			if (joined)
				return { success, *joined, result.remaining() };
		}
		return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
