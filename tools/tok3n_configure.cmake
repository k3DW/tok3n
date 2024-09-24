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
        >
    )

endmacro()

function(tok3n_configure_ide list_of_files)

    if (TOK3N_SETUP_IDE)

        foreach(_source IN ITEMS ${list_of_files})
            get_filename_component(_source_path "${_source}" PATH)
            file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_LIST_DIR}" "${_source_path}")
            string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
            source_group("${_group_path}" FILES "${_source}")
        endforeach()

        if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/tests.dir/cmake_pch.cxx")

            # https://stackoverflow.com/questions/71070320/cmake-how-to-group-generated-precompiled-headers-in-visual-studio
            source_group("_cmake_generated" FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/tests.dir/cmake_pch.cxx)
            foreach(config_type ${CMAKE_CONFIGURATION_TYPES})
                source_group("_cmake_generated" FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/tests.dir/${config_type}/cmake_pch.hxx)
            endforeach()

        endif()

    endif()

endfunction()
