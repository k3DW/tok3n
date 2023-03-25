#include "pch.h"
#include <cassert>

struct CharWrapper
{
	constexpr CharWrapper(char chr) : chr(chr) {}

	char chr;
};

template <auto value>
concept True = true;

template <CharWrapper wrapper>
requires True<wrapper>
struct Checker
{
	static constexpr bool check(char c)
	{
		return wrapper.chr == c;
	}
};

int main()
{
	{
		constexpr Checker<'a'> checker;

		constexpr bool compile_time = checker.check('a');
		bool run_time = checker.check('a');

		assert(compile_time); // Passes
		assert(run_time);     // Passes
	}

	[] {
		constexpr Checker<'b'> checker;

		constexpr bool compile_time = checker.check('b');
		bool run_time = checker.check('b');

		assert(compile_time); // Passes
		assert(run_time);     // Fails!! This is wrong
	}();
}

#if 0
#include <iostream>
#include "examples/json.h"
#include "examples/algebraic.h"

int main()
{
	using namespace k3;
	using namespace k3::tok3n;

	constexpr std::string_view json =
		R"({
	"id": "0001",
	"type": "donut",
	"name": "Cake",
	"image":
		{
			"url": "images/0001.jpg",
			"width": 200,
			"height": 200
		},
	"thumbnail":
		{
			"url": "images/thumbnails/0001.jpg",
			"width": 32,
			"height": 32
		}
})";

	using namespace k3::tok3n::examples;

	//auto result = json_parser::number.parse("-1234.5678e+9012");
	auto result = json_parser::string.parse(R"("-1234.5678e+9012tdtrwehfg)");

	//auto json_result = json_parser::JsonValueParser::parse(R"( [  "test"  , true, -1234.5678e+90123 , [  "test"  , true, -1234.5678e+90123 , "" ]   ]      )");
	auto json_result = json_parser::JsonObjectParser::parse(json);

	volatile int x = 0;

	if (json_result)
	{
		auto& val = json_result.value();
		x += val.data.empty() ? 0 : 1;
	}
	else
		std::cout << "Json parse error!!!\n";


	constexpr auto oc = OneChar<"ab">{};
	constexpr auto test = exactly<2>(oc);

	[[maybe_unused]] auto algtest = algebraic::test();

	auto result_ = test.parse("cbac");
	auto result_2 = test.parse("abac");
}
#endif