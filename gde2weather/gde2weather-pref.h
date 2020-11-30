/* $Id$ */

/*
 *  Papadimitriou Spiros <spapadim+@cs.cmu.edu>
 *
 *  This code released under the GNU GPL.
 *  Read the file COPYING for more information.
 *
 *  Preferences dialog
 *
 */

#ifndef __GDE2WEATHER_PREF_H_
#define __GDE2WEATHER_PREF_H_

#include <gtk/gtk.h>

#define GDE2WEATHER_I_KNOW_THIS_IS_UNSTABLE

#include "gde2weather.h"

G_BEGIN_DECLS

#define GDE2WEATHER_TYPE_PREF		(gde2weather_pref_get_type ())
#define GDE2WEATHER_PREF(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2WEATHER_TYPE_PREF, Gde2WeatherPref))
#define GDE2WEATHER_PREF_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), GDE2WEATHER_TYPE_PREF, Gde2WeatherPrefClass))
#define GDE2WEATHER_IS_PREF(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2WEATHER_TYPE_PREF))
#define GDE2WEATHER_IS_PREF_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2WEATHER_TYPE_PREF))
#define GDE2WEATHER_PREF_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2WEATHER_TYPE_PREF, Gde2WeatherPrefClass))

typedef struct _Gde2WeatherPref Gde2WeatherPref;
typedef struct _Gde2WeatherPrefPrivate Gde2WeatherPrefPrivate;
typedef struct _Gde2WeatherPrefClass Gde2WeatherPrefClass;

struct _Gde2WeatherPref
{
	GtkDialog parent;

	/* private */
	Gde2WeatherPrefPrivate *priv;
};


struct _Gde2WeatherPrefClass
{
	GtkDialogClass parent_class;
};

GType		 gde2weather_pref_get_type	(void);
GtkWidget	*gde2weather_pref_new	(Gde2WeatherApplet *applet);


void set_access_namedesc (GtkWidget *widget, const gchar *name, const gchar *desc);


G_END_DECLS

#endif /* __GDE2WEATHER_PREF_H */

