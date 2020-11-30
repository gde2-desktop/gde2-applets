if BUILD_CPUFREQ_SELECTOR
selector_SUBDIR = cpufreq-selector
endif

SUBDIRS = $(selector_SUBDIR)

AM_CPPFLAGS = \
	-DCPUFREQ_MENU_UI_DIR=\""$(datadir)/gde2/ui"\" 	\
	$(GDE2_APPLETS4_CFLAGS) 				\
	$(GDE2DESKTOP_CFLAGS) 				\
	$(DBUS_CFLAGS)

libexec_PROGRAMS = gde2-cpufreq-applet

if HAVE_LIBCPUFREQ
cpufreq_files=cpufreq-monitor-libcpufreq.c    cpufreq-monitor-libcpufreq.h
endif

gde2_cpufreq_applet_SOURCES =  \
	cpufreq-applet.c        	cpufreq-applet.h        	\
	cpufreq-utils.c			cpufreq-utils.h			\
	cpufreq-prefs.c         	cpufreq-prefs.h         	\
	cpufreq-selector.c		cpufreq-selector.h		\
	cpufreq-popup.c                 cpufreq-popup.h			\
	cpufreq-monitor.c       	cpufreq-monitor.h	      	\
	cpufreq-monitor-factory.c	cpufreq-monitor-factory.h	\
	cpufreq-monitor-procfs.c	cpufreq-monitor-procfs.h	\
	cpufreq-monitor-sysfs.c	        cpufreq-monitor-sysfs.h	        \
	$(cpufreq_files)						\
	cpufreq-monitor-cpuinfo.c       cpufreq-monitor-cpuinfo.h

gde2_cpufreq_applet_LDADD =  \
	$(GDE2_APPLETS4_LIBS)   	\
	$(GDE2DESKTOP_LIBS)   	\
	$(LIBCPUFREQ_LIBS)		\
	$(DBUS_LIBS)

	

-include $(top_srcdir)/git.mk
