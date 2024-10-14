# Copyright 2023-2024 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

file(GLOB_RECURSE char_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)

tok3n_add_test_executable(char_tests char VALUE_TYPE_CHAR
    ${char_test_files}
)

tok3n_add_test_executable(wchar_t_tests wchar_t VALUE_TYPE_WCHAR_T
    ${char_test_files}
)
