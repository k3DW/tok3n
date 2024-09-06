#include "samples.h"

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

#define ASSERT_SUBSTITUTION_TYPE(SUB, NAME, SUBBED)                                                                       \
    ASSERT(IsSubstitution<decltype(SUB)>, #SUB " is expected to satisfy IsSubstitution concept.");                        \
    ASSERT(std::is_empty_v<decltype(SUB)>, #SUB " is expected to be an empty type.");                                     \
    ASSERT((std::same_as<std::remove_cvref_t<decltype(SUB)>, Substitution<NAME, std::remove_cvref_t<decltype(SUBBED)>>>), \
        #SUB " must be the same as Substitution<" NAME ", decltype(" #SUBBED ").")

#define ASSERT_SUBSTITUTION_SAME_NAME(SUB1, SUB2)                                    \
    ASSERT((not std::same_as<decltype(SUB1), decltype(SUB2)>),                       \
        #SUB1 " and " #SUB2 " must not be the same type.");                          \
    ASSERT(SUB1.name == SUB2.name, #SUB1 " and " #SUB2 " must have the same name."); \
    ASSERT((not std::same_as<decltype(SUB1.mod), decltype(SUB2.mod)>),               \
        #SUB1 " and " #SUB2 " must not have the same substituted modifier.")

TEST("sub modifier", "create substitutions")
{
    ASSERT_SUBSTITUTION_TYPE(sub11, "nam1", ignore);
    ASSERT_SUBSTITUTION_TYPE(sub21, "nam2", join);
    ASSERT_SUBSTITUTION_TYPE(sub31, "nam3", name<"nam2">);
    ASSERT_SUBSTITUTION_TYPE(sub41, "nam4", exactly<2>);
    ASSERT_SUBSTITUTION_TYPE(sub12, "nam1", join);
    ASSERT_SUBSTITUTION_TYPE(sub22, "nam2", ignore);
    ASSERT_SUBSTITUTION_TYPE(sub32, "nam3", exactly<2>);
    ASSERT_SUBSTITUTION_TYPE(sub42, "nam4", name<"nam2">);

    ASSERT_SUBSTITUTION_SAME_NAME(sub11, sub12);
    ASSERT_SUBSTITUTION_SAME_NAME(sub21, sub22);
    ASSERT_SUBSTITUTION_SAME_NAME(sub31, sub32);
    ASSERT_SUBSTITUTION_SAME_NAME(sub41, sub42);
}

TEST("sub modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub11), Ignore<_21>{});
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub21), nam1);
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub31), nam1);
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub41), nam1);
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub12), Join<_21>{});
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub22), nam1);
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub32), nam1);
	ASSERT_PARSER_VALUES_EQ(sub(nam1, sub42), nam1);

	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub11), nam2);
	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub21), Join<_22>{});
	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub31), nam2);
	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub41), nam2);
	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub12), nam2);
	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub22), Ignore<_22>{});
	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub32), nam2);
	ASSERT_PARSER_VALUES_EQ(sub(nam2, sub42), nam2);

	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub11), nam3);
	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub21), nam3);
	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub31), (Named<_23, "nam2">{}));
	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub41), nam3);
	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub12), nam3);
	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub22), nam3);
	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub32), (Exactly<_23, detail::index_c<2>>{}));
	ASSERT_PARSER_VALUES_EQ(sub(nam3, sub42), nam3);

	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub11), nam4);
	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub21), nam4);
	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub31), nam4);
	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub41), (Exactly<_24, detail::index_c<2>>{}));
	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub12), nam4);
	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub22), nam4);
	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub32), nam4);
	ASSERT_PARSER_VALUES_EQ(sub(nam4, sub42), (Named<_24, "nam2">{}));
}

TEST("sub modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub11), Ignore<_21>{});
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub21), nam1);
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub31), nam1);
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub41), nam1);
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub12), Join<_21>{});
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub22), nam1);
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub32), nam1);
	ASSERT_PARSER_VALUES_EQ(nam1 % sub(sub42), nam1);

	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub11), nam2);
	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub21), Join<_22>{});
	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub31), nam2);
	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub41), nam2);
	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub12), nam2);
	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub22), Ignore<_22>{});
	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub32), nam2);
	ASSERT_PARSER_VALUES_EQ(nam2 % sub(sub42), nam2);

	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub11), nam3);
	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub21), nam3);
	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub31), (Named<_23, "nam2">{}));
	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub41), nam3);
	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub12), nam3);
	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub22), nam3);
	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub32), (Exactly<_23, detail::index_c<2>>{}));
	ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub42), nam3);

	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub11), nam4);
	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub21), nam4);
	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub31), nam4);
	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub41), (Exactly<_24, detail::index_c<2>>{}));
	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub12), nam4);
	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub22), nam4);
	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub32), nam4);
	ASSERT_PARSER_VALUES_EQ(nam4 % sub(sub42), (Named<_24, "nam2">{}));
}

TEST("sub modifier", "order-dependent")
{
    ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub21, sub31), (Named<_23, "nam2">{}));
    ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub31, sub21), Join<_23>{});
}

TEST("sub modifier", "chainable")
{
    ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub21, sub31), nam3 % sub(sub21) % sub(sub31));
    ASSERT_PARSER_VALUES_EQ(nam3 % sub(sub31, sub21), nam3 % sub(sub31) % sub(sub21));
}

TEST("sub modifier", "non consteval")
{
	(sub(nam1, sub11)).parse(TT("abc"));
	(nam1 % sub(sub11)).parse(TT("abc"));
}
