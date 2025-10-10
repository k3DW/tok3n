# Copyright 2023-2025 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_executable(json
    json.cpp
)

tok3n_configure_source_group(json)

set_target_properties(json
    PROPERTIES
        FOLDER examples
)

target_link_libraries(json tok3n_shared_settings)
