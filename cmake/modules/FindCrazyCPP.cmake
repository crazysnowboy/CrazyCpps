# - Check for the presence of CrazyCPP
# The following variables control the behaviour of this module:
#
# CrazyCPP_DIR: List of additional directories in which to
#                                search for CrazyCPP

# The following variables are set when CrazyCPPis found:
#  CrazyCPP_FOUND      = Set to true, if all components of CrazyCPP
#                          have been found.
#  CrazyCPP_INCLUDES_DIRS  = Include path for the header files of CrazyCPP
#  CrazyCPP_LIBRARIES  = Link these to use CrazyCPP
#  CrazyCPP_LIBRARIE_DIRS  = LIBS PATHS
## -----------------------------------------------------------------------------

include(cmake/toolsets/FindPackageTools.cmake)


MyFindPackages(
        "CrazyCPP"
         ${CrazyCPP_DIR}

         "include"
         "crazycpp.h"

        "libs"
         "CrazyCppLib Pangolin ZipLib"

        CrazyCPP_FOUND
        CrazyCPP_INCLUDES_DIRS
        CrazyCPP_LIBRARIES
        CrazyCPP_LIBRARIE_DIRS

         )

#message (STATUS "   CrazyCPP_FOUND    = ${CrazyCPP_FOUND}")
#message (STATUS "   CrazyCPP_INCLUDES_DIRS    = ${CrazyCPP_INCLUDES_DIRS}")
#message (STATUS "   CrazyCPP_LIBRARIES    = ${CrazyCPP_LIBRARIES}")
#message (STATUS "   CrazyCPP_LIBRARIE_DIRS    = ${CrazyCPP_LIBRARIE_DIRS}")

mark_as_advanced (
        CrazyCPP_FOUND
        CrazyCPP_LIBRARIES
        CrazyCPP_INCLUDES_DIRS
        CrazyCPP_LIBRARIE_DIRS
)

