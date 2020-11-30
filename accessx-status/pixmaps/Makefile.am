accessx_status_iconsdir = $(iconsdir)/hicolor/48x48/apps
accessx_status_icons_DATA = gde2-ax-applet.png

accessx_status_pixmapsdir  = $(pixmapsdir)/gde2-accessx-status-applet
accessx_status_pixmaps_DATA =	\
	gde2-ax-applet.png			\
	gde2-ax-key-base.png			\
	gde2-ax-key-inverse.png			\
	gde2-ax-key-none.png			\
	gde2-ax-key-yes.png			\
	gde2-ax-key-no.png			\
	gde2-mousekeys-base.png			\
	gde2-mousekeys-pressed-left.png		\
	gde2-mousekeys-pressed-middle.png	\
	gde2-mousekeys-pressed-right.png	\
	gde2-mousekeys-default-left.png		\
	gde2-mousekeys-default-middle.png	\
	gde2-mousekeys-default-right.png	\
	gde2-sticky-shift-none.png		\
	gde2-sticky-shift-latched.png		\
	gde2-sticky-shift-locked.png		\
	gde2-sticky-ctrl-none.png		\
	gde2-sticky-ctrl-latched.png		\
	gde2-sticky-ctrl-locked.png		\
	gde2-sticky-alt-none.png		\
	gde2-sticky-alt-latched.png		\
	gde2-sticky-alt-locked.png		\
	gde2-sticky-meta-latched.png		\
	gde2-sticky-meta-locked.png		\
	gde2-sticky-meta-none.png		\
	gde2-sticky-hyper-latched.png		\
	gde2-sticky-hyper-locked.png		\
	gde2-sticky-hyper-none.png		\
	gde2-sticky-super-latched.png		\
	gde2-sticky-super-locked.png		\
	gde2-sticky-super-none.png		\
	gde2-ax-slowkeys.png			\
	gde2-ax-slowkeys-pending.png		\
	gde2-ax-slowkeys-yes.png		\
	gde2-ax-slowkeys-no.png			\
	gde2-ax-bouncekeys.png

gtk_update_icon_cache = gtk-update-icon-cache -f -t $(iconsdir)/hicolor
install-data-hook: update-icon-cache
uninstall-hook: update-icon-cache
update-icon-cache:
	@-if test -z "$(DESTDIR)"; then \
		echo "Updating Gtk icon cache."; \
		$(gtk_update_icon_cache); \
	else \
		echo "*** Icon cache not updated. After install, run this:"; \
		echo "***   $(gtk_update_icon_cache)"; \
	fi

EXTRA_DIST = \
	$(accessx_status_pixmaps_DATA)

-include $(top_srcdir)/git.mk
