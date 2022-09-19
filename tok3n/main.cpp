#include "parsers/parsers.h"
#include "operators/operators.h"

#include <iostream>
#if 1

void print(std::string_view str);
template <class... Ts>
void print(const std::tuple<Ts...>& tuple);
template <class T>
void print(const std::vector<T>& vector);
template <class T>
void print(const std::optional<T>& opt);
template <class T>
void print(const k3::parser::Result<T>& result);

void print(std::string_view str)
{
	std::cout << str;
}

template <class... Ts>
void print(const std::tuple<Ts...>& tuple)
{
	[&tuple]<std::size_t... Is>(std::index_sequence<Is...>)
	{
		(..., print(std::get<Is>(tuple)));
	}(std::index_sequence_for<Ts...>{});
}

template <class T>
void print(const std::vector<T>& vector)
{
	for (const auto& element : vector)
		print(element);
}

template <class T>
void print(const std::optional<T>& opt)
{
	if (opt.has_value())
		print(*opt);
}

template <class T>
void print(const k3::parser::Result<T>& result)
{
	if constexpr (std::same_as<T, void>)
	{
		if (result)
		{
			std::cout << "Lookahead parsed successfully";
			std::cout << "\nRemain: " << result.remaining() << "\n\n";
		}
		else
			std::cout << "Parse error\n\n";
	}
	else
	{
		if (result)
		{
			std::cout << "Parsed: ";
			print(result.value());
			std::cout << "\nRemain: " << result.remaining() << "\n\n";
		}
		else
			std::cout << "Parse error\n\n";
	}
}

#include "examples/json.h"

