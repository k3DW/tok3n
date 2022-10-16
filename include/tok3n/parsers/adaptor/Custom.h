#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <class CRTP>
struct Custom : CustomBase
{
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