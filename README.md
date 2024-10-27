# tok3n

`tok3n` is a header-only C++20 parser combinator library, where everything is valid at compile-time. `tok3n` is created with ergonomics in mind. The syntax is easy to pick up, but I make no promises of a stable API at this time.

## Building

### Compiler support

Support in C++20 mode for:

* Visual Studio 2022
* Clang 16, 17, 18, 19
* GCC 12, 13, 14

### Build `tok3n` with CMake

In the root directory of the repository, run the following.

```none
mkdir build
cd build
cmake [--preset <name>] ..
cmake --build .
```

* If the `--preset` command is missing or if `<name>` is `default`, then this will not build anything. It exposes the header-only library, and nothing else.
* Build the examples when `<name>` is `examples`
* Build the tests when `<name>` is `tests`
* Build the `main()` function (usually for debugging purposes) when `<name>` is `exe`
* Build everything when `<name>` is `all`

### Incorporate `tok3n` into your CMake project

* Find this repo using `add_subdirectory()`, `FetchContent`, or whichever other method you prefer
* Use `target_link_libraries()` either with the target `k3_tok3n` or with its alias `k3::tok3n`
* `#include "k3/tok3n.h"` in your C++ file 

## Usage examples

In all these examples, I will assume the following setup:

```cpp
#include "k3/tok3n.h"
using namespace k3::tok3n;
```

`tok3n` consists of parsers with `parse()` and `lookahead()` static functions. Both functions can take any contiguous range.

### Match a given string

```cpp
constexpr auto abc = "abc"_all;
```

This is a parser that checks for `'a'`, then `'b'`, then `'c'`, in that order.

```cpp
constexpr std::array<char, 4> arr{{ 'a', 'b', 'c', 'd' }};
constexpr auto result = abc.parse(arr);
```

Even though `arr` is a `std::array`, it is still a contiguous range, so this is fine.

```cpp
static_assert(result); // could call `result.has_value()`
static_assert(*result == "abc");
static_assert(result.remaining() == "d");
```

Here, `result` is a `std::optional`-like type. Each of the `static_assert`s above is explained in a bullet point below.

* The parse succeeded, so `result` converts to `true`, like a `std::optional`.
* `result` is dereferenced to grab the contents of the parse. In this case, the `abc` parser outputs a span of `char` equal to `"abc"`. Importantly, this span points to the data inside `arr`. No allocation took place.
* There is 1 element remaining from `arr` that we didn't parse. We can query the remaining contents of the input with the `.remaining()` method, which returns a span of `char`, also pointing to the data inside `arr`.

If we called `lookahead()` instead of `parse()`, then `result`'s stored type would be `void`. There are no parsed contents. The function `lookahead()` simply gives a boolean answer to the question "Can we parse this?". The 1st and 3rd `static_assert`s above would still apply, but the 2nd one would fail to compile.

### Combinators

`tok3n` takes inspiration from other parser combinator libraries like Boost.Spirit, and it tries to maintain a similar syntax of operator overloading.

The parser below shows the overloaded operators.

```cpp
constexpr auto abc = "abc"_all;
constexpr auto xyz = "xyz"_any;
constexpr auto p = ~abc >> !xyz >> (+xyz | *abc);
```

* `abc` parses the characters `'a'`, `'b'`, `'c'` in order, and returns a span of `char` of size 3 if the parse succeeds
* `xyz` parses only one of either `'x'`, `'y'`, or `'z'`, and returns a span of `char` of size 1 if the parse succeeds

`p` is a parser that parses 3 things in order, denoted by the `>>` operator. The `parse()` function will result in a `std::tuple` of the types returned by the sub-parsers respectively. If any of the 3 sub-parsers fails, the whole parse fails.

