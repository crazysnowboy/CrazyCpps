#ifndef PANGOLIN_CONFIG_H
#define PANGOLIN_CONFIG_H

/*
 * Configuration Header for Pangolin
 */

/// Version
#define PANGOLIN_VERSION_MAJOR 0
#define PANGOLIN_VERSION_MINOR 5
#define PANGOLIN_VERSION_STRING "0.5"

/// Pangolin options
#define BUILD_PANGOLIN_GUI
#define BUILD_PANGOLIN_VARS



#define HAVE_EIGEN
/* #undef HAVE_TOON */



#define HAVE_GLEW


/// Platform
#define _UNIX_

#define _LINUX_


/// Compiler
#define _GCC_


#if (__cplusplus > 199711L) || (_MSC_VER >= 1800)
#define CALLEE_HAS_VARIADIC_TEMPLATES
#endif

#endif //PANGOLIN_CONFIG_H
