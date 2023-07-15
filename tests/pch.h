#pragma once
#include <k3/tok3n.h>

#include "framework/Assert.h"
#include "framework/AssertParse.h"
#include "framework/comparison.h"
#include "framework/Error.h"
#include "framework/Fixture.h"
#include "framework/FixtureResult.h"
#include "framework/parser_list.h"
#include "framework/Test.h"
#include "framework/TestResult.h"
#include "framework/underlying.h"
#include "samples/adaptor.h"
#include "samples/basic.h"
#include "samples/classes.h"
#include "samples/compound.h"
#include "samples/divergent.h"
#include "samples/functions.h"
#include "samples/repeat.h"

using namespace k3::tok3n;

constexpr auto the_parser_list = adaptor_list + basic_list + compound_list + divergent_list + repeat_list;

consteval bool check_all_samples(auto checker)
{
	return [checker]<Parser... Ps>(parser_list<Ps...>) -> bool
	{
		return (... && checker(Ps{}));
	}(the_parser_list);
}

constexpr bool check_all_sample_pairs(auto checker)
{
	auto inner = [checker] <Parser LHS, Parser... RHS>(LHS, parser_list<RHS...>) -> bool
	{
		return (... && checker(LHS{}, RHS{}));
	};

	auto outer = [inner] <Parser... Ps>(parser_list<Ps...>) -> bool
	{
		return (... && inner(Ps{}, parser_list<Ps...>{}));
	};

	return outer(the_parser_list);
}
