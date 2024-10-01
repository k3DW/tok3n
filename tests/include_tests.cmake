# Expected variables:
#   TEST_DIRECTORY
#   LIST_OF_TESTS_FILE

set(CTEST_FILE "${TEST_DIRECTORY}/CTestTestfile.cmake")

file(READ "${CTEST_FILE}" ctest_file_contents)
string(FIND "${ctest_file_contents}" "${LIST_OF_TESTS_FILE}" found_position)
if(found_position EQUAL -1)
    file(APPEND "${CTEST_FILE}" "include(${LIST_OF_TESTS_FILE})\n")
endif()
