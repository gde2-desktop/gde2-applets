AM_CPPFLAGS = -I$(top_srcdir) -I$(includedir) \
       $(GIO_CFLAGS) $(GTOP_APPLETS_CFLAGS) \
       $(GDE2_APPLETS4_CFLAGS) $(GDE2DESKTOP_CFLAGS) \
       -DGDE2LOCALEDIR=\""$(datadir)/locale"\" \
       -DNETSPEED_MENU_UI_DIR=\""$(datadir)/gde2/ui"\"

libexec_PROGRAMS = gde2-netspeed-applet

gde2_netspeed_applet_SOURCES = backend.h backend.c netspeed.c

gde2_netspeed_applet_LDADD = $(GIO_LIBS) $(GTOP_APPLETS_LIBS) \
       $(GDE2_APPLETS4_LIBS) $(GDE2DESKTOP_LIBS) \
       $(IWLIB) $(INTLLIBS) -lm

