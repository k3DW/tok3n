# Expected variables:
#   ASSEMBLY_NAME
#   TEST_TARGET
#   TEST_DIRECTORY
#   LIST_OF_TESTS_FILE

set(CTEST_FILE "${TEST_DIRECTORY}/CTestTestfile.cmake")

file(READ "${CTEST_FILE}" ctest_file_contents)
string(FIND "${ctest_file_contents}" "${LIST_OF_TESTS_FILE}" found_position)
if(found_position EQUAL -1)
    file(APPEND "${CTEST_FILE}" "include(${LIST_OF_TESTS_FILE})\n")
endif()

file(READ "${LIST_OF_TESTS_FILE}" list_of_tests_contents)
string(REGEX REPLACE
    "(\"[^\r\n]*\") - (\"[^\r\n]*\")([\r\n]+)"
    "add_test([=[\"${ASSEMBLY_NAME} - \\1 - \\2\"]=] ${TEST_DIRECTORY}/${TEST_TARGET}${CMAKE_EXECUTABLE_SUFFIX} \"run\" \\1 \\2)\\3"
    list_of_tests_contents "${list_of_tests_contents}"
)
file(WRITE "${LIST_OF_TESTS_FILE}" "${list_of_tests_contents}")
