#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT(cppconact,0.0.1,me@fake.email.addy.com)
AC_LANG([C++])
AM_INIT_AUTOMAKE(gnu dist-bzip2)
AC_PROG_LIBTOOL
dnl LT_PREREQ([2.2])
dnl LT_INIT([dlopen])
AC_CONFIG_SRCDIR([cppconact_common.am])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AM_PROG_CC_C_O

# Checks for typedefs, structures, and compiler characteristics.
dnl AC_HEADER_STDBOOL
dnl AC_C_INLINE
dnl AC_TYPE_SIZE_T

# Checks for library functions.
dnl AC_FUNC_ERROR_AT_LINE

# system and posix headers
dnl m4_foreach( [myvar],
dnl             [sys/file.h,getopt.h],
dnl             [AC_CHECK_HEADERS( myvar,,
dnl                                AC_MSG_ERROR( missing myvar ) )] )dnl

dnl AX_CXX_HEADER_STDCXX_0X

AX_CXX_HAVE_STD

AX_CXX_HAVE_STL

AX_CXX_COMPILE_STDCXX_0X

AX_BOOST_BASE([1.47],,AC_MSG_ERROR(you need Boost >= v.1.47))


dnl AI_CHECK_ORB([],[])
dnl if test "x$ORB" = "xno"
dnl then
dnl     AC_MSG_ERROR([an ORB is required])
dnl fi


AC_CONFIG_FILES([ Makefile ])
                  dnl cutil/Makefile
                  dnl cereal/Makefile
                  dnl bobtalk/Makefile ])
                  dnl fcdig/Makefile
                  dnl fcdig/bobtalk/Makefile
                  dnl fcdig/simulator/Makefile ])
                  dnl newport/Makefile ])
                  dnl hall/Makefile ])

dnl AC_CONFIG_SUBDIRS([example1 example5])

AC_OUTPUT

