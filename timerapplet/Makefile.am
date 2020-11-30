AM_CPPFLAGS = \
	$(GDE2_APPLETS4_CFLAGS) \
	$(GDE2DESKTOP_CFLAGS) \
	$(LIBNOTIFY_CFLAGS) \
	-I$(srcdir) \
	-DGDE2LOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(DISABLE_DEPRECATED_CFLAGS)

APPLET_LOCATION = $(libexecdir)/timer-applet

libexec_PROGRAMS = timer-applet
timer_applet_SOURCES = timerapplet.c
timer_applet_LDADD = $(GDE2_APPLETS4_LIBS) $(GDE2DESKTOP_LIBS) $(LIBNOTIFY_LIBS)
timer_applet_CFLAGS = $(WARN_CFLAGS)

appletsdir       = $(datadir)/gde2-panel/applets
applets_in_files = org.gde2.applets.TimerApplet.gde2-panel-applet.in
applets_DATA     = $(applets_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applets_in_files): $(applets_in_files).in Makefile
	$(AM_V_GEN)sed \
		-e "s|\@LOCATION\@|$(APPLET_LOCATION)|" \
		$< > $@
%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.TimerAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.TimerAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
		-e "s|\@LOCATION\@|$(APPLET_LOCATION)|" \
		$< > $@

@INTLTOOL_XML_NOMERGE_RULE@
timer_gschema_in_files = org.gde2.panel.applet.timer.gschema.xml.in
gsettings_SCHEMAS = $(timer_gschema_in_files:.xml.in=.xml)
@GSETTINGS_RULES@

EXTRA_DIST = \
	$(applets_in_files).in \
	$(service_in_files) \
	$(timer_gschema_in_files)

CLEANFILES = $(applets_DATA) $(applets_DATA).in $(service_DATA) $(gsettings_SCHEMAS) *.gschema.valid
