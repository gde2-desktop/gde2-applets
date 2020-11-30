AM_CPPFLAGS = \
	$(GDE2_APPLETS4_CFLAGS) \
	$(GDE2DESKTOP_CFLAGS) \
	-I$(srcdir) \
	-DGDE2LOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(DISABLE_DEPRECATED_CFLAGS)

APPLET_LOCATION = $(libexecdir)/command-applet

libexec_PROGRAMS = command-applet
command_applet_SOURCES = command.c
command_applet_LDADD = $(GDE2_APPLETS4_LIBS) $(GDE2DESKTOP_LIBS)
command_applet_CFLAGS = $(WARN_CFLAGS)

appletsdir       = $(datadir)/gde2-panel/applets
applets_in_files = org.gde2.applets.CommandApplet.gde2-panel-applet.in
applets_DATA     = $(applets_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applets_in_files): $(applets_in_files).in Makefile
	$(AM_V_GEN)sed \
		-e "s|\@LOCATION\@|$(APPLET_LOCATION)|" \
		$< > $@
%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.CommandAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.CommandAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
		-e "s|\@LOCATION\@|$(APPLET_LOCATION)|" \
		$< > $@

@INTLTOOL_XML_NOMERGE_RULE@
command_gschema_in_files = org.gde2.panel.applet.command.gschema.xml.in
gsettings_SCHEMAS = $(command_gschema_in_files:.xml.in=.xml)
@GSETTINGS_RULES@

EXTRA_DIST = \
	$(applets_in_files).in \
	$(service_in_files) \
	$(command_gschema_in_files)

CLEANFILES = $(applets_DATA) $(applets_DATA).in $(service_DATA) $(gsettings_SCHEMAS) *.gschema.valid
