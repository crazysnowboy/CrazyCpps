
function(get_all_targets _result _dir)
    get_property(_subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
    foreach(_subdir IN LISTS _subdirs)
        get_all_targets(${_result} "${_subdir}")
    endforeach()
    get_property(_sub_targets DIRECTORY "${_dir}" PROPERTY BUILDSYSTEM_TARGETS)
    set(${_result} ${${_result}} ${_sub_targets} PARENT_SCOPE)
endfunction()


function(get_all_incs _result _dir)
    get_property(_subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
    foreach(_subdir IN LISTS _subdirs)
        get_all_incs(${_result} "${_subdir}")
    endforeach()
    get_property(_sub_targets DIRECTORY "${_dir}" PROPERTY INCLUDE_DIRECTORIES)
    set(${_result} ${${_result}} ${_sub_targets} PARENT_SCOPE)
endfunction()



function(get_all_target_incs _result _targes)
    foreach(_target IN LISTS _targes)
        get_target_property(_property ${_target} INTERFACE_INCLUDE_DIRECTORIES )
        set(${_result} ${${_result}} ${_property} PARENT_SCOPE)
    endforeach()

endfunction()


function(add_subdirectory_with_folder module_names _folder force_on_off)

    message("-------------------------------------------------")
    message("               ${module_names}                    ")
    message("-------------------------------------------------")

    separate_arguments(module_names)

    add_subdirectory(${_folder} ${ARGN})
    get_all_targets(_targets "${_folder}")
    foreach(_target IN LISTS _targets)
        set(SET_PROPERTY OFF)
        foreach(module_name  ${module_names})
            if (${module_name} STREQUAL ${_target} AND ${force_on_off})
                set(SET_PROPERTY ON)
            endif ()
            if (${SET_PROPERTY})
                set_target_properties(${_target} PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs"
                        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/libs")
            endif ()
        endforeach()
#        message("${SET_PROPERTY} --------->   ${_target}" )
    endforeach()

#    get_all_incs(dirs_incs "${_folder}")
#    Gobal_Append(MODULES_INCLUDE_DIR "${_folder}")
#    message("-inc--crazy------>   ${_folder}" )
#    foreach(_inc IN LISTS dirs_incs)
#            message("-inc-from-dirs------>   ${_inc}" )
#            Gobal_Append(MODULES_INCLUDE_DIRS "${_inc}")
#    endforeach()


#    foreach(_target IN LISTS _targets)
#        get_all_target_incs(target_incs "${_target}")
#        foreach(_inc IN LISTS target_incs)
#            message("-inc-from-target------>   ${_inc}" )
#        endforeach()
#    endforeach()

    foreach(_target  ${module_names})
        get_all_target_incs(target_incs "${_target}")
        foreach(_inc IN LISTS target_incs)
            if (NOT ${_inc} STREQUAL "_property-NOTFOUND")

#                message("-inc-from-target------>   ${_inc}" )
                Gobal_Append(MODULES_INCLUDE_DIRS "${_inc}")
                Gobal_Append(MODULES_LIBRARIES ${_target})

            endif()

        endforeach()
    endforeach()




endfunction()

#
#
#function(get_info_without_compile _folder)
#
#    message("-------------------------------------------------")
#    message("               ${_folder}                    ")
#    message("-------------------------------------------------")
#
#    add_subdirectory(${_folder} ${ARGN})
#    get_all_targets(_targets "${_folder}")
#    foreach(_target IN LISTS _targets)
#
#        message("----get----->   ${_target}" )
#
#    endforeach()
#endfunction()
#
#
#function(test_new_add_subdirectory_with_folder module_names _folder force_on_off)
#
#    message("-------------------------------------------------")
#    message("               ${module_names}                    ")
#    message("-------------------------------------------------")
#
#    separate_arguments(module_names)
#    foreach(module_name ${module_names})
#        message("-------- ${module_name} --------" )
#    endforeach()
#
#endfunction()
#
#
##set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
##define_property(
##        TARGET
##        PROPERTY FOLDER
##        INHERITED
##        BRIEF_DOCS "Set the folder name."
##        FULL_DOCS  "Use to organize targets in an IDE."
##)
##
##function(add_subdirectory_with_folder _folder_name _folder)
##    add_subdirectory(${_folder} ${ARGN})
##    set_property(DIRECTORY "${_folder}" PROPERTY FOLDER "${_folder_name}")
##endfunction()
