file(GLOB_RECURSE char_test_files
     LIST_DIRECTORIES false
     "./*.h"
     "./*.cpp"
)



add_executable(char_tests
    ${char_test_files}
)

tok3n_configure_ide(char_tests)
tok3n_configure_test_target(char_tests VALUE_TYPE_CHAR)



add_executable(wchar_t_tests
    ${char_test_files}
)

tok3n_configure_ide(wchar_t_tests)
tok3n_configure_test_target(wchar_t_tests VALUE_TYPE_WCHAR_T)
