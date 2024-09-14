using _11 = All1;
using _12 = Any1;
using _13 = k3::tok3n::detail::choice_parser<All1, Any1>;
using _14 = k3::tok3n::detail::sequence_parser<All1, Any1>;

using _21 = ABC;
using _22 = k3::tok3n::OneOrMore<ABC>;
using _23 = k3::tok3n::Maybe<k3::tok3n::detail::choice_parser<ABC, QQ>>;
using _24 = k3::tok3n::detail::sequence_parser<ABC, k3::tok3n::ZeroOrMore<QQ>>;
using _25 = k3::tok3n::detail::sequence_parser<k3::tok3n::OneOrMore<ABC>, k3::tok3n::Maybe<k3::tok3n::detail::choice_parser<ABC, QQ>>>;