* `~abc`, the "maybe" operator, either parses an `abc` or it doesn't. Its result type is a `std::optional`. If `"abc"` is present, then the `std::optional` will be engaged with a span of size 3. Otherwise the parse will still succeed, and the `std::optional` will be disengaged.
* `!xyz`, the "not" operator, negates `xyz`. This will parse any character that is _not_ `'x'`, `'y'`, or `'z'`. This `!` operator only works on `""_any` or `""_none` parses, flipping them back and forth.
* `+xyz`, the "one or more" operator, will parse one or more of `xyz`, giving the result as a `std::vector`. This means an input of `"xyzzy"` would be output as a `std::vector` of 5 spans of char, each span with a size of 1.
* `*abc`, the "zero or more" operator, will parse zero or more of `abc`, giving the result as a `std::vector`. The operator `*` is similar to `+`, but it can never fail the parse.
* `(+xyz | *abc)`, with the "choice" operator `|`, is a choice between the left side and the right side.
  * It first checks the left side `+xyz`. If that succeeds, then we short circuit and succeed the parse of the whole choice.
  * If the left side fails, then we check the right side, which determines the success of the whole choice.
  * This will result in a `std::variant` if the left side and right side have different result types. Otherwise, if the types are the same, it will result in that same type. In this case, the result types on both sides are the same.

### Modifiers

There are more transformations on a parser that don't fit within operator overloading. To expand the possible set of transformations, `tok3n` uses "modifiers".

Each modifier `m` can be used on a parser `p` in 2 ways. These are exactly equivalent operations.

* `m(p)`
* `p % m`

The `join` modifier takes care of an annoyance displayed above.

```cpp
constexpr auto p = +"xyz"_any;
```

This parses one or more of the letters `'x'`, `'y'`, or `'z'`. Unfortunately, calling `p.parse("xyzzy")` results in a vector of 5 spans, where each span has a size of 1. This is inconvenient to work with. Alternatively:

```cpp
constexpr auto p = join(+"xyz"_any);
//                 +"xyz"_any % join;
constexpr auto result = p.parse("xyzzy");
static_assert(*result == "xyzzy");
```

Using the `join` modifier flattens all the spans into 1 span, as long as the entire output is contiguous. It does this recursively.

Another important modifier is `ignore`. Take the following parsers `p` and `q`.

```cpp
constexpr auto xyz = "xyz"_any;
constexpr auto p = xyz >> xyz >> xyz;
constexpr auto q = xyz >> ignore(xyz) >> xyz;
```

The `ignore` modifier changes the result type into `void`. It ignores the result. This plays nicely with the sequence operator. Here, `p` will give a result with a `std::tuple` of 3 elements, while `q` will give a result with a `std::tuple` of 2 elements.

This also interacts with `join` in an interesting way.

```cpp
constexpr auto pj = join(p);
constexpr auto qj = join(q);
```

The parser `pj` is fine. It will flatted the tuple-of-3-spans into a single span. On the other hand, `qj` will never succeed a parse. Its 1st element and its 2nd element are not adjacent in memory. There is an ignored element in the middle. This means the output cannot ever be contiguous, so `join` will fail the parse.

Other modifiers include:

* `delimit(pd)` does the equivalent of `p >> *(ignore(pd) >> p)`, except that all parsed elements are put into the same `std::vector`
* `exactly<N>` returns a `std::array` of `N` of the inner result types
* `map<fn>` transforms the result of the inner parser by the invocable `fn`
* `filter<fn>` filters the result of the inner parser by the invocable `fn`
* `into<T>` transforms the result of the inner parser through the constructor of type `T`
* `apply<fn>`, `apply_filter<fn>` and `apply_into<fn>` do the same things as the above 3 respectively, but using `std::apply` instead of `std::invoke`
* `complete` fails the parse if the inner parser left any remaining elements in the input
* `name<"str">` names a parser `"str"`, which has no effect on the output, but rather it is a method of tagging specific parsers for interactions with `sub` explained below
* `sub(...)` is a special modifier that takes "substitutions" as its parameter
  * For example `sub(name<"str"> = ignore)` is a modifier that adds the `ignore` modifier onto each and every inner parser (recursively) that is named `"str"`
  * `sub(...)` is variadic, so you can pass as many substitutions at once
  * The effect of `p % sub(s1) % sub(s2)` is identical to `p % sub(s1, s2)`

Applying modifiers is associative. That is, for any parser `p` and modifiers `m1` and `m2`, the following expressions are identical.

* `(p % m1) % m2`
* `p % (m1 % m2)`
