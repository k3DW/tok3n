macro(tok3n_configure_target target visibility)

    set_target_properties(${target}
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
    )

    target_compile_features(${target}
        ${visibility}
            cxx_std_20
    )

    target_compile_options(${target} ${visibility}
        $<$<CXX_COMPILER_ID:MSVC>:
            /permissive- /volatile:iso /Zc:preprocessor
            /WX /W4
            /w14640
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /we4289
            /w14296
            /w14311
            /w14545
            /w14546
            /w14547
            /w14549
            /w14555
            /w14619
            /w14640
            /w14826
            /w14905
            /w14906
            /w14928
        >
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
            -Werror
            -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
            -Wold-style-cast
            -Wcast-align
            -Wunused
            -Woverloaded-virtual
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wmisleading-indentation
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
            -Wimplicit-fallthrough
        >
        $<$<CXX_COMPILER_ID:GNU>:
            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wuseless-cast
            -Wlifetime
        >
    )

endmacro()

function(tok3n_configure_source_group target)

    get_target_property(list_of_files ${target} SOURCES)

    foreach(_source IN ITEMS ${list_of_files})
        if(${_source} MATCHES "^\\$<") # Skip any unevaluated generator expressions
            continue()
        endif()
        get_filename_component(_source_path "${_source}" DIRECTORY)
        file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_LIST_DIR}" "${_source_path}")
        string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
        source_group("${_group_path}" FILES "${_source}")
    endforeach()

    if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target}.dir/cmake_pch.cxx")
        # https://stackoverflow.com/questions/71070320/cmake-how-to-group-generated-precompiled-headers-in-visual-studio
        source_group("_cmake_generated" FILES "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target}.dir/cmake_pch.cxx")
        foreach(config_type ${CMAKE_CONFIGURATION_TYPES})
            source_group("_cmake_generated" FILES "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target}.dir/${config_type}/cmake_pch.hxx")
        endforeach()
    endif()

endfunction()
