// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_JOIN_HPP
#define K3_TOK3N_DETAIL_PARSERS_JOIN_HPP

#include <k3/tok3n/detail/helpers.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>
#include <array>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

namespace k3::tok3n::detail {

template <parser P>
struct join_parser;

namespace impl {

struct dummy_visitor
{
	constexpr bool operator()(const auto&)
	{
		return true;
	}
};

template <class T>
concept joinable = span_like<T>
	or optional_like<T>
	or std::ranges::range<T>
	or tuple_like<T>
	or visitable<T, dummy_visitor>;

template <span_like Span>
class join_executor
{
public:
	template <class V, joinable T>
	constexpr join_executor(const result<void, V>& res, const T& t)
	{
		if (try_join(t) && joined == std::nullopt)
		{
			// If the contents are empty, make sure this result is still contiguous
			joined.emplace(res.remaining().data(), std::size_t{0});
		}
	}

	constexpr std::optional<Span> get_joined() &&
	{
		return joined;
	}

private:
	template <joinable T>
	constexpr bool try_join(const T& t)
	{
		if constexpr (span_like<T>)
		{
			if constexpr(std::same_as<typename T::value_type, typename Span::value_type>)
				return try_join_span(t);
			else
				return try_join_range(t);
		}
		else if constexpr (optional_like<T>)
			return try_join_optional(t);
		else if constexpr (std::ranges::range<T>)
			return try_join_range(t);
		else if constexpr (tuple_like<T>)
			return try_join_tuple(t);
		else if constexpr (visitable<T, visitor>)
			return try_join_visitable(t);
	}

	// This is the fundamental function of this class,
	// where we check if the next string_view is adjacent in memory to the last one.
	template <span_like T>
	constexpr bool try_join_span(const T& span)
	{
		if (span.empty())
		{
			return true;
		}
		else if (!joined)
		{
			joined.emplace(span.data(), span.size());
			return true;
		}
#if defined(_MSC_VER)
		else if (joined->data() + joined->size() == span.data())
#elif defined(__GNUC__) || defined(__clang__)
		else if
		(
			(
				not std::is_constant_evaluated() or
				__builtin_constant_p(span.data() - joined->data())
			) and
			static_cast<std::ptrdiff_t>(joined->size()) == span.data() - joined->data()
		)
#else
#error
#endif
		{
			// ^^ If (&joined->back() + 1 == &span.front())
			joined.emplace(joined->data(), joined->size() + span.size());
			return true;
		}
		else
		{
			joined = std::nullopt;
			return false;
		}
	}

	template <std::ranges::range T>
	constexpr bool try_join_range(const T& range)
	{
		for (const auto& element : range)
		{
			if (not try_join(element))
				return false;
		}
		return true;
	}

	template <optional_like T>
	constexpr bool try_join_optional(const T& opt)
	{
		return (not opt.has_value()) || try_join(*opt);
	}

	template <tuple_like T>
	constexpr bool try_join_tuple(const T& tup)
	{
		return [&]<std::size_t... Is>(std::index_sequence<Is...>) -> bool
		{
			return (... && try_join(adl_get<Is>(tup)));
		}(std::make_index_sequence<std::tuple_size_v<T>>{});
	}

	struct visitor
	{
		template <class Element>
		constexpr bool operator()(const Element& element)
		{
			return self.try_join(element);
		}
		join_executor& self;
	};
	friend struct visitor;

	template <visitable<visitor> T>
	constexpr bool try_join_visitable(const T& var)
	{
		return visit(var, visitor{*this});
	}

	std::optional<Span> joined;
};

template <class CRTP>
struct join_parser_base;

template <parser P>
struct join_parser_base<join_parser<P>>
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = output_span<V>;

	static constexpr parser_family family = join_family;

	template <input_constructible_for<value_type> R>
	requires requires (R&& r, result_for<input_value_t<R>>& out) { join_parser<P>::_parse_impl(std::forward<R>(r), out); }
	static constexpr auto parse(R&& r) -> result<result_for<input_value_t<R>>, input_value_t<R>>
	{
		result_for<input_value_t<R>> out;
		return join_parser<P>::_parse_impl(std::forward<R>(r), out)
			.with_value(std::move(out));
	}

	template <input_constructible_for<value_type> R, span_like Out>
	requires requires (R&& r, Out& out) { join_parser<P>::_parse_impl(std::forward<R>(r), out); }
		and std::same_as<input_value_t<R>, typename Out::value_type>
	static constexpr auto parse(R&& r, Out& out) -> result<void, input_value_t<R>>
	{
		return join_parser<P>::_parse_impl(std::forward<R>(r), out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r) -> result<void, input_value_t<R>>
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace impl

template <parser P>
struct join_parser : impl::join_parser_base<join_parser<P>>
{
	friend struct impl::join_parser_base<join_parser<P>>;
	using value_type = typename impl::join_parser_base<join_parser<P>>::value_type;

private:
	template <input_constructible_for<value_type> R, class Out>
	requires impl::joinable<typename P::template result_for<input_value_t<R>>>
	static constexpr result<void, input_value_t<R>> _parse_impl(R&& r, Out& out)
	{
		const input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		typename P::template result_for<V> before;
		result<void, V> res = P::parse(input, before);
		if (res.has_value())
		{
			using Executor = impl::join_executor<Out>;
			std::optional<Out> joined = Executor(res, before).get_joined();
			if (joined)
			{
				out = *std::move(joined);
				return { success_tag, res.remaining() };
			}
		}
		return { failure_tag, input };
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_JOIN_HPP
