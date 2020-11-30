/* $Id$ */

/*
 *  Papadimitriou Spiros <spapadim+@cs.cmu.edu>
 *
 *  This code released under the GNU GPL.
 *  Read the file COPYING for more information.
 *
 *  Main applet widget
 *
 */

#include <glib.h>
#include <config.h>
#include <gtk/gtk.h>
#include <gio/gio.h>
#include <gde2-panel-applet.h>
#include <gde2-panel-applet-gsettings.h>

#define GDE2WEATHER_I_KNOW_THIS_IS_UNSTABLE

#include <libgde2weather/gde2weather-prefs.h>

#include "gde2weather.h"
#include "gde2weather-pref.h"
#include "gde2weather-dialog.h"
#include "gde2weather-applet.h"


static gboolean gde2weather_applet_new(Gde2PanelApplet* applet, const gchar* iid, gpointer data)
{
	Gde2WeatherApplet* gw_applet;

	gw_applet = g_new0(Gde2WeatherApplet, 1);

	gw_applet->applet = applet;
	gw_applet->gde2weather_info = NULL;
	gw_applet->settings = gde2_panel_applet_settings_new (applet, "org.gde2.weather");

	gde2weather_applet_create(gw_applet);

	gde2weather_prefs_load(&gw_applet->gde2weather_pref, gw_applet->settings);

	gde2weather_update(gw_applet);

	return TRUE;
}

static gboolean gde2weather_applet_factory(Gde2PanelApplet* applet, const gchar* iid, gpointer data)
{
	gboolean retval = FALSE;

	retval = gde2weather_applet_new(applet, iid, data);

	return retval;
}

GDE2_PANEL_APPLET_OUT_PROCESS_FACTORY("Gde2WeatherAppletFactory", PANEL_TYPE_APPLET, "gde2weather", gde2weather_applet_factory, NULL)
