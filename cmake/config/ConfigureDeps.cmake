#opencv
SET(OpenCV_DIR /usr/local/opencv344)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv344)
Gobal_Append(MODULES_LIBRARIES "${OPENCV_LDFLAGS}")
Gobal_Append(MODULES_INCLUDE_DIRS "${OPENCV_INCLUDE_DIRS}")
link_directories(${OpenCV_DIR}/lib)


#SET(OpenCV_DIR /usr/local/opencv3/share/OpenCV)
#find_package(OpenCV REQUIRED)
#if(OpenCV_FOUND)
#    message(STATUS "The Opecv lib is found!")
#    message(${OpenCV_LIBS})
#    message(${OpenCV_INCLUDE_DIRS})
#
#    Gobal_Append(MODULES_LIBRARIES "${OpenCV_LIBS}")
#    Gobal_Append(MODULES_INCLUDE_DIRS "${OpenCV_INCLUDE_DIRS}")
#    link_directories(${OpenCV_DIR}/../../lib)
#
#else()
#    message(STATUS "The Opecv lib not found!")
#endif()

#opengl
#set(OpenGL_INC_DIR /usr/include/GL)
#set(OpenGL_LIB_DIR /usr/lib/x86_64-linux-gnu)
#link_directories("${OpenGL_LIB_DIR}")

find_package(glfw3 3.2 REQUIRED)

Gobal_Append( MODULES_LIBRARIES "glfw")

#boost
find_package(Boost  REQUIRED COMPONENTS system filesystem)
if(Boost_FOUND)
    Gobal_Append( MODULES_INCLUDE_DIRS  ${Boost_INCLUDE_DIRS}/boost )
    Gobal_Append( MODULES_INCLUDE_DIRS  "${Boost_INCLUDE_DIRS}" )
    Gobal_Append( MODULES_LIBRARIES "${Boost_LIBRARIES}")

else()
    message("--------------Boost not FOUND------------")

endif()


set(PYTHON_ROOT /home/collin/.conda/envs/3d_face_tracking)
include_directories(${PYTHON_ROOT}/include
        ${PYTHON_ROOT}/include/python3.5m
        ${PYLIB_DESTINATION}
        ${PYTHON_ROOT}/lib/python3.5/site-packages/numpy/core/include)


#if(WIN32)
#    set(EIGEN_INCLUDE_DIR D:/dev/eigen3/Eigen)
#    list(APPEND INCLUDE_DIR  ${EIGEN_INCLUDE_DIR} )
#
#else()
#    find_package(Eigen REQUIRED OPTIONAL_COMPONENTS filesystem)
#    if(EIGEN_FOUND)
#        set(HAVE_EIGEN 1)
#        list(APPEND INCLUDE_DIR  ${EIGEN_INCLUDE_DIR} )
#
#        Gobal_Append(MODULES_INCLUDE_DIRS "${EIGEN_INCLUDE_DIR}")
#
#        add_definitions(-DEIGEN_NO_DEBUG)
#        message(STATUS "Eigen Found and Enabled")
#
#    else()
#        message(STATUS "Eigen not Found")
#    endif()
#endif()
# SET(CUDA_DIR /usr/local/cudas/cuda-8.0)
# find_package(CUDA  REQUIRED)
# if(CUDA_FOUND)

#     Gobal_Append( MODULES_INCLUDE_DIRS  "${CUDA_INCLUDES_DIRS}")
#     Gobal_Append( MODULES_LIBRARIES "${CUDA_LIBRARIES}")
#     link_directories(${CUDA_LIBRARIE_DIRS})

# else()
#     message("--------------CUDA not FOUND------------")
# endif()


Gobal_Append( MODULES_LIBRARIES "-ldl -lGL -lGLEW -lglut  -lGLU ")

