SUBDIRS = help pixmaps src

@INTLTOOL_XML_NOMERGE_RULE@
cpufreq_gschema_in_files = org.gde2.panel.applet.cpufreq.gschema.xml.in
gsettings_SCHEMAS = $(cpufreq_gschema_in_files:.xml.in=.xml)
@GSETTINGS_RULES@

appletdir       = $(datadir)/gde2-panel/applets
applet_in_files = org.gde2.applets.CPUFreqApplet.gde2-panel-applet.in
applet_DATA     = $(applet_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applet_in_files): $(applet_in_files).in Makefile
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            -e "s|\@VERSION\@|$(PACKAGE_VERSION)|" \
            $< > $@

%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.CPUFreqAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.CPUFreqAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            $< > $@

builder_DATA = cpufreq-preferences.ui

uidir = $(datadir)/gde2/ui
ui_DATA = cpufreq-applet-menu.xml

CLEANFILES = \
             $(applet_DATA)			\
             $(applet_DATA).in			\
             $(service_DATA)			\
	     $(gsettings_SCHEMAS)               \
	     *.gschema.valid                    \
	     *.bak                              \
	     *.gladep

EXTRA_DIST = \
             org.gde2.applets.CPUFreqApplet.gde2-panel-applet.in.in	\
             $(service_in_files)				\
	     $(cpufreq_gschema_in_files)			\
	     $(builder_DATA)                 			\
	     $(ui_DATA)
	     
					


-include $(top_srcdir)/git.mk
