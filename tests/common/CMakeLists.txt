# Copyright 2024-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_library(common INTERFACE)
target_sources(common INTERFACE FILE_SET headers TYPE HEADERS FILES
    include/common.hpp
    include/common/asserts/Parse.hpp
    include/common/fragments/all_pairs_of_samples.hpp
    include/common/fragments/all_samples.hpp
    include/common/fragments/fails_parsing.hpp
    include/common/fragments/has_family.hpp
    include/common/fragments/has_value_type.hpp
    include/common/fragments/is_modifiable_by.hpp
    include/common/fragments/is_not_modifiable_by.hpp
    include/common/fragments/is_not_parser_for.hpp
    include/common/fragments/is_parser_for.hpp
    include/common/fragments/modifier_value.hpp
    include/common/fragments/parser_family.hpp
    include/common/fragments/parser_fragment_builder.hpp
    include/common/fragments/parser_value.hpp
    include/common/fragments/succeeds_parsing.hpp
    include/common/config.hpp
    include/common/samples_list.hpp
    include/common/underlying.hpp
    include/common/wrappers.hpp
    include/samples/adaptor.hpp
    include/samples/basic-char.hpp
    include/samples/basic-non-char.hpp
    include/samples/classes.hpp
    include/samples/compound.hpp
    include/samples/divergent.hpp
    include/samples/functions.hpp
    include/samples/helpers.hpp
    include/samples/macros-char.hpp
    include/samples/macros-common.hpp
    include/samples/macros-non-char.hpp
    include/samples/repeat.hpp
    include/samples/sub_parsers.hpp
)

target_include_directories(common INTERFACE include)

target_link_libraries(common INTERFACE framework)
target_link_libraries(common INTERFACE Boost::preprocessor)

set_target_properties(common
    PROPERTIES
        FOLDER tests
)
