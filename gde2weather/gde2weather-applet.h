#ifndef __GDE2WEATHER_APPLET_H_
#define __GDE2WEATHER_APPLET_H_

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

#define GDE2WEATHER_I_KNOW_THIS_IS_UNSTABLE

#include "gde2weather.h"

G_BEGIN_DECLS

extern void gde2weather_applet_create(Gde2WeatherApplet *gw_applet);
extern gint timeout_cb (gpointer data);
extern gint suncalc_timeout_cb (gpointer data);
extern void gde2weather_update (Gde2WeatherApplet *applet);

G_END_DECLS

#endif /* __GDE2WEATHER_APPLET_H_ */

