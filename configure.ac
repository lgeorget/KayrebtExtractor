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
AM_PROG_AR
AC_CHECK_TOOL([CXX],[gcc-4.8],[:])
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
