#***************************************************************************
#                                  _   _ ____  _
#  Project                     ___| | | |  _ \| |
#                             / __| | | | |_) | |
#                            | (__| |_| |  _ <| |___
#                             \___|\___/|_| \_\_____|
#
# Copyright (C) 1998 - 2022, Daniel Stenberg, <daniel@haxx.se>, et al.
#
# This software is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at https://curl.se/docs/copyright.html.
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the COPYING file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
# SPDX-License-Identifier: curl
#
#***************************************************************************

AC_DEFUN([CURL_WITH_NSS], [
if test "x$OPT_NSS" != xno; then
  ssl_msg=

  if test X"$OPT_NSS" != Xno; then

    addld=""
    addlib=""
    addcflags=""
    nssprefix=""
    version=""

    if test "x$OPT_NSS" = "xyes"; then

      CURL_CHECK_PKGCONFIG(nss)

      if test "$PKGCONFIG" != "no" ; then
        addlib=`$PKGCONFIG --libs nss`
        addcflags=`$PKGCONFIG --cflags nss`
        version=`$PKGCONFIG --modversion nss`
        nssprefix=`$PKGCONFIG --variable=prefix nss`
      else
        dnl Without pkg-config, we check for nss-config

        check=`nss-config --version 2>/dev/null`
        if test -n "$check"; then
          addlib=`nss-config --libs`
          addcflags=`nss-config --cflags`
          version=`nss-config --version`
          nssprefix=`nss-config --prefix`
        else
          addlib="-lnss3"
          addcflags=""
          version="unknown"
        fi
      fi
    else
      NSS_PCDIR="$OPT_NSS/lib/pkgconfig"
      if test -f "$NSS_PCDIR/nss.pc"; then
        CURL_CHECK_PKGCONFIG(nss, [$NSS_PCDIR])
        if test "$PKGCONFIG" != "no" ; then
          addld=`CURL_EXPORT_PCDIR([$NSS_PCDIR]) $PKGCONFIG --libs-only-L nss`
          addlib=`CURL_EXPORT_PCDIR([$NSS_PCDIR]) $PKGCONFIG --libs-only-l nss`
          addcflags=`CURL_EXPORT_PCDIR([$NSS_PCDIR]) $PKGCONFIG --cflags nss`
          version=`CURL_EXPORT_PCDIR([$NSS_PCDIR]) $PKGCONFIG --modversion nss`
          nssprefix=`CURL_EXPORT_PCDIR([$NSS_PCDIR]) $PKGCONFIG --variable=prefix nss`
        fi
      fi
    fi

    if test -z "$addlib"; then
      # Without pkg-config, we'll kludge in some defaults
      AC_MSG_WARN([Using hard-wired libraries and compilation flags for NSS.])
      addld="-L$OPT_NSS/lib"

      # curl-impersonate: Link NSS statically.
      # NSS is poorly documented in this regard and a lot of trial and error
      # was made to come up with the correct list of linking flags. The
      # libraries have circular dependencies which makes their order extremely
      # difficult to find out.

      # Some references:
      # https://github.com/mozilla/application-services/blob/b2690fd2e4cc3e8e10b6868ab0de8b79c89d3a93/components/support/rc_crypto/nss/nss_build_common/src/lib.rs#L94
      # and
      # https://hg.mozilla.org/mozilla-central/file/tip/security/nss/lib/freebl/freebl.gyp

      # On Linux we can use special linker flags to force static linking
      # (-l:libplc4.a etc.), otherwise the linker will prefer to use
      # libplc4.so. On other systems the dynamic libraries would have to be
      # removed manually from the NSS directory before building curl.
      case $host_os in
        linux*)
          addlib="-lssl -lnss_static -lpk11wrap_static -lcertdb -lcerthi -lnsspki -lnssdev -lsoftokn_static -lfreebl_static -lnssutil -lnssb -lcryptohi -l:libplc4.a -l:libplds4.a -l:libnspr4.a -lsqlite"
          ;;
        darwin*)
          addlib="-lssl -lnss_static -lpk11wrap_static -lcertdb -lcerthi -lnsspki -lnssdev -lsoftokn_static -lfreebl_static -lnssutil -lnssb -lcryptohi -lplc4 -lplds4 -lnspr4"
          ;;
        *)
          addlib="-lssl -lnss_static -lpk11wrap_static -lcertdb -lcerthi -lnsspki -lnssdev -lsoftokn_static -lfreebl_static -lnssutil -lnssb -lcryptohi -lplc4 -lplds4 -lnspr4 -lsqlite"
          ;;
      esac

      case $host_cpu in
        arm)
          addlib="$addlib -larmv8_c_lib"
          ;;
        aarch64)
          addlib="$addlib -larmv8_c_lib -lgcm-aes-aarch64_c_lib"
          ;;
        x86)
          addlib="$addlib -lgcm-aes-x86_c_lib"
          ;;
        x86_64)
          addlib="$addlib -lgcm-aes-x86_c_lib -lhw-acc-crypto-avx -lhw-acc-crypto-avx2 -lsha-x86_c_lib"
          case $host_os in
            linux*)
              addlib="$addlib -lintel-gcm-wrap_c_lib -lintel-gcm-s_lib"
              ;;
          esac
          ;;
      esac

      # curl-impersonate:
      # On Linux these linker flags are necessary to resolve
      # the symbol mess and circular dependencies of NSS .a libraries
      # to make the AC_CHECK_LIB test below pass.
      case $host_os in
        linux*)
          addlib="-Wl,--start-group $addlib -Wl,--end-group"
          ;;
      esac

      # External dependencies for nss
      case $host_os in
        linux*)
          addlib="$addlib -pthread -ldl"
          ;;
        darwin*)
          addlib="$addlib -lsqlite3"
          ;;
      esac

      # Attempt to locate libnssckbi.
      # This library file contains the trusted certificates and nss loads it
      # at runtime using dlopen. If it's not in a path findable by dlopen
      # we have to add that path explicitly using -rpath so it may find it.
      # On Ubuntu and Mac M1 it is in a non-standard location.
      AC_ARG_WITH(libnssckbi,
        [AS_HELP_STRING([--with-libnssckbi=DIRECTORY],
                       [Path where libnssckbi can be found when using NSS])],
        [AS_IF(
          [test x"$withval" = xyes],
          [nssckbi_path="check"],
          [nssckbi_path="$withval"])],
        [nssckbi_path="check"])

      AS_IF(
        [test "x$nssckbi_path" = xno],
        [],
        [test "x$nssckbi_path" != xcheck],
        [addld="$addld -Wl,-rpath,$nssckbi_path"],
        [
          AC_MSG_CHECKING([if libnssckbi is in a non-standard location])
          case $host_os in
            linux*)
              search_paths="/usr/lib/$host /usr/lib/$host/nss"
              search_paths="$search_paths /usr/lib/$host_cpu-$host_os"
              search_paths="$search_paths /usr/lib/$host_cpu-$host_os/nss"
              search_ext="so"
              ;;
            darwin*)
              search_paths="/opt/homebrew/lib"
              search_ext="dylib"
              ;;
          esac

          found="no"
          for path in $search_paths; do
            if test -f "$path/libnssckbi.$search_ext"; then
              AC_MSG_RESULT([$path])
              addld="$addld -Wl,-rpath,$path"
              found="yes"
              break
            fi
          done

          if test "$found" = "no"; then
            AC_MSG_RESULT([no])
          fi
        ])

      addcflags="-I$OPT_NSS/include"
      version="unknown"
      nssprefix=$OPT_NSS
    fi

    CLEANLDFLAGS="$LDFLAGS"
    CLEANLIBS="$LIBS"
    CLEANCPPFLAGS="$CPPFLAGS"

    LDFLAGS="$addld $LDFLAGS"
    LIBS="$addlib $LIBS"
    if test "$addcflags" != "-I/usr/include"; then
       CPPFLAGS="$CPPFLAGS $addcflags"
    fi

    dnl The function SSL_VersionRangeSet() is needed to enable TLS > 1.0
    AC_CHECK_LIB(nss_static, SSL_VersionRangeSet,
     [
     AC_DEFINE(USE_NSS, 1, [if NSS is enabled])
     AC_SUBST(USE_NSS, [1])
     USE_NSS="yes"
     NSS_ENABLED=1
     ssl_msg="NSS"
     test nss != "$DEFAULT_SSL_BACKEND" || VALID_DEFAULT_SSL_BACKEND=yes
     ],
     [
       AC_MSG_ERROR([Failed linking NSS statically])
     ])

    if test "x$USE_NSS" = "xyes"; then
      AC_MSG_NOTICE([detected NSS version $version])

      dnl PK11_CreateManagedGenericObject() was introduced in NSS 3.34 because
      dnl PK11_DestroyGenericObject() does not release resources allocated by
      dnl PK11_CreateGenericObject() early enough.
      AC_CHECK_FUNC(PK11_CreateManagedGenericObject,
        [
          AC_DEFINE(HAVE_PK11_CREATEMANAGEDGENERICOBJECT, 1,
                    [if you have the PK11_CreateManagedGenericObject function])
        ])

      dnl needed when linking the curl tool without USE_EXPLICIT_LIB_DEPS
      NSS_LIBS=$addlib
      AC_SUBST([NSS_LIBS])

      dnl when shared libs were found in a path that the run-time
      dnl linker doesn't search through, we need to add it to
      dnl CURL_LIBRARY_PATH to prevent further configure tests to fail
      dnl due to this
      if test "x$cross_compiling" != "xyes"; then
        CURL_LIBRARY_PATH="$CURL_LIBRARY_PATH:$nssprefix/lib$libsuff"
        export CURL_LIBRARY_PATH
        AC_MSG_NOTICE([Added $nssprefix/lib$libsuff to CURL_LIBRARY_PATH])
      fi

    fi dnl NSS found

  fi dnl NSS not disabled

  test -z "$ssl_msg" || ssl_backends="${ssl_backends:+$ssl_backends, }$ssl_msg"
fi

])
