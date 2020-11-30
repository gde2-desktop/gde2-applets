SUBDIRS = themes docs

AM_CPPFLAGS =						\
	-I.						\
	-I$(srcdir) 					\
	$(GDE2_APPLETS4_CFLAGS)			\
	$(GDE2DESKTOP_CFLAGS)			\
	-I$(includedir) 				\
	-DGEYES_THEMES_DIR=\""$(pkgdatadir)/geyes/"\"	\
	-DGEYES_MENU_UI_DIR=\""$(uidir)"\"

libexec_PROGRAMS = gde2-geyes-applet

gde2_geyes_applet_SOURCES =	\
        geyes.c \
	themes.c \
	geyes.h

gde2_geyes_applet_LDADD = 		\
	$(GDE2_APPLETS4_LIBS) \
	$(GDE2DESKTOP_LIBS) \
	-lm

appletdir       = $(datadir)/gde2-panel/applets
applet_in_files = org.gde2.applets.GeyesApplet.gde2-panel-applet.in
applet_DATA     = $(applet_in_files:.gde2-panel-applet.in=.gde2-panel-applet)

$(applet_in_files): $(applet_in_files).in Makefile
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            -e "s|\@VERSION\@|$(PACKAGE_VERSION)|" \
            $< > $@

%.gde2-panel-applet: %.gde2-panel-applet.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

servicedir       = $(datadir)/dbus-1/services
service_in_files = org.gde2.panel.applet.GeyesAppletFactory.service.in
service_DATA     = $(service_in_files:.service.in=.service)

org.gde2.panel.applet.GeyesAppletFactory.service: $(service_in_files)
	$(AM_V_GEN)sed \
            -e "s|\@LIBEXECDIR\@|$(libexecdir)|" \
            $< > $@

uidir = $(datadir)/gde2/ui
ui_DATA = geyes-applet-menu.xml

@INTLTOOL_XML_NOMERGE_RULE@
geyes_gschema_in_files = org.gde2.panel.applet.geyes.gschema.xml.in
gsettings_SCHEMAS = $(geyes_gschema_in_files:.xml.in=.xml)
@GSETTINGS_RULES@

themesdir = $(pkgdatadir)/geyes

icons =	\
	gde2-eyes-applet.svg	 \
	gde2-eyes-applet.32.png \
	gde2-eyes-applet.24.png \
	gde2-eyes-applet.22.png \
	gde2-eyes-applet.16.png

CLEANFILES = $(applet_DATA) $(applet_DATA).in $(service_DATA) $(gsettings_SCHEMAS) *.gschema.valid

EXTRA_DIST = \
	     README.themes					\
	     org.gde2.applets.GeyesApplet.gde2-panel-applet.in.in 	\
             $(service_in_files)				\
	     $(geyes_gschema_in_files)				\
	     $(ui_DATA)						\
	     $(icons)

gtk_update_icon_cache = gtk-update-icon-cache -f -t $(datadir)/icons/hicolor

uninstall-local:
	for icon in $(icons); do \
		SIZE=`echo $$icon | cut -d. -f2`; \
		FILE=`echo $$icon | cut -d. -f1,3`; \
		if [ "$$SIZE" = "svg" ]; then \
			SIZE="scalable"; \
			FILE="$$FILE.svg"; \
		else \
			SIZE="$${SIZE}x$${SIZE}"; \
		fi; \
		rm -f $(DESTDIR)$(iconsdir)/hicolor/$$SIZE/apps/$$FILE; \
	done
	@-if test -z "$(DESTDIR)"; then \
		echo "Updating Gtk icon cache."; \
		$(gtk_update_icon_cache); \
	else \
		echo "*** Icon cache not updated. After install, run this:"; \
		echo "***   $(gtk_update_icon_cache)"; \
	fi

install-data-local:
	for icon in $(icons); do \
		SIZE=`echo $$icon | cut -d. -f2`; \
		FILE=`echo $$icon | cut -d. -f1,3`; \
		if [ "$$SIZE" = "svg" ]; then \
			SIZE="scalable"; \
			FILE="$$FILE.svg"; \
		else \
			SIZE="$${SIZE}x$${SIZE}"; \
		fi; \
		mkdir -p $(DESTDIR)$(iconsdir)/hicolor/$$SIZE/apps/; \
		$(INSTALL_DATA) $(srcdir)/$$icon $(DESTDIR)$(iconsdir)/hicolor/$$SIZE/apps/$$FILE; \
	done
	@-if test -z "$(DESTDIR)"; then \
		echo "Updating Gtk icon cache."; \
		$(gtk_update_icon_cache); \
	else \
		echo "*** Icon cache not updated. After install, run this:"; \
		echo "***   $(gtk_update_icon_cache)"; \
	fi

-include $(top_srcdir)/git.mk
