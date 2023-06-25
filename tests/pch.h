#pragma once
#include <k3/tok3n.h>

#include "traits.h"
#include "framework/assert.h"
#include "framework/comparison.h"
#include "framework/parse.h"
#include "framework/underlying.h"
#include "samples/adaptor.h"
#include "samples/basic.h"
#include "samples/classes.h"
#include "samples/compound.h"
#include "samples/divergent.h"
#include "samples/functions.h"
#include "samples/repeat.h"

namespace k3::tok3n::tests {

constexpr auto the_parser_list = adaptor_list + basic_list + compound_list + divergent_list + repeat_list;

consteval bool check_all_samples(auto checker)
{
	return [checker]<Parser... Ps>(parser_list<Ps...>) -> bool
	{
		return (... && checker(Ps{}));
	}(the_parser_list);
}

} // namespace k3::tok3n::tests
