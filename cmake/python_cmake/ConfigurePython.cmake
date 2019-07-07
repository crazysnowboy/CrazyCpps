set(HEAD_DIRS   ${PROJECT_SOURCE_DIR}/include/CrazyCppLib

        )
set(SRCS_DIRS   ${PROJECT_SOURCE_DIR}/src/CrazyCppLib
        )

# set(PYTHON_ROOT /home/collin/.conda/envs/ai)
set(PYTHON_ROOT /home/collin/anaconda3/envs/blender)

Gobal_Append( LOCAL_LIBRARIES "${PYTHON_ROOT}/lib/libpython3.5m.so")


set(PYLIB_DESTINATION ${PROJECT_SOURCE_DIR}/python/core/cpplib)

foreach(HEAD_DIR ${HEAD_DIRS})
    file(GLOB_RECURSE files_hpp_i "${HEAD_DIR}/*.hpp")
    file(GLOB_RECURSE files_h_i "${HEAD_DIR}/*.h")

    LIST(APPEND files_hpp ${files_hpp_i})
    LIST(APPEND files_h ${files_h_i})

endforeach(HEAD_DIR)


foreach(SRCS_DIR ${SRCS_DIRS})
    file(GLOB_RECURSE CtoLIB_SRCS_c_i "${SRCS_DIR}/*.c")
    file(GLOB_RECURSE CtoLIB_SRCS_cc_i "${SRCS_DIR}/*.cc")
    file(GLOB_RECURSE CPP_SRCS_i "${SRCS_DIR}/*.cpp")

    list(APPEND CtoLIB_SRCS_c ${CtoLIB_SRCS_c_i})
    list(APPEND CtoLIB_SRCS_cc ${CtoLIB_SRCS_cc_i})
    list(APPEND CPP_SRCS ${CPP_SRCS_i})

endforeach(SRCS_DIR)

set(CPP_SRCS ${CPP_SRCS} ${CtoLIB_SRCS_c} ${CtoLIB_SRCS_cc})



set(mid_file_save_path ${PYLIB_DESTINATION}/cmake_generated)

#--------------headers.h---------------------
foreach(file ${files_hpp})
    list(APPEND incs "#include \"${file}\"\n")
endforeach(file)
foreach(file ${files_h})
    list(APPEND incs "#include \"${file}\" \n")
endforeach(file)
file(WRITE ${mid_file_save_path}/headers.h ${incs})

##--------------incs_for_wrap.i---------------------
foreach(file ${files_hpp})
    list(APPEND incs_2 "%include \"${file}\"\n")
endforeach(file)
foreach(file ${files_h})
    list(APPEND incs_2 "%include \"${file}\" \n")
endforeach(file)
file(WRITE ${mid_file_save_path}/incs_for_wrap.i ${incs_2})


##--------------module x.i---------------------
include(cmake/python_cmake/python_i_template.cmake)
file(WRITE ${PYLIB_DESTINATION}/py${PROJECT_NAME}.i ${PTHON_I_TEMPLATE})

##--------------numpy.i---------------------

file(COPY ${PROJECT_SOURCE_DIR}/cmake/python_cmake/numpy.i DESTINATION ${PYLIB_DESTINATION}/swig )


cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)


find_package(SWIG REQUIRED)
include(UseSWIG)
include_directories(${PYTHON_ROOT}/include
                    ${PYTHON_ROOT}/include/python3.5m
                    ${PYLIB_DESTINATION}
                    ${PYTHON_ROOT}/lib/python3.5/site-packages/numpy/core/include)

if(${SWIG_FOUND})
        message(" SWIG Found SWIG_DIR  = " ${SWIG_DIR})
        message(" SWIG Found SWIG_EXECUTABLE  = " ${SWIG_EXECUTABLE})
        message(" SWIG Found SWIG_VERSION  = " ${SWIG_VERSION})
endif()
set_property(   SOURCE ${PYLIB_DESTINATION}/py${PROJECT_NAME}.i
                PROPERTY CPLUSPLUS ON)



set (UseSWIG_TARGET_NAME_PREFERENCE STANDARD)
set(PythonLIBName py${PROJECT_NAME})


swig_add_library(${PythonLIBName}
        LANGUAGE python
        TYPE SHARED
        OUTPUT_DIR ${PYLIB_DESTINATION}
        OUTFILE_DIR ${PYLIB_DESTINATION}/outfile_dir
        SOURCES ${PYLIB_DESTINATION}/py${PROJECT_NAME}.i ${CPP_SRCS})

TARGET_LINK_LIBRARIES(${PythonLIBName} ${LIBRARIES} ${LOCAL_LIBS}
                ${PYTHON_ROOT}/lib/libpython3.5m.so
                -lz)

set_target_properties(${PythonLIBName} PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE
        ARCHIVE_OUTPUT_DIRECTORY "${PYLIB_DESTINATION}/archive"
        LIBRARY_OUTPUT_DIRECTORY "${PYLIB_DESTINATION}/libs"
        RUNTIME_OUTPUT_DIRECTORY "${PYLIB_DESTINATION}/runtime")


install(TARGETS ${PythonLIBName}
        CONFIGURATIONS Release
        DESTINATION python)
install(FILES ${PYLIB_DESTINATION}/${PythonLIBName}.py
        CONFIGURATIONS Release
        DESTINATION python)

