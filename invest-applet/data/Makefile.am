SUBDIRS = art

# ******************************************************************************
# Panel applet DBUS stuff
# ******************************************************************************
servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.InvestAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.InvestAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            $< > $@

# ******************************************************************************
# Panel stuff
# ******************************************************************************

appletdir       = $(datadir)/gde2-panel/applets
applet_in_files = org.gde2.applets.InvestApplet.gde2-panel-applet.in
applet_DATA     = $(applet_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applet_in_files): $(applet_in_files).in Makefile
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            -e "s|\@VERSION\@|$(PACKAGE_VERSION)|" \
            $< > $@

%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

# ******************************************************************************
# Misc data
# ******************************************************************************

uidir = $(datadir)/gde2-applets
ui_DATA = \
	Invest_Applet.xml
builder_DATA = \
	prefs-dialog.ui \
	financialchart.ui

investbindir = $(libdir)/invest-applet

# ******************************************************************************
# Build rules
# ******************************************************************************

CLEANFILES = \
	$(applet_DATA) \
	$(applet_DATA).in \
	$(service_in_files:.service.in=.service)



EXTRA_DIST = \
	org.gde2.applets.InvestApplet.gde2-panel-applet.in.in \
	$(service_in_files) \
	$(ui_DATA) \
	$(builder_DATA)

-include $(top_srcdir)/git.mk
