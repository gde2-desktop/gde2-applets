SUBDIRS = docs

AM_CPPFLAGS =			\
	-I$(srcdir)		\
	-DMULTILOAD_MENU_UI_DIR=\""$(uidir)"\" \
	$(GDE2_APPLETS4_CFLAGS)	\
	$(GTOP_APPLETS_CFLAGS)	\
	$(GDE2DESKTOP_CFLAGS)	\
	$(GIO_CFLAGS)

libexec_PROGRAMS = gde2-multiload-applet

gde2_multiload_applet_SOURCES = \
			global.h	\
			linux-proc.h	\
			load-graph.h	\
			linux-proc.c	\
			load-graph.c	\
			main.c	\
			properties.c	\
			netspeed.c netspeed.h \
			autoscaler.c	\
			autoscaler.h

gde2_multiload_applet_LDADD = \
				$(GDE2_APPLETS4_LIBS) 	\
				$(GTOP_APPLETS_LIBS)	\
				$(GDE2DESKTOP_LIBS)		\
				$(GIO_LIBS)				\
				-lm

@INTLTOOL_XML_NOMERGE_RULE@
multiload_gschema_in_files = org.gde2.panel.applet.multiload.gschema.xml.in
gsettings_SCHEMAS = $(multiload_gschema_in_files:.xml.in=.xml)
@GSETTINGS_RULES@

EXTRA_DIST =							\
	org.gde2.applets.MultiLoadApplet.gde2-panel-applet.in.in	\
	$(service_in_files)					\
	$(multiload_gschema_in_files)				\
	$(ui_DATA)

uidir		= $(datadir)/gde2/ui
ui_DATA		= multiload-applet-menu.xml

appletdir       = $(datadir)/gde2-panel/applets
applet_in_files = org.gde2.applets.MultiLoadApplet.gde2-panel-applet.in
applet_DATA     = $(applet_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applet_in_files): $(applet_in_files).in Makefile
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            -e "s|\@VERSION\@|$(PACKAGE_VERSION)|" \
            $< > $@

%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.MultiLoadAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.MultiLoadAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            $< > $@

CLEANFILES = $(applet_DATA) $(applet_DATA).in $(service_DATA) $(gsettings_SCHEMAS) *.gschema.valid

-include $(top_srcdir)/git.mk
