# Copyright 2024 Braden Ganetsky
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

# Expected variables:
#   ASSEMBLY_NAME
#   TEST_TARGET
#   TEST_DIRECTORY
#   LIST_OF_TESTS_FILE

file(READ "${LIST_OF_TESTS_FILE}" list_of_tests_contents)
string(REGEX REPLACE
    "(\"[^\r\n]*\") - (\"[^\r\n]*\")([\r\n]+)"
    "add_test([=[\"${ASSEMBLY_NAME} - \\1 - \\2\"]=] ${TEST_DIRECTORY}/${TEST_TARGET}${CMAKE_EXECUTABLE_SUFFIX} \"run\" \\1 \\2)\\3"
    list_of_tests_contents "${list_of_tests_contents}"
)
file(WRITE "${LIST_OF_TESTS_FILE}" "${list_of_tests_contents}")
