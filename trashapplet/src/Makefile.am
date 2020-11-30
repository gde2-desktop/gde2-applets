AM_CPPFLAGS = -I$(top_srcdir)		\
	   $(GDE2_APPLETS4_CFLAGS)	\
	   $(GDE2DESKTOP_CFLAGS)	\
	   $(GIO_CFLAGS)		\
           -DTRASH_MENU_UI_DIR=\""$(datadir)/gde2/ui"\"

libexec_PROGRAMS = trashapplet

trashapplet_SOURCES = \
	trashapplet.c \
	trash-empty.h \
	trash-empty.c \
	xstuff.c \
	xstuff.h

trashapplet_LDADD = 		\
	$(GDE2_APPLETS4_LIBS) 	\
	$(GDE2DESKTOP_LIBS) 	\
	$(GIO_LIBS) \
	-lX11

-include $(top_srcdir)/git.mk
