dnl ***************************************************************************
dnl *** configure.in for GDE2-APPLETS                                      ***
dnl ***************************************************************************
AC_INIT(gde2-applets, 1.1.0)
AC_PREREQ(2.59)

AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([1.9 tar-ustar dist-xz no-dist-gzip check-news])
AC_CONFIG_MACRO_DIR(m4)

dnl ***************************************************************************
dnl *** Minimum library versions for GDE2-APPLETS                          ***
dnl ***************************************************************************
GLIB_REQUIRED=2.36.0
GIO_REQUIRED=2.15.3
LIBPANEL4_REQUIRED=1.1.0
LIBGTOP_REQUIRED=2.11.92
LIBGDE2_DESKTOP_REQUIRED=1.1.0
LIBNOTIFY_REQUIRED=0.7.0
UPOWER_REQUIRED=0.9.4
DBUS_REQUIRED=1.1.2
DBUS_GLIB_REQUIRED=0.74
LIBXML_REQUIRED=2.5.0
POLKIT_REQUIRED=0.92
dnl ***************************************************************************

AM_MAINTAINER_MODE

IT_PROG_INTLTOOL([0.50.1])
PKG_PROG_PKG_CONFIG([0.19])

AC_PROG_CC
AC_STDC_HEADERS
AM_PROG_LIBTOOL
AC_PATH_XTRA
AM_PATH_PYTHON(2.4)
AM_CHECK_PYTHON_HEADERS(HAVE_PYHDRS="yes", HAVE_PYHDRS="no")

X_LIBS="$X_LIBS $X_PRE_LIBS -lX11 $X_EXTRA_LIBS"
AC_SUBST(X_LIBS)

GDE2_COMPILE_WARNINGS

dnl Check for non-portable headers
AC_CHECK_HEADERS([pty.h values.h])

dnl ***************************************************************************
dnl *** --enable-more-warnings turns on more compiler warnings              ***
dnl ***************************************************************************
AC_ARG_ENABLE(more-warnings,
[  --enable-more-warnings  Maximum compiler warnings],
set_more_warnings="$enableval",[
    set_more_warnings=no
])
AC_MSG_CHECKING(for more warnings, including -Werror)
if test "$GCC" = "yes" -a "$set_more_warnings" != "no"; then
    AC_MSG_RESULT(yes)
    CFLAGS="\
    -Wall \
    -Wchar-subscripts -Wmissing-declarations -Wmissing-prototypes \
    -Wnested-externs -Wpointer-arith \
    -Wcast-align -Wsign-compare \
    -std=gnu89 \
    $CFLAGS"

    for option in -Wno-strict-aliasing -Wno-sign-compare; do
        SAVE_CFLAGS="$CFLAGS"
        CFLAGS="$CFLAGS $option"
        AC_MSG_CHECKING([whether gcc understands $option])
        AC_TRY_COMPILE([], [],
            has_option=yes,
            has_option=no,)
        if test $has_option = no; then
            CFLAGS="$SAVE_CFLAGS"
        fi
        AC_MSG_RESULT($has_option)
        unset has_option
        unset SAVE_CFLAGS
    done
    unset option
else
    AC_MSG_RESULT(no)
fi
dnl ***************************************************************************

dnl ***************************************************************************
dnl *** Check for GTK+ version to use                                       ***
dnl ***************************************************************************

GTK_API_VERSION=2.0
GTK_REQUIRED=2.24.0
LIBWNCK_API_VERSION=1.0
LIBWNCK_REQUIRED=2.30.0
GUCHARMAP_API_VERSION=2
GUCHARMAP_REQUIRED=2.32.1

AC_SUBST(GTK_API_VERSION)

dnl ***************************************************************************


dnl ***************************************************************************
dnl *** Use pkg-config to check for dependancies                            ***
dnl ***************************************************************************

dnl -- check for gio (required) ------------------------------------------
PKG_CHECK_MODULES(GIO, gio-2.0 >= $GIO_REQUIRED gio-unix-2.0)
AC_SUBST(GIO_CFLAGS)
AC_SUBST(GIO_LIBS)

dnl -- Check for GTK+ 2.0 (required) ------------------------------------------
PKG_CHECK_MODULES(GTK, gtk+-$GTK_API_VERSION >= $GTK_REQUIRED)
AC_SUBST(GTK_FLAGS)
AC_SUBST(GTK_LIBS)

