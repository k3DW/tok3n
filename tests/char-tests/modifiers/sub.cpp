// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("sub modifier");

namespace {

constexpr auto sub11 = (name<"nam1"> = ignore);
constexpr auto sub21 = (name<"nam2"> = join);
constexpr auto sub31 = (name<"nam3"> = name<"nam2">);
constexpr auto sub41 = (name<"nam4"> = exactly<2>);
constexpr auto sub12 = (name<"nam1"> = join);
constexpr auto sub22 = (name<"nam2"> = ignore);
constexpr auto sub32 = (name<"nam3"> = exactly<2>);
constexpr auto sub42 = (name<"nam4"> = name<"nam2">);

} // namespace

template <class S, class... Fragments>
struct sub_fragment_builder
{
    static_assert(detail::substitution<S>, "Must use a substitution type");
    static_assert(std::is_empty_v<S>, "Substitution must be an empty type.");
    void operator()() const
    {
        (..., Fragments{}(S{}));
    }
};

template <detail::substitution auto s>
constexpr auto the_substitution = sub_fragment_builder<std::remove_cvref_t<decltype(s)>>{};

template <class S, class... Fragments, class Frag>
constexpr auto operator|(sub_fragment_builder<S, Fragments...>, Frag)
{
    return sub_fragment_builder<S, Fragments..., Frag>{};
}

template <static_array Name, detail::modifier M>
struct has_name_and_modifier_fragment
{
    template <class S>
    void operator()(S s) const
    {
        EXPECT_COMPILE_AND_RUN_TIME(s.name == Name)
            << "The substitution's name did not match the expected name.\n"
            << "[\n"
            << "    Given name    = " << s.name.view() << "\n"
            << "    Expected name = " << Name.view() << "\n"
            << "]";

        using GivenMod = std::remove_cvref_t<decltype(s.mod)>;
        EXPECT_COMPILE_TIME((std::same_as<GivenMod, M>))
            << "The substitution's modifier did not match the expected modifier.\n"
            << "[\n"
            << "    Given modifier    = " << typeid(GivenMod).name() << "\n"
            << "    Expected modifier = " << typeid(M).name() << "\n"
            << "]";
    }
};
template <static_array Name, detail::modifier auto m>
constexpr auto has_name_and_modifier = has_name_and_modifier_fragment<Name, std::remove_cvref_t<decltype(m)>>{};

TEST("sub modifier", "create substitutions")
{
    EXPECT_THAT(the_substitution<sub11> | (has_name_and_modifier<"nam1", ignore>));
    EXPECT_THAT(the_substitution<sub21> | (has_name_and_modifier<"nam2", join>));
    EXPECT_THAT(the_substitution<sub31> | (has_name_and_modifier<"nam3", name<"nam2">>));
    EXPECT_THAT(the_substitution<sub41> | (has_name_and_modifier<"nam4", exactly<2>>));
    EXPECT_THAT(the_substitution<sub12> | (has_name_and_modifier<"nam1", join>));
    EXPECT_THAT(the_substitution<sub22> | (has_name_and_modifier<"nam2", ignore>));
    EXPECT_THAT(the_substitution<sub32> | (has_name_and_modifier<"nam3", exactly<2>>));
    EXPECT_THAT(the_substitution<sub42> | (has_name_and_modifier<"nam4", name<"nam2">>));

    EXPECT_COMPILE_TIME(sub11.name == sub12.name);
    EXPECT_COMPILE_TIME(sub21.name == sub22.name);
    EXPECT_COMPILE_TIME(sub31.name == sub32.name);
    EXPECT_COMPILE_TIME(sub41.name == sub42.name);
}

