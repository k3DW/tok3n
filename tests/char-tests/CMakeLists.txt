file(GLOB_RECURSE char_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)

tok3n_configure_ide("${char_test_files}")



add_executable(char_tests
    ${char_test_files}
)

tok3n_configure_test_target(char_tests VALUE_TYPE_CHAR)



add_executable(wchar_t_tests
    ${char_test_files}
)

tok3n_configure_test_target(wchar_t_tests VALUE_TYPE_WCHAR_T)
