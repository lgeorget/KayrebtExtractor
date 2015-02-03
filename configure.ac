#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Kayrebt-dumper], [0.0], [laurent.georget@inria.fr])
AM_INIT_AUTOMAKE([1.11 foreign -Wall -Werror])
AC_CONFIG_SRCDIR([src/integer_cst.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SUBDIRS([activity_diagram])
AC_LANG([C++])

# Checks for programs.
AC_PROG_CC
# We need GNU C++ compiler because we are building a plugin for gcc
AC_PROG_CXX([g++])
AC_PROG_AWK
AX_COMPILER_VENDOR
AM_CONDITIONAL([GXX_AVAIL], [test x${ax_cv_cxx_compiler_vendor} = xgnu])
AM_COND_IF([GXX_AVAIL], [:],
	   [AC_MSG_ERROR([g++ is required to build gcc plugins])]
	  )
AX_COMPILER_VERSION
gcc_ver=`echo ${ax_cv_cxx_compiler_version} | awk -F'[[^[0-9]]*]' '{print (1000 * $1 + $2)}'`
AM_CONDITIONAL([GXX_4_8_AVAIL], [test [${gcc_ver}] -eq 4008])
AM_COND_IF([GXX_4_8_AVAIL], [:],
	   [AC_MSG_ERROR([g++ version 4.8 exactly is required])]
	  )
AM_PROG_AR
LT_INIT

# Checks for libraries.

# Checks for header files.
AX_GCC_PLUGIN

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile activity_diagram/Makefile activity_diagram/src/Makefile])
AC_OUTPUT
