#pragma once
#include <algorithm>
#include <array>
#include <iterator>
#include <optional>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "util/static_string.h"

#include "parsers/parsers.h"
#include "operators/operators.h"

namespace k3::parser
{




	template <static_string str>
	constexpr auto operator!(OneChar<str>)
	{
		return NotChar<str>{};
	}
	template <static_string str>
	constexpr auto operator!(NotChar<str>)
	{
		return OneChar<str>{};
	}










}