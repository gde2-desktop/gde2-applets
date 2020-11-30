SUBDIRS = help

AM_CPPFLAGS =					\
	-I.					\
	-I$(srcdir)				\
	-DCHARPICK_MENU_UI_DIR=\""$(uidir)"\"	\
	$(GDE2_APPLETS4_CFLAGS)		\
	$(GDE2DESKTOP_CFLAGS)		\
	$(GUCHARMAP_CFLAGS)

libexec_PROGRAMS = gde2-charpick-applet

gde2_charpick_applet_SOURCES = charpick.c \
                          charpick.h \
                          properties.c

gde2_charpick_applet_LDADD = \
		       $(GDE2_APPLETS4_LIBS)	\
		       $(GDE2DESKTOP_LIBS)	\
		       $(GUCHARMAP_LIBS)

appletdir       = $(datadir)/gde2-panel/applets
applet_in_files = org.gde2.applets.CharpickerApplet.gde2-panel-applet.in
applet_DATA     = $(applet_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applet_in_files): $(applet_in_files).in Makefile
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            -e "s|\@VERSION\@|$(PACKAGE_VERSION)|" \
            $< > $@

%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.CharpickerAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.CharpickerAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            $< > $@

@INTLTOOL_XML_NOMERGE_RULE@
charpick_gschema_in_files = org.gde2.panel.applet.charpick.gschema.xml.in
gsettings_SCHEMAS = $(charpick_gschema_in_files:.xml.in=.xml)
@GSETTINGS_RULES@

uidir = $(datadir)/gde2/ui
ui_DATA = charpick-applet-menu.xml

CLEANFILES = $(applet_DATA) $(applet_DATA).in $(service_DATA) $(gsettings_SCHEMAS) *.gschema.valid

EXTRA_DIST =							\
	org.gde2.applets.CharpickerApplet.gde2-panel-applet.in.in	\
	$(service_in_files)					\
	$(ui_DATA)						\
	$(charpick_gschema_in_files)

-include $(top_srcdir)/git.mk
