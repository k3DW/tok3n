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
