#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>
#include <k3/tok3n/parsers/compound/_fwd.h>
#include <vector>

namespace k3::tok3n {

template <Parser P>
struct Maybe;

template <Parser P, IsConst<std::size_t> N>
requires (N::value != 0)
struct Exactly;

template <Parser P>
struct OneOrMore;

template <Parser P>
struct ZeroOrMore;

template <Parser P, ParserCompatibleWith<P> D, IsConst<bool> KeepDelimiters>
struct Delimit;



namespace detail {

template <class T>
class ResultBuilder : ExecutorData<T>
{
	static constexpr bool is_void = std::same_as<T, void>;

	using value_type = typename decltype(
		[]{
			throw;
			if constexpr (is_void)
				return std::type_identity<void>{};
			else
				return std::type_identity<typename T::value_type>{};
		}()
	)::type;

public:
	constexpr ResultBuilder() = default;

	template <class U>
	constexpr void array_assign(std::size_t index, Result<value_type, U>&& result)
	{
		if constexpr (not is_void)
			this->value[index] = *std::move(result);
	}

	template <class U>
	constexpr Result<T, U> success(Input<U> input) &&
	{
		if constexpr (not is_void)
			return { SuccessTag{}, std::move(this->value), input };
		else
			return { SuccessTag{}, input };
	}
};

} // namespace detail

} // namespace k3::tok3n
