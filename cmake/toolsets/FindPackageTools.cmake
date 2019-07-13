
function(MyFindIncs HINT_DIRS PATH_SUFFIXES_DIRS HeadFiles output_inc_dirs)

    separate_arguments(HeadFiles)
    foreach(header_file  ${HeadFiles})
        find_path (${header_file}_INCLUDES_DIR
                NAMES ${header_file}
                PATHS /usr/local/include
                      /usr/include
                HINTS ${HINT_DIRS}  # addition search dirs
                PATH_SUFFIXES ${PATH_SUFFIXES_DIRS}  # subdirectories
                )

        if (${header_file}_INCLUDES_DIR)
            set(inc_dirs  ${inc_dirs} ${${header_file}_INCLUDES_DIR})
        else (${header_file}_INCLUDES_DIR)
            message (STATUS "Unable to find  header file = " ${header_file})
        endif (${header_file}_INCLUDES_DIR)

    endforeach()
    set(${output_inc_dirs} ${inc_dirs} PARENT_SCOPE)
endfunction(MyFindIncs)


function(MyFindLIBS HINT_DIRS PATH_SUFFIXES_DIRS LIB_FILES output_libs)
    separate_arguments(LIB_FILES)
    foreach(lib_file  ${LIB_FILES})

        find_library (${lib_file}_LIBRARIES
                NAMES ${lib_file}
                PATHS /usr/local/lib
                      /usr/lib
                      /lib

                HINTS ${HINT_DIRS}  # addition search dirs
                PATH_SUFFIXES ${PATH_SUFFIXES_DIRS} # subdirectories
                )


        if (${lib_file}_LIBRARIES)
            set(find_libs  ${find_libs} ${${lib_file}_LIBRARIES})
        else (${lib_file}_LIBRARIES)
            message (STATUS "Unable to find  lib file = " ${lib_file})
        endif (${lib_file}_LIBRARIES)

    endforeach()
    set(${output_libs} ${find_libs} PARENT_SCOPE)

endfunction(MyFindLIBS)

function(REMOVE_DUPES ARG_STR OUTPUT)
    set(ARG_LIST ${ARGS})
    separate_arguments(ARG_LIST)
    list(REMOVE_DUPLICATES ARG_LIST)
    string (REGEX REPLACE "([^\\]|^);" "\\1 " _TMP_STR "${ARG_LIST}")
    string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
    set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

function(MyFindPackages PACKAGE_NAME PACKAGE_DIR INC_PATH_SUFFIXES_DIRS  HEAD_FILES LIBS_PATH_SUFFIXES_DIRS LIB_FILES OUT_FOUND_BOOL OUT_INCS_DIRS OUT_LIBS_DIRS OUTLIBS)


    MyFindIncs(${PACKAGE_DIR}
            ${INC_PATH_SUFFIXES_DIRS}
            ${HEAD_FILES}
            ${PACKAGE_NAME}_INCLUDES_DIRS)

        
    MyFindLIBS(${PACKAGE_DIR}
            ${LIBS_PATH_SUFFIXES_DIRS}
            ${LIB_FILES}
            ${PACKAGE_NAME}_LIBRARIES)


    if (${PACKAGE_NAME}_INCLUDES_DIRS AND ${PACKAGE_NAME}_LIBRARIES)
        set (HAVE_${PACKAGE_NAME} TRUE)
    else (${PACKAGE_NAME}_INCLUDES_DIRS AND ${PACKAGE_NAME}_LIBRARIES)
        if (NOT ${PACKAGE_NAME}_FIND_QUIETLY)
            if (NOT ${PACKAGE_NAME}_INCLUDES_DIRS)
                message (STATUS "Unable to find ${PACKAGE_NAME} header files!")
            endif (NOT ${PACKAGE_NAME}_INCLUDES_DIRS)
            if (NOT ${PACKAGE_NAME}_LIBRARIES)
                message (STATUS "Unable to find ${PACKAGE_NAME} library files!")
            endif (NOT ${PACKAGE_NAME}_LIBRARIES)
        endif (NOT ${PACKAGE_NAME}_FIND_QUIETLY)
    endif (${PACKAGE_NAME}_INCLUDES_DIRS AND ${PACKAGE_NAME}_LIBRARIES)



    if (HAVE_${PACKAGE_NAME})
        if (NOT ${PACKAGE_NAME}_FIND_QUIETLY)
            message (STATUS "Found components for ${PACKAGE_NAME}")
#            message (STATUS "${PACKAGE_NAME}_INCLUDES_DIRS = ${${PACKAGE_NAME}_INCLUDES_DIRS}")
#            message (STATUS "${PACKAGE_NAME}_LIBRARIES     = ${${PACKAGE_NAME}_LIBRARIES}")
        endif (NOT ${PACKAGE_NAME}_FIND_QUIETLY)
    else (HAVE_${PACKAGE_NAME})
        if (${PACKAGE_NAME}_FIND_REQUIRED)
            message (FATAL_ERROR "Could not find ${PACKAGE_NAME}!")
        endif (${PACKAGE_NAME}_FIND_REQUIRED)
    endif (HAVE_${PACKAGE_NAME})

    set(${OUT_INCS_DIRS} ${${PACKAGE_NAME}_INCLUDES_DIRS} PARENT_SCOPE)
    set(${OUT_LIBS_DIRS} ${${PACKAGE_NAME}_LIBRARIES} PARENT_SCOPE)
    set(${OUT_FOUND_BOOL} ${HAVE_${PACKAGE_NAME}} PARENT_SCOPE)



    foreach(lib_path  ${${PACKAGE_NAME}_LIBRARIES})
        get_filename_component(file_path ${lib_path} DIRECTORY)

        #crazy: check if the path already exist in the list
        list(FIND link_paths ${file_path} res)
        if(${res} LESS 0)
            set(link_paths ${link_paths}  ${file_path})
        endif()
    endforeach()
    set(${OUTLIBS} ${link_paths} PARENT_SCOPE)

endfunction(MyFindPackages)
