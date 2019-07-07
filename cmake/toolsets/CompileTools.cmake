# message("----------" ${LIBRARIES})


macro(add_subdirectory_ex arg)
#    message(STATUS "---------${arg} scanning---------")
    add_subdirectory(${arg})
#    message(STATUS "---------${arg} finished---------")
endmacro()


macro(TestMacro)

    message(STATUS "----ARGC-----${ARGC}---------")
    message(STATUS "----ARGV-----${ARGV}---------")
    message(STATUS "----ARGN-----${ARGN}---------")

    message(STATUS "----ARGV0-----${ARGV0}---------")
    message(STATUS "----ARGV1-----${ARGV1}---------")
    message(STATUS "----ARGV2-----${ARGV2}---------")
    message(STATUS "----ARGV3-----${ARGV3}---------")

    foreach(arg ${ARGN})
        message(STATUS "---------${arg}---------")
    endforeach()
endmacro()


macro(CompileCLib path module_name)
    foreach(src_dir ${path})
        file(GLOB_RECURSE CtoLIB_SRCS_c "${src_dir}/*.c")
        set(toLIB_SRCS_c ${CtoLIB_SRCS_c})
    endforeach()
    if(toLIB_SRCS_c)

        if(BUILD_SHARED_LIBS)
            add_library(${module_name}_c SHARED ${toLIB_SRCS_c})
        else()
            add_library(${module_name}_c STATIC ${toLIB_SRCS_c})
        endif()

        link_libraries(${module_name}_c ${LIBRARIES})
        set_target_properties(${module_name}_c PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs")

        Gobal_Append(LOCAL_LIBRARIES ${module_name}_c)

    endif()
endmacro()


macro(CompileCppLib path module_name)

    foreach(src_dir ${path})
        file(GLOB_RECURSE CtoLIB_SRCS_cc "${src_dir}/*.cc")
        file(GLOB_RECURSE CPPtoLIB_SRCS_cpp "${src_dir}/*.cpp")
        set(toLIB_SRCS_cc  ${CtoLIB_SRCS_cc} ${CPPtoLIB_SRCS_cpp})
    endforeach()


    if(toLIB_SRCS_cc)
        if(BUILD_SHARED_LIBS)
            add_library(${module_name} SHARED ${toLIB_SRCS_cc} )
        else()
            add_library(${module_name} STATIC ${toLIB_SRCS_cc} )
        endif()
        link_libraries(${module_name}  ${LOCAL_LIBS} ${LIBRARIES})
        set_target_properties(${PROJECT_NAME} PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs")

        Gobal_Append(LOCAL_LIBRARIES ${module_name})

    endif()
endmacro()



macro(CompileC_CPP_Lib inc_root src_root module_name cxxflag)

    foreach(src_dir ${src_root})
        file(GLOB_RECURSE CtoLIB_SRCS_c "${src_dir}/*.c")
        file(GLOB_RECURSE CtoLIB_SRCS_cc "${src_dir}/*.cc")
        file(GLOB_RECURSE CPPtoLIB_SRCS_cpp "${src_dir}/*.cpp")
        set(toLIB_SRCS_cc  ${CtoLIB_SRCS_cc} ${CPPtoLIB_SRCS_cpp} ${CtoLIB_SRCS_c})
    endforeach()

    foreach(inc_dir ${inc_root})
        file(GLOB_RECURSE CtoLIB_H "${inc_dir}/*.h")
        file(GLOB_RECURSE CtoLIB_HPP "${inc_dir}/*.hpp")
        set(toLIB_INCS_HEADER  ${CtoLIB_H} ${CtoLIB_HPP})
    endforeach()


    if(toLIB_SRCS_cc OR toLIB_SRCS_c)
        if(BUILD_SHARED_LIBS)
            add_library(${module_name} SHARED ${toLIB_SRCS_cc} ${toLIB_SRCS_c} ${toLIB_INCS_HEADER})
        else()
            add_library(${module_name} STATIC ${toLIB_SRCS_cc} ${toLIB_SRCS_c} ${toLIB_INCS_HEADER})
        endif()
        link_libraries(${module_name}  ${LIBRARIES})
        set_target_properties(${module_name} PROPERTIES
                INSTALL_RPATH_USE_LINK_PATH TRUE
                ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs")

        target_compile_features(${module_name} PRIVATE cxx_std_14)

        Gobal_Append(LOCAL_LIBRARIES ${module_name})

    endif()
endmacro()



macro(CompileMain MAIN_PATHS type)
    file(GLOB_RECURSE ForExe_SRCS "${MAIN_PATHS}/${type}")
    if(ForExe_SRCS)
        foreach(source ${ForExe_SRCS})
            get_filename_component(SourceName ${source} NAME_WE)
            set(ExeName ${SourceName}_cpp)
            # target
            set(SRCS_ALL ${source})
            add_executable(${ExeName} ${SRCS_ALL})
            # link library
            target_link_libraries(${ExeName}
                    ${LIBRARIES}
                    )
            set_target_properties(${ExeName} PROPERTIES
                    INSTALL_RPATH TRUE
                    INSTALL_RPATH_USE_LINK_PATH TRUE
                    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
                    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

            target_compile_features(${ExeName} PRIVATE cxx_std_14)
            install(TARGETS ${ExeName}
                    CONFIGURATIONS Release
                    DESTINATION bin)

        endforeach(source)
    endif()
endmacro()



function(CompileLib inc_root src_root modules_list)

    separate_arguments(modules_list)
    foreach(module_name  ${modules_list})

            CompileC_CPP_Lib(${inc_root} ${src_root}/${module_name} ${module_name} 14)
            install(TARGETS ${module_name}
                    CONFIGURATIONS Release
                    DESTINATION lib)
    endforeach()

endfunction()