dnl -- check for libgde2panelapplet4 (required) ------------------------------------
PKG_CHECK_MODULES(GDE2_APPLETS4, libgde2panelapplet-4.0 >= $LIBPANEL4_REQUIRED)
AC_SUBST(GDE2_APPLETS4_CFLAGS)
AC_SUBST(GDE2_APPLETS4_LIBS)

dnl -- check for gde2-desktop (required) -------------------------------------
PKG_CHECK_MODULES(GDE2DESKTOP, gde2-desktop-2.0 >= $LIBGDE2_DESKTOP_REQUIRED)
AC_SUBST(GDE2DESKTOP_CFLAGS)
AC_SUBST(GDE2DESKTOP_LIBS)

dnl -- check for libgtop (optional) -------------------------------------------
build_gtop_applets=false
PKG_CHECK_MODULES(GTOP_APPLETS,
                 [libgtop-2.0 >= $LIBGTOP_REQUIRED],
                 build_gtop_applets=true,
		 AC_MSG_WARN([libgtop not found. Not building gtop applets.]))
AC_SUBST(GTOP_APPLETS_CFLAGS)
AC_SUBST(GTOP_APPLETS_LIBS)
AM_CONDITIONAL(BUILD_GTOP_APPLETS, $build_gtop_applets)

dnl -- check for libwnck (required) -------------------------------------------
PKG_CHECK_MODULES(LIBWNCK, libwnck-$LIBWNCK_API_VERSION >= $LIBWNCK_REQUIRED,,
	AC_MSG_ERROR([libwnck is required to build gde2-applets.], 1))

AC_SUBST(LIBWNCK_CFLAGS)
AC_SUBST(LIBWNCK_LIBS)

dnl -- check for libnotify (optional) -----------------------------------------
LIBNOTIFY_CFLAGS=
LIBNOTIFY_LIBS=
PKG_CHECK_MODULES(LIBNOTIFY, libnotify >= $LIBNOTIFY_REQUIRED,
		  HAVE_LIBNOTIFY="yes", HAVE_LIBNOTIFY="no")

if test "x$HAVE_LIBNOTIFY" = "xyes"; then
	AC_DEFINE(HAVE_LIBNOTIFY, 1, [libnotify available])
fi

AC_SUBST(LIBNOTIFY_CFLAGS)
AC_SUBST(LIBNOTIFY_LIBS)

dnl -- check for glib/gobject (required) --------------------------------------
PKG_CHECK_MODULES(CPUFREQ_SELECTOR, glib-2.0 >= $GLIB_REQUIRED gobject-2.0 >= $GLIB_REQUIRED)
AC_SUBST(CPUFREQ_SELECTOR_CFLAGS)
AC_SUBST(CPUFREQ_SELECTOR_LIBS)

dnl -- check for dbus (required for cpufreq-selector)
PKG_CHECK_MODULES(DBUS, dbus-1 >= $DBUS_REQUIRED dbus-glib-1 >= $DBUS_GLIB_REQUIRED, HAVE_DBUS=yes, HAVE_DBUS=no)

AC_SUBST(DBUS_CFLAGS)
AC_SUBST(DBUS_LIBS)

dnl -- check for PolicyKit and PolicyKit-gde2 (optional) -----------------------------------------
POLKIT_CFLAGS=
POLKIT_LIBS=
AC_ARG_ENABLE([polkit],
    AC_HELP_STRING([--enable-polkit], [Enable PolicyKit support @<:@default auto@:>@]),
    enable_polkit=$enableval,
    enable_polkit=auto)
if test "x$enable_polkit" != "xno"; then
    PKG_CHECK_MODULES(POLKIT, polkit-gobject-1 >= $POLKIT_REQUIRED dbus-glib-1 >= $DBUS_GLIB_REQUIRED, HAVE_POLKIT=yes, HAVE_POLKIT=no)
    if test "x$enable_polkit" = "xyes" -a "x$HAVE_POLKIT" = "xno"; then
        AC_MSG_ERROR([PolicyKit support explicitly requested but dependencies not found])
    fi
fi
dnl - This is only so the printout at the end of configure is correct -
if test "x$enable_polkit" = "xno"; then
   HAVE_POLKIT=no
fi
if test "x$HAVE_POLKIT" = "xyes"; then
    AC_DEFINE(HAVE_POLKIT, [1], [PolicyKit available])
fi
AM_CONDITIONAL(HAVE_POLKIT, test "x$HAVE_POLKIT" = "xyes")
AC_SUBST(POLKIT_CFLAGS)
AC_SUBST(POLKIT_LIBS)

dnl -- check for libupower-glib (optional) ------------------------------------
UPOWER_CFLAGS=
UPOWER_LIBS=
AC_ARG_WITH(upower, [  --without-upower        build without upower support])

if test "x$with_upower" != xno; then
   PKG_CHECK_MODULES(UPOWER, upower-glib >= $UPOWER_REQUIRED,
         HAVE_UPOWER="yes",
         HAVE_UPOWER="no")
         
   if test "x$HAVE_UPOWER" = "xyes"; then
       AC_DEFINE(HAVE_UPOWER, 1, [UPOWER available])
   fi
else
   HAVE_UPOWER="no"
   AC_MSG_WARN(["upower support disabled"])
fi

AC_SUBST(UPOWER_CFLAGS)
AC_SUBST(UPOWER_LIBS)

dnl -- check for gucharmap (optional) -----------------------------------------

PKG_CHECK_EXISTS([gucharmap-$GUCHARMAP_API_VERSION >= $GUCHARMAP_REQUIRED],
                 [have_gucharmap=yes], [have_gucharmap=no])
if test "$have_gucharmap" = "yes"; then
	PKG_CHECK_MODULES([GUCHARMAP], [gucharmap-$GUCHARMAP_API_VERSION >= $GUCHARMAP_REQUIRED])
	AC_DEFINE([HAVE_GUCHARMAP], [1] ,[Gucharmap Available])
else
  AC_MSG_WARN([*** 'charpick' applet will be built without gucharmap support ***])
fi
AC_SUBST(GUCHARMAP_CFLAGS)
AC_SUBST(GUCHARMAP_LIBS)

dnl -- check for Python modules (optional) ------------------------------
PKG_CHECK_MODULES(PYGOBJECT, pygobject-3.0, HAVE_PYGOBJECT="yes", HAVE_PYGOBJECT="no")

dnl -- check for libxml2 (required) ------------------------------------------
PKG_CHECK_MODULES(XML2, libxml-2.0 >= $LIBXML_REQUIRED)
AC_SUBST(XML2_CFLAGS)
AC_SUBST(XML2_LIBS)

 dnl -- check for libgde2weather (required for gde2weather applet) ------------------
build_libgde2weather_applets=false
PKG_CHECK_MODULES(LIBGDE2WEATHER, gde2weather >= 1.6.1,
	          build_libgde2weather_applets=true,
		  AC_MSG_WARN([libgde2weather not found. Not building the weather applet.]))
AC_SUBST(LIBGDE2WEATHER_CFLAGS)
AC_SUBST(LIBGDE2WEATHER_LIBS)
AM_CONDITIONAL(BUILD_LIBGDE2WEATHER_APPLETS, $build_libgde2weather_applets)

dnl ***************************************************************************
dnl *** GSettings                                                               ***
dnl ***************************************************************************
GLIB_GSETTINGS

dnl ***************************************************************************
dnl *** Set up gettext                                                      ***
dnl ***************************************************************************

GETTEXT_PACKAGE=gde2-applets
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Gettext Package])
AC_DEFINE_DIR(GDE2LOCALEDIR, "${datadir}/locale", [locale directory])
AM_GLIB_GNU_GETTEXT

# this is the directory where the *.{mo,gmo} files are installed
gde2localedir='${prefix}/${DATADIRNAME}/locale'
AC_SUBST(gde2localedir)

dnl ***************************************************************************
dnl *** yelp-tools                                                          ***
dnl ***************************************************************************
YELP_HELP_INIT

dnl ***************************************************************************
dnl *** battstat specific checks                                            ***
dnl ***************************************************************************

dnl --disable-battstat=(yes|no)
AC_ARG_ENABLE(battstat,
	      [  --disable-battstat=[@<:@no/yes@:>@]
                          dont build battery monitor applet [@<:@default: no@:>@]],,
	      disable_battstat=no)

HAVE_LIBAPM=no
NEED_LIBAPM=no
ACPIINC=
build_battstat_applet=no

if test x$disable_battstat = xno; then
   build_battstat_applet=yes
   AC_CHECK_HEADERS([err.h sys/sysctl.h])
   case "${host}" in
       powerpc-*-linux*)
           NEED_LIBAPM=yes
           AC_CHECK_LIB(apm,apm_read,[HAVE_LIBAPM=yes],[HAVE_LIBAPM=no])
	   ;;
       # list of supported OS cores that use libapm
       *-*-linux*)
	   NEED_LIBAPM=yes
	   AC_CHECK_LIB(apm,apm_read,[HAVE_LIBAPM=yes],[HAVE_LIBAPM=no])
	   ;;
       # list of supported OS cores that do not use libapm
       i386-*-freebsd*|*-*-netbsd*|*-*-openbsd*|*-*kfreebsd*-gnu)
          if test -n "${OS_SYS}"; then
	       ACPIINC="-I${OS_SYS}"
	   else
	       ACPIINC="-I/usr/src/sys"
	   fi

	   savecppflags=$CPPFLAGS
	   CPPFLAGS="$CPPFLAGS $ACPIINC"
	   AC_CHECK_HEADER(dev/acpica/acpiio.h, have_acpiio=true, have_acpiio=false)
	   if test $have_acpiio = true; then
	     AC_DEFINE(HAVE_ACPIIO, 1, [Define if acpiio.h exists on the system])
	   fi

	   ;;
       *)
	   echo "warning: ${host} is not supported by battstat_applet, not building" >&2
	   build_battstat_applet=no
	   ;;
    esac
fi

AC_SUBST(HAVE_LIBAPM)
AC_SUBST(NEED_LIBAPM)
AC_SUBST(ACPIINC)
AM_CONDITIONAL(HAVE_LIBAPM, test "x$HAVE_LIBAPM" = "xyes")
AM_CONDITIONAL(NEED_LIBAPM, test "x$NEED_LIBAPM" = "xyes")
AM_CONDITIONAL(BUILD_BATTSTAT_APPLET, test x$build_battstat_applet = xyes)

dnl ***************************************************************************
dnl *** Stickynotes specific checks                                         ***
dnl ***************************************************************************
AC_ARG_ENABLE([stickynotes],
    AC_HELP_STRING([--enable-stickynotes], [Enable stickynotes applet.]),
    enable_stickynotes=$enableval,
    enable_stickynotes=yes)
if test "x$enable_stickynotes" = "xyes"; then
    PKG_CHECK_MODULES(STICKYNOTES, gtksourceview-$GTK_API_VERSION,
                      have_gtksourceview=yes, have_gtksourceview=no)

    if test "x$enable_stickynotes" = "xyes" -a "x$have_gtksourceview" = "xno"; then
        AC_MSG_ERROR([Stickynotes explicitely requested but dependency not found])
    fi
fi
AM_CONDITIONAL(BUILD_STICKYNOTES_APPLET, test "x$have_gtksourceview" = "xyes")

dnl ***************************************************************************
dnl *** keyboard accessibility status applet check                          ***
dnl ***************************************************************************

savecppflags=$CPPFLAGS
CPPFLAGS="$CPPFLAGS $X_CFLAGS"
AC_CHECK_HEADER(X11/extensions/XKB.h, HAVE_XKB=true, HAVE_XKB=false)
AC_SUBST(HAVE_XKB)

AM_CONDITIONAL(APPLET_ACCESSX, $HAVE_XKB)
if test "x$APPLET_ACCESSX" = "xtrue"; then
  AC_MSG_WARN([*** keyboard accessibility status applet will not be built ***])
fi
CPPFLAGS=$savecppflags

dnl ***************************************************************************
dnl *** cpufreq applet check                                                ***
dnl ***************************************************************************

dnl --disable-cpufreq=(yes|no)
AC_ARG_ENABLE(cpufreq,
	      [  --disable-cpufreq[@<:@=no/yes@:>@]
                          dont build cpu frequency scaling monitor applet
			  [@<:@default: no@:>@]],,
	      disable_cpufreq=no)

dnl --enable-frequency-selector=(yes/no)
AC_ARG_ENABLE(frequency-selector,
	      [  --enable-frequency-selector[@<:@=yes/no@:>@]
	                  build frequency selector [@<:@default: yes@:>@]], enable_selector=$enableval,
	      enable_selector=yes)

dnl --enable-suid=(yes/no)
AC_ARG_ENABLE(suid,
	      [  --enable-suid[@<:@=yes/no@:>@]  suid root the frequency selector executable
                          [@<:@default: yes@:>@]],,
	      enable_suid=yes)

if test "x$HAVE_POLKIT" = "xyes"; then
   enable_suid=no
fi

AC_ARG_WITH([cpufreq-lib],
	AS_HELP_STRING([--with-cpufreq-lib=lib], [library to use for cpufreq applet @<:@default=cpufreq@:>@]),
	[with_cpufreq_lib=$withval], [with_cpufreq_lib="cpupower"])

AC_CHECK_HEADER(cpufreq.h, have_libcpufreq=yes, have_libcpufreq=no)
LIBCPUFREQ_LIBS=
if test "x$have_libcpufreq" = "xyes"; then
   AC_DEFINE([HAVE_LIBCPUFREQ], [1], [Have libcpufreq.])
   LIBCPUFREQ_LIBS="-l$with_cpufreq_lib"
fi
AM_CONDITIONAL(HAVE_LIBCPUFREQ, test x$have_libcpufreq = xyes)
AC_SUBST(LIBCPUFREQ_LIBS)

build_cpufreq_applet=no

if test x$disable_cpufreq = xno; then
   case "${host}" in
      *linux*)
         build_cpufreq_applet=yes
	 ;;
      *)
         AC_MSG_WARN([${host} is not supported by cpufreq applet, not building])
	 build_cpufreq_applet=no
	 ;;
   esac
fi

AM_CONDITIONAL(BUILD_CPUFREQ_APPLET, test x$build_cpufreq_applet = xyes)
AM_CONDITIONAL(BUILD_CPUFREQ_SELECTOR, test x$enable_selector = xyes)
AM_CONDITIONAL(CPUFREQ_SELECTOR_SUID, test x$enable_suid = xyes)

dnl ***************************************************************************
dnl *** timerapplet specific checks                                       ***
dnl ***************************************************************************

AM_CONDITIONAL(BUILD_TIMERAPPLET, test "x$HAVE_LIBNOTIFY" = "xyes")

dnl ***************************************************************************
dnl *** invest-applet specific checks                                       ***
dnl ***************************************************************************

AM_CONDITIONAL(BUILD_INVEST_APPLET, test "x$HAVE_PYGOBJECT" = "xyes")

dnl ***************************************************************************
dnl *** iwlib support for netspeed applet                                   ***
dnl ***************************************************************************
have_iwevgenie=no
AC_MSG_CHECKING([for libiw >= 28pre9])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([
                #include <iwlib.h>
                #ifndef IWEVGENIE
                #error "not found"
                #endif])],
               [have_iwevgenie=yes],
    AC_MSG_WARN([iwlib.h not found. It's provided by libiw or wireless-tools (depends on the distro)])
)
AC_MSG_RESULT([$have_iwevgenie])
if test "$have_iwevgenie" = yes; then
    AC_DEFINE(HAVE_IW, 1, [Defined if you have libiw/wireless-tools (depends on the distro)])
    IWLIB=-liw
    AC_SUBST(IWLIB)
fi

dnl ***************************************************************************
dnl *** Check if IPv6 is available                                          ***
dnl ***************************************************************************
AC_MSG_CHECKING([whether to enable ipv6])
AC_ARG_ENABLE(ipv6, [  --enable-ipv6 enable IPv6 extensions], ,enable_ipv6=yes)
if test $enable_ipv6 = yes; then

  dnl Code for checking presence of AF_INET6 on the system.
  AC_TRY_COMPILE([
    #include <sys/types.h>
    #include <sys/socket.h>], [
    socket(AF_INET6, SOCK_STREAM, 0)
    ],
    have_ipv6=yes,
    have_ipv6=no
  )
  AC_MSG_RESULT($have_ipv6)
  if test $have_ipv6 = yes; then
      AC_DEFINE(ENABLE_IPV6, 1, [Define if system is IPv6 enabled])
  fi
fi

dnl ***************************************************************************
dnl *** Check for getaddrinfo                                               ***
dnl ***************************************************************************
have_getaddrinfo=no
AC_CHECK_FUNC(getaddrinfo, have_getaddrinfo=yes)
if test $have_getaddrinfo != yes; then
  # getaddrinfo is not in the default libraries.  See if it's in some other.
  for lib in bsd socket inet; do
    AC_CHECK_LIB($lib, getaddrinfo, [LIBS="$LIBS -l$lib";have_getaddrinfo=yes; break])
  done
fi
if test $have_getaddrinfo = yes; then
  AC_DEFINE(HAVE_GETADDRINFO, 1, [Define if getaddrinfo() exists on the system])
fi

dnl ***************************************************************************
dnl *** Check for presence of tm.tm_gmtoff on the system                    ***
dnl ***************************************************************************
AC_CHECK_MEMBER([struct tm.tm_gmtoff],[struct_tm_tm_gmtoff=true],[struct_tm_tm_gmtoff=false],[#include <time.h>])
case $struct_tm_tm_gmtoff in
        true)
                AC_DEFINE_UNQUOTED(HAVE_TM_TM_GMOFF, 1, Have the tm.tm_gmtoff member.)
                ;;
        *)
                AC_CHECK_DECL(timezone,AC_DEFINE(HAVE_TIMEZONE,1,Have timezone),,
[
#include <time.h>
])
                ;;
esac

dnl ***************************************************************************
dnl *** _NL_MEASUREMENT_MEASUREMENT is an enum and not a define             ***
dnl ***************************************************************************
AC_MSG_CHECKING([for _NL_MEASUREMENT_MEASUREMENT])
AC_TRY_LINK([#include <langinfo.h>], [
char c;
c = *((unsigned char *)  nl_langinfo(_NL_MEASUREMENT_MEASUREMENT));
], gtk_ok=yes, gtk_ok=no)
AC_MSG_RESULT($gtk_ok)
if test "$gtk_ok" = "yes"; then
  AC_DEFINE([HAVE__NL_MEASUREMENT_MEASUREMENT], [1],
            [Define if _NL_MEASUREMENT_MEASUREMENT is available])
fi

dnl ***************************************************************************
dnl *** Honour aclocal flags                                                ***
dnl ***************************************************************************
ACLOCAL_AMFLAGS="\${ACLOCAL_FLAGS}"
AC_SUBST(ACLOCAL_AMFLAGS)

dnl ***************************************************************************
dnl *** Set install directories                                             ***
dnl ***************************************************************************
iconsdir="${datadir}/icons"
AC_SUBST(iconsdir)
pixmapsdir="${datadir}/pixmaps"
AC_SUBST(pixmapsdir)
pkgdatadir="${datadir}/gde2-applets"
AC_SUBST(pkgdatadir)
builderdir="${pkgdatadir}/builder"
AC_SUBST(builderdir)

AC_DEFINE_DIR(GDE2_ICONDIR, "${iconsdir}", [Gde2 Icon Directory])
AC_DEFINE_DIR(GDE2_PIXMAPSDIR, "${pixmapsdir}", [Gde2 Pixmaps Directory])
AC_DEFINE_DIR(PKGDATADIR, "${pkgdatadir}", [Gde2 Applets Directory])
AC_DEFINE_DIR(GTK_BUILDERDIR, "${builderdir}", [GtkBuilder Resources Directory])
AC_DEFINE_DIR(DATADIR, "${datadir}", [datadir])
AC_DEFINE_DIR(PKG_DATA_DIR, "${pkgdatadir}", [pkgdatadir])
AC_DEFINE_DIR(SYSCONFDIR, "${sysconfdir}", [sysconfdir])
AC_DEFINE_DIR(LIBDIR, "${libdir}", [libdir])
AC_DEFINE_DIR(PREFIX, "$prefix", [install prefix])

AS_AC_EXPAND(DATADIR, "${datadir}")
AS_AC_EXPAND(PYTHONDIR, $pythondir)
AS_AC_EXPAND(BUILDERDIR, $builderdir)

AC_SUBST(VERSION)
AC_SUBST(PACKAGE)
AC_SUBST(DATADIR)
AC_SUBST(LIBDIR)
AC_SUBST(PYTHONDIR)
AC_SUBST(PKGDATADIR)
AC_SUBST(BUILDERDIR)

dnl ***************************************************************************
dnl *** Output Makefiles et al                                              ***
dnl ***************************************************************************
AC_OUTPUT([
Makefile
po/Makefile.in
accessx-status/Makefile
accessx-status/docs/Makefile
accessx-status/pixmaps/Makefile
drivemount/Makefile
drivemount/help/Makefile
multiload/Makefile
multiload/org.gde2.panel.applet.multiload.gschema.xml
multiload/docs/Makefile
charpick/Makefile
charpick/org.gde2.panel.applet.charpick.gschema.xml
charpick/help/Makefile
invest-applet/Makefile
invest-applet/docs/Makefile
invest-applet/invest/Makefile
invest-applet/invest/defs.py
invest-applet/data/Makefile
invest-applet/data/art/Makefile
gde2weather/Makefile
gde2weather/docs/Makefile
geyes/Makefile
geyes/org.gde2.panel.applet.geyes.gschema.xml
geyes/themes/Makefile
geyes/docs/Makefile
battstat/Makefile
battstat/org.gde2.panel.applet.battstat.gschema.xml
battstat/apmlib/Makefile
battstat/sounds/Makefile
battstat/docs/Makefile
man/Makefile
stickynotes/Makefile
stickynotes/org.gde2.stickynotes.gschema.xml
stickynotes/pixmaps/Makefile
stickynotes/docs/Makefile
trashapplet/Makefile
trashapplet/src/Makefile
trashapplet/docs/Makefile
cpufreq/Makefile
cpufreq/src/Makefile
cpufreq/org.gde2.panel.applet.cpufreq.gschema.xml
cpufreq/src/cpufreq-selector/Makefile
cpufreq/pixmaps/Makefile
cpufreq/help/Makefile
timerapplet/Makefile
timerapplet/org.gde2.panel.applet.timer.gschema.xml
command/Makefile
command/org.gde2.panel.applet.command.gschema.xml
netspeed/Makefile
netspeed/data/Makefile
netspeed/data/org.gde2.panel.applet.netspeed.gschema.xml
netspeed/icons/Makefile
netspeed/icons/16x16/Makefile
netspeed/icons/16x16/apps/Makefile
netspeed/icons/16x16/devices/Makefile
netspeed/icons/22x22/Makefile
netspeed/icons/22x22/apps/Makefile
netspeed/icons/24x24/Makefile
netspeed/icons/24x24/apps/Makefile
netspeed/icons/24x24/status/Makefile
netspeed/icons/32x32/Makefile
netspeed/icons/32x32/apps/Makefile
netspeed/icons/48x48/Makefile
netspeed/icons/48x48/apps/Makefile
netspeed/icons/scalable/Makefile
netspeed/icons/scalable/apps/Makefile
netspeed/src/Makefile
netspeed/help/Makefile
])

dnl ***************************************************************************
dnl *** Display Summary                                                     ***
dnl ***************************************************************************
echo "
gde2-applets-$VERSION configure summary:

    Prefix:                        ${prefix}
    Source code location:          ${srcdir}
    Compiler:                      ${CC}

    GTK+ version:                  ${GTK_API_VERSION}

    Building:
        - accessx-status           $HAVE_XKB
        - battstat                 $build_battstat_applet
        - charpick                 always
            - gucharmap support    $have_gucharmap
        - cpufreq                  $build_cpufreq_applet
            - building selector    $enable_selector
            - using PolicyKit      $HAVE_POLKIT
            - enabling suid bit    $enable_suid
        - drivemount               always
        - geyes                    always
        - gde2weather              $build_libgde2weather_applets
        - invest-applet            $HAVE_PYGOBJECT
        - multiload                $build_gtop_applets
        - netspeed                 $build_gtop_applets
            - iwlib support        $have_iwevgenie
        - stickynotes              $enable_stickynotes
        - timerapplet              $HAVE_LIBNOTIFY
        - trashapplet              always

    Using DBUS:                    $HAVE_DBUS
    Using UPOWER:                  $HAVE_UPOWER
    Using libnotify:               $HAVE_LIBNOTIFY
    Enabling IPv6:                 $have_ipv6
" >&2
