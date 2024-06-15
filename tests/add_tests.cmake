# Expected variables:
#   TEST_TARGET
#   TEST_DIRECTORY
#   LIST_OF_TESTS_FILE

set(CTEST_FILE "${TEST_DIRECTORY}/CTestTestfile.cmake")

file(READ "${CTEST_FILE}" file_contents)
string(REGEX REPLACE "([\r\n]+)[^#].+[\n\r]+" "\\1" file_contents "${file_contents}")
file(WRITE "${CTEST_FILE}" "${file_contents}")

file(STRINGS "${LIST_OF_TESTS_FILE}" LIST_OF_TESTS)

foreach(TEST_NAME IN ITEMS ${LIST_OF_TESTS})
    string(REGEX MATCH "^(\".*\") - (\".*\")$" _ "${TEST_NAME}")
    file(APPEND "${CTEST_FILE}"
        "add_test("
        "[=[\"${CMAKE_MATCH_1} - ${CMAKE_MATCH_2}\"]=] "
        "${TEST_DIRECTORY}/${TEST_TARGET}${CMAKE_EXECUTABLE_SUFFIX} "
        "\"run\" "
        "${CMAKE_MATCH_1} "
        "${CMAKE_MATCH_2}"
        ")\n"
    )
endforeach()
