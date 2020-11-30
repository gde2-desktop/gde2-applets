/* $Id$ */

/*
 *  Papadimitriou Spiros <spapadim+@cs.cmu.edu>
 *
 *  This code released under the GNU GPL.
 *  Read the file COPYING for more information.
 *
 *  About box
 *
 */

#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <libgde2-desktop/gde2-aboutdialog.h>

#define GDE2WEATHER_I_KNOW_THIS_IS_UNSTABLE

#include "gde2weather.h"
#include "gde2weather-about.h"

void gde2weather_about_run(Gde2WeatherApplet* gw_applet)
{
	static const gchar* authors[] = {
		"Todd Kulesza <fflewddur@dropline.net>",
		"Philip Langdale <philipl@mail.utexas.edu>",
		"Ryan Lortie <desrt@desrt.ca>",
		"Davyd Madeley <davyd@madeley.id.au>",
		"Spiros Papadimitriou <spapadim+@cs.cmu.edu>",
		"Kevin Vandersloot <kfv101@psu.edu>",
		NULL
	};

	const gchar* documenters[] = {
		"Dan Mueth <d-mueth@uchicago.edu>",
		"Spiros Papadimitriou <spapadim+@cs.cmu.edu>",
		"Sun GNOME Documentation Team <gdocteam@sun.com>",
		"Davyd Madeley <davyd@madeley.id.au>",
		NULL
	};

	gde2_show_about_dialog(NULL,
		"version", VERSION,
		"copyright", _("\xC2\xA9 1999-2005 by S. Papadimitriou and others"),
		"comments", _("A panel application for monitoring local weather conditions."),
		"authors", authors,
		"documenters", documenters,
		"translator-credits", _("translator-credits"),
		"logo-icon-name", "weather-storm",
		NULL);
}
