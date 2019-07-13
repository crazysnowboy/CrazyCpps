# - Check for the presence of CUDA
# The following variables control the behaviour of this module:
#
# CUDA_DIR: List of additional directories in which to
#                                search for CUDA

# The following variables are set when CUDAis found:
#  CUDA_FOUND      = Set to true, if all components of CUDA
#                          have been found.
#  CUDA_INCLUDES_DIRS  = Include path for the header files of CUDA
#  CUDA_LIBRARIES  = Link these to use CUDA
#  CUDA_LIBRARIE_DIRS  = LIBS PATHS
## -----------------------------------------------------------------------------

include(cmake/toolsets/FindPackageTools.cmake)


MyFindPackages(
        "CUDA"
         ${CUDA_DIR}

         "include"
         "cuda.h"

        "lib64"
         "cudart"

        CUDA_FOUND
        CUDA_INCLUDES_DIRS
        CUDA_LIBRARIES
        CUDA_LIBRARIE_DIRS

         )

message (STATUS "   CUDA_FOUND    = ${CUDA_FOUND}")
message (STATUS "   CUDA_INCLUDES_DIRS    = ${CUDA_INCLUDES_DIRS}")
message (STATUS "   CUDA_LIBRARIES    = ${CUDA_LIBRARIES}")
message (STATUS "   CUDA_LIBRARIE_DIRS    = ${CUDA_LIBRARIE_DIRS}")

mark_as_advanced (
        CUDA_FOUND
        CUDA_LIBRARIES
        CUDA_INCLUDES_DIRS
        CUDA_LIBRARIE_DIRS
)