int main()
{
	using namespace k3;
	using namespace k3::parser;


	using OCA = OneChar<'a'>;
	using OCB = OneChar<'b'>;
	using OCC = OneChar<'c'>;

	print(OCA::parse("abc"));
	print(OCB::parse("abc"));

	print(Choice<OCA, OCB, OCC>::parse("bx"));

	std::cout << "\n\n";



	constexpr static_string sdfjksdnf = "asfnjaksd";

	OneChar<"ab"> test;
	OneChar<"ac"> test2;

	auto dkfjsdkf = test | test2;
	static_assert(std::same_as<OneChar<"abc">, decltype(dkfjsdkf)>);

	OneChar<'d'> test3;

	constexpr Choice<OneChar<'a'>, OneChar<'b'>> c1;
	constexpr Choice<OneChar<'c'>, OneChar<'d'>> c2;

	constexpr OneChar<'e'> oc;

	auto c3a = c1 | c2;
	static_assert(std::same_as<Choice<OneChar<'a'>, OneChar<'b'>, OneChar<'c'>, OneChar<'d'>>, decltype(c3a)>);
	auto c3b = c2 | c1;
	static_assert(std::same_as<Choice<OneChar<'c'>, OneChar<'d'>, OneChar<'a'>, OneChar<'b'>>, decltype(c3b)>);

	auto c4a = c1 | oc;
	static_assert(std::same_as<Choice<OneChar<'a'>, OneChar<'b'>, OneChar<'e'>>, decltype(c4a)>);
	auto c4b = oc | c1;
	static_assert(std::same_as<Choice<OneChar<'e'>, OneChar<'a'>, OneChar<'b'>>, decltype(c4b)>);

	auto c5a = c2 | oc;
	static_assert(std::same_as<Choice<OneChar<'c'>, OneChar<'d'>, OneChar<'e'>>, decltype(c5a)>);
	auto c5b = oc | c2;
	static_assert(std::same_as<Choice<OneChar<'e'>, OneChar<'c'>, OneChar<'d'>>, decltype(c5b)>);


	Sequence<OneChar<"abc">, OneChar<"bcd">> seq;
	auto seq2 = seq >> seq;

	print(seq2.parse("abcd"));

	using SEQ1 = Sequence<OneChar<"ab">, OneChar<"bc">>;
	static_assert(std::same_as<decltype(std::declval<SEQ1>() >> std::declval<SEQ1>()), Sequence<OneChar<"ab">, OneChar<"bc">, OneChar<"ab">, OneChar<"bc">>>);


	using OC01 = OneChar<"abc">;
	using OC02 = OneChar<'b'>;
	auto oc01 = OC01{};
	auto oc02 = OC02{};

	using SEQ02 = Sequence<OC01, OC02>;
	auto seq02 = oc01 >> oc02;
	static_assert(std::same_as<SEQ02, decltype(seq02)>);

	using OOM01 = OneOrMore<SEQ02>;
	auto oom01 = +seq02;
	static_assert(std::same_as<OOM01, decltype(oom01)>);
	static_assert(std::same_as<decltype(oom01), decltype(+oom01)>);
	static_assert(std::same_as<decltype(oom01), decltype(+ +oom01)>);
	static_assert(std::same_as<decltype(oom01), decltype(+ + +oom01)>);

	using ZOM01 = ZeroOrMore<SEQ02>;
	auto zom01 = *seq02;
	static_assert(std::same_as<ZOM01, decltype(zom01)>);
	static_assert(std::same_as<decltype(zom01), decltype(*zom01)>);
	static_assert(std::same_as<decltype(zom01), decltype(**zom01)>);
	static_assert(std::same_as<decltype(zom01), decltype(***zom01)>);

	static_assert(std::same_as<ZOM01, decltype(*oom01)>);
	static_assert(std::same_as<ZOM01, decltype(+zom01)>);
	static_assert(std::same_as<ZOM01, decltype(+*oom01)>);
	static_assert(std::same_as<ZOM01, decltype(*+zom01)>);

	std::cout << "\n";
	print(zom01.parse("aabbbcbbaba"));
	std::cout << "\n";
	print(zom01.parse("abbbcbbaba"));

	using ZOO01 = ZeroOrOne<SEQ02>;
	auto zoo01 = ~seq02;
	std::cout << "\n";
	print(zoo01.parse("abbb"));
	std::cout << "\n";
	print(zoo01.parse("aabb"));

	static_assert(std::same_as<ZOO01, decltype(zoo01)>);
	static_assert(std::same_as<ZOO01, decltype(~zoo01)>);
	static_assert(std::same_as<ZOO01, decltype(~~zoo01)>);
	static_assert(std::same_as<ZOO01, decltype(~~~zoo01)>);

	static_assert(std::same_as<ZOM01, decltype(+zoo01)>);
	static_assert(std::same_as<ZOM01, decltype(*zoo01)>);
	static_assert(std::same_as<ZOM01, decltype(~oom01)>);
	static_assert(std::same_as<ZOM01, decltype(~zom01)>);

	std::cout << "\n\n";

	{
		/*
		using namespace Json;
		
		Result res = number.parse("-14324.124e+42this is now the end");
		print(res);

		Result res2 = string.parse(R"("this is a "test string)");
		print(res2);
		
		Result res3 = string.parse(R"("this is another t"est" strin"g")");
		print(res3);
		*/
	}


	static_assert(std::same_as<decltype(zoo01 | zoo01), ZOO01>);



	using OC10 = OneChar<"abc">;
	using NC10 = NotChar<"abc">;
	using NC11 = NotChar<"d">;
	using NC12 = NotChar<"bcd">;

	constexpr OC10 oc10;
	constexpr NC10 nc10;
	constexpr NC11 nc11;
	constexpr NC12 nc12;

	static_assert(std::same_as<decltype(!oc10), NC10>);
	static_assert(std::same_as<decltype(!nc10), OC10>);
	static_assert(std::same_as<decltype(!!nc10), NC10>);
	static_assert(std::same_as<decltype(!!oc10), OC10>);

	static_assert(std::same_as<decltype(nc10 | nc10), NC10>);
	static_assert(std::same_as<decltype(nc11 | nc11), NC11>);
	static_assert(std::same_as<decltype(nc10 | nc11), OneChar<every_char>>);
	static_assert(std::same_as<decltype(nc11 | nc10), OneChar<every_char>>);

	static_assert(std::same_as<decltype(nc10 | oc10), OneChar<every_char>>);
	static_assert(std::same_as<decltype(oc10 | nc10), OneChar<every_char>>);
	static_assert(std::same_as<decltype(nc11 | oc10), NC11>);
	static_assert(std::same_as<decltype(oc10 | nc11), NC11>);
	static_assert(std::same_as<decltype(nc12 | oc10), NotChar<'d'>>);
	static_assert(std::same_as<decltype(oc10 | nc12), NotChar<'d'>>);

	print(NC10::parse("d"));
	print(NC10::parse("a"));
	print(NC10::parse("+"));



	using L01 = Literal<"test">;
	using L02 = Literal<"1234">;

	constexpr L01 l01;
	constexpr L02 l02;

	static_assert(std::same_as<decltype(l01 >> l01), Literal<"testtest">>);
	static_assert(std::same_as<decltype(l01 >> l02), Literal<"test1234">>);
	static_assert(std::same_as<decltype(l02 >> l01), Literal<"1234test">>);
	static_assert(std::same_as<decltype(l02 >> l02), Literal<"12341234">>);


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

	using namespace k3::examples;

	//auto result = json_parser::number.parse("-1234.5678e+9012");
	auto result = json_parser::string.parse(R"("-1234.5678e+9012tdtrwehfg)");

	//auto json_result = json_parser::JsonValueParser::parse(R"( [  "test"  , true, -1234.5678e+90123 , [  "test"  , true, -1234.5678e+90123 , "" ]   ]      )");
	auto json_result = json_parser::JsonObjectParser::parse(json);

	volatile int x = 0;

	if (json_result)
	{
		volatile auto& val = json_result.value();
		x++;
	}
	else
		std::cout << "Json parse error!!!\n";




	{

		print(OneChar<"a">::lookahead("ab"));
		print(NotChar<"a">::lookahead("basdf"));
		print(Literal<"abc">::lookahead("abcdef"));


		using CC = Choice<Literal<"abc">, OneChar<"def">>;
		print(CC::lookahead("abcdef"));
		print(CC::lookahead("fedcba"));

		

	}

}
#endif