## Process this file with automake to produce Makefile.in

SUBDIRS = docs

AM_CPPFLAGS =					\
	-I$(srcdir)				\
	-I$(top_srcdir)				\
	-DGDE2WEATHER_MENU_UI_DIR=\""$(uidir)"\"	\
	$(GDE2_APPLETS4_CFLAGS)		\
	$(GDE2DESKTOP_CFLAGS)		\
	$(LIBNOTIFY_CFLAGS)			\
	$(LIBGDE2WEATHER_CFLAGS)			\
	$(DBUS_CFLAGS)

libexec_PROGRAMS = gde2weather-applet

gde2weather_applet_SOURCES = \
	gde2weather.h \
	main.c \
	gde2weather-about.c gde2weather-about.h \
	gde2weather-pref.c gde2weather-pref.h \
	gde2weather-dialog.c gde2weather-dialog.h \
	gde2weather-applet.c gde2weather-applet.h

gde2weather_applet_LDADD = 	\
	$(LIBNOTIFY_LIBS) 	\
	$(GDE2_APPLETS4_LIBS)	\
	$(GDE2DESKTOP_LIBS)	\
	$(GDE2_LIBS2_LIBS)	\
	$(LIBGDE2WEATHER_LIBS)	\
	$(DBUS_LIBS)

uidir = $(datadir)/gde2/ui
ui_DATA = gde2weather-applet-menu.xml

appletdir       = $(datadir)/gde2-panel/applets
applet_in_files = org.gde2.applets.Gde2WeatherApplet.gde2-panel-applet.in
applet_DATA     = $(applet_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applet_in_files): $(applet_in_files).in Makefile
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            -e "s|\@VERSION\@|$(PACKAGE_VERSION)|" \
            $< > $@

%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.Gde2WeatherAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.Gde2WeatherAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            $< > $@

CLEANFILES = $(applet_DATA) $(applet_DATA).in $(service_DATA)

EXTRA_DIST = \
	org.gde2.applets.Gde2WeatherApplet.gde2-panel-applet.in.in	\
	$(service_in_files)					\
	$(ui_DATA)

-include $(top_srcdir)/git.mk
