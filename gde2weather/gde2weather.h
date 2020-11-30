#ifndef __GDE2WEATHER_H__
#define __GDE2WEATHER_H__

/*
 *  todd kulesza <fflewddur@dropline.net>
 *
 *  This code released under the GNU GPL.
 *  Read the file COPYING for more information.
 *
 * main header file
 *
 */
#include <glib/gi18n.h>

#include <gio/gio.h>

#include <gde2-panel-applet.h>

#include <libgde2weather/gde2weather-prefs.h>


/* Radar map on by default. */
#define RADARMAP

G_BEGIN_DECLS

typedef struct _Gde2WeatherApplet {
	Gde2PanelApplet* applet;
	WeatherInfo* gde2weather_info;

	GSettings* settings;

	GtkWidget* container;
	GtkWidget* box;
	GtkWidget* label;
	GtkWidget* image;

	Gde2PanelAppletOrient orient;
	gint size;
	gint timeout_tag;
	gint suncalc_timeout_tag;

	/* preferences  */
	Gde2WeatherPrefs gde2weather_pref;

	GtkWidget* pref_dialog;

	/* dialog stuff */
	GtkWidget* details_dialog;
} Gde2WeatherApplet;

G_END_DECLS

#endif
