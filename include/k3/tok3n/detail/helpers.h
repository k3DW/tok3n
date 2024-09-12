#pragma once
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
	constexpr result_builder() = default;

	template <class U>
	constexpr void array_assign(std::size_t index, result<value_type, U>&& res)
	{
		if constexpr (not is_void)
			this->value[index] = *std::move(res);
	}

	template <class U>
	constexpr void emplace(result<value_type, U>&& res)
	{
		if constexpr (not is_void)
			this->value.emplace(*std::move(res));
	}

    template <class U>
    constexpr void insert_back(result<value_type, U>&& res)
    {
        if constexpr (not is_void)
            this->value.insert(this->value.end(), *std::move(res));
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

} // namespace k3::tok3n::detail