TEST("sub modifier", "prefix")
{
    EXPECT_THAT(parser_value<sub(nam1, sub11)>
                         .is<ignore_parser<_21>{}>);
    EXPECT_THAT(parser_value<sub(nam1, sub21)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub31)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub41)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub12)>
                         .is<join_parser<_21>{}>);
    EXPECT_THAT(parser_value<sub(nam1, sub22)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub32)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub42)>
                         .is<nam1>);

    EXPECT_THAT(parser_value<sub(nam2, sub11)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub21)>
                         .is<join_parser<_22>{}>);
    EXPECT_THAT(parser_value<sub(nam2, sub31)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub41)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub12)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub22)>
                         .is<ignore_parser<_22>{}>);
    EXPECT_THAT(parser_value<sub(nam2, sub32)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub42)>
                         .is<nam2>);

    EXPECT_THAT(parser_value<sub(nam3, sub11)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub21)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub31)>
                         .is<(named_parser<_23, "nam2">{})>);
    EXPECT_THAT(parser_value<sub(nam3, sub41)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub12)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub32)>
                         .is<(exactly_parser<_23, index_c<2>>{})>);
    EXPECT_THAT(parser_value<sub(nam3, sub32)>
                         .is<(exactly_parser<_23, index_c<2>>{})>);
    EXPECT_THAT(parser_value<sub(nam3, sub42)>
                         .is<nam3>);

    EXPECT_THAT(parser_value<sub(nam4, sub11)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub21)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub31)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub41)>
                         .is<(exactly_parser<_24, index_c<2>>{})>);
    EXPECT_THAT(parser_value<sub(nam4, sub12)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub22)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub32)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub42)>
                         .is<(named_parser<_24, "nam2">{})>);
}

TEST("sub modifier", "infix")
{
    EXPECT_THAT(parser_value<nam1 % sub(sub11)>
                         .is<ignore_parser<_21>{}>);
    EXPECT_THAT(parser_value<nam1 % sub(sub21)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub31)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub41)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub12)>
                         .is<join_parser<_21>{}>);
    EXPECT_THAT(parser_value<nam1 % sub(sub22)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub32)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub42)>
                         .is<nam1>);

    EXPECT_THAT(parser_value<nam2 % sub(sub11)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub21)>
                         .is<join_parser<_22>{}>);
    EXPECT_THAT(parser_value<nam2 % sub(sub31)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub41)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub12)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub22)>
                         .is<ignore_parser<_22>{}>);
    EXPECT_THAT(parser_value<nam2 % sub(sub32)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub42)>
                         .is<nam2>);

    EXPECT_THAT(parser_value<nam3 % sub(sub11)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub21)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub31)>
                         .is<(named_parser<_23, "nam2">{})>);
    EXPECT_THAT(parser_value<nam3 % sub(sub41)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub12)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub22)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub32)>
                         .is<(exactly_parser<_23, index_c<2>>{})>);
    EXPECT_THAT(parser_value<nam3 % sub(sub42)>
                         .is<nam3>);

    EXPECT_THAT(parser_value<nam4 % sub(sub11)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub21)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub31)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub41)>
                         .is<(exactly_parser<_24, index_c<2>>{})>);
    EXPECT_THAT(parser_value<nam4 % sub(sub12)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub22)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub32)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub42)>
                         .is<(named_parser<_24, "nam2">{})>);
}

TEST("sub modifier", "order-dependent")
{
    EXPECT_THAT(parser_value<nam3 % sub(sub21, sub31)>
                         .is<(named_parser<_23, "nam2">{})>);
    EXPECT_THAT(parser_value<nam3 % sub(sub31, sub21)>
                         .is<join_parser<_23>{}>);
}

TEST("sub modifier", "chainable")
{
    EXPECT_THAT(parser_value<nam3 % sub(sub21, sub31)>
                         .is<nam3 % sub(sub21) % sub(sub31)>);
    EXPECT_THAT(parser_value<nam3 % sub(sub31, sub21)>
                         .is<nam3 % sub(sub31) % sub(sub21)>);
}

TEST("sub modifier", "non consteval")
{
    (sub(nam1, sub11)).parse(TT("abc"));
    (nam1 % sub(sub11)).parse(TT("abc"));
}

} // namespace
} // namespace k3::tok3n::tests
