#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Kayrebt::Actdiags], [2.0.0-r1], [laurent.georget@irisa.fr])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([1.11 foreign -Wall -Werror])
AC_CONFIG_SRCDIR([src/end_of_flow_identifier.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR
AC_CHECK_PROGS([DOT], [dot])
if test -z "$DOT";
then AC_MSG_WARN([You will eventually need GraphViz to use this library])
fi
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi
LT_INIT

# Checks for libraries.
BOOST_REQUIRE([1.52])
BOOST_GRAPH

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_FORK

AM_CONDITIONAL([HAVE_DOXYGEN],[test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([Doxyfile])])
AM_CONDITIONAL([HAVE_DOT],[test -n "$DOT"])
AM_COND_IF([HAVE_DOT], [AC_SUBST(DOT_IS_AVAILABLE,["YES"])], [AC_SUBST(DOT_IS_AVAILABLE,["NO"])])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
