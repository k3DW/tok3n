cmake_minimum_required (VERSION 3.26)

project (k3_tok3n
         VERSION 0
         LANGUAGES CXX)


#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(k3_tok3n INTERFACE)
set_target_properties(k3_tok3n PROPERTIES CXX_STANDARD 20)
target_compile_features(k3_tok3n INTERFACE cxx_std_20)

target_include_directories(k3_tok3n INTERFACE include)

option (tok3n_BUILD_TESTS "Build tests" ON)



#--------------------------------------------
#   Tests
#--------------------------------------------
if (tok3n_BUILD_TESTS)
    add_subdirectory(tests)
endif()



#--------------------------------------------
#   Visual Studio
#--------------------------------------------
file(GLOB_RECURSE list_of_files
     LIST_DIRECTORIES false
     "include/*.h"
     "src/main.cpp"
)

add_executable(tok3n
    ${list_of_files}
)

target_include_directories(tok3n PUBLIC include)

set_target_properties(tok3n
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

foreach(_source IN ITEMS ${list_of_files})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_LIST_DIR}/include" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
