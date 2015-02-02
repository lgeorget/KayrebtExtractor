#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Kayrebt], [0.2], [laurent@lgeorget.eu])
AM_INIT_AUTOMAKE([1.11 foreign -Wall -Werror])
AC_CONFIG_SRCDIR([src/end_of_flow_identifier.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR
LT_INIT

# Checks for libraries.
BOOST_REQUIRE([1.52])
BOOST_GRAPH

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_FORK

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
