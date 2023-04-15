#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

TOK3N_BEGIN_NAMESPACE()

template <class CRTP>
struct Custom
{
	static constexpr ParserType type = CustomType;

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<typename P::result_type> parse(Input input)
	{
		return decltype(P::get_parser())::parse(input);
	}

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<void> lookahead(Input input)
	{
		return decltype(P::get_parser())::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()

TOK3N_BEGIN_NAMESPACE(inline operators)
using k3::tok3n::Custom;
TOK3N_END_NAMESPACE(inline operators)
