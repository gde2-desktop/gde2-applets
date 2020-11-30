#ifndef __GDE2WEATHER_DIALOG_H_
#define __GDE2WEATHER_DIALOG_H_

/* $Id$ */

/*
 *  Papadimitriou Spiros <spapadim+@cs.cmu.edu>
 *
 *  This code released under the GNU GPL.
 *  Read the file COPYING for more information.
 *
 *  Main status dialog
 *
 */

#include <gtk/gtk.h>

#define GDE2WEATHER_I_KNOW_THIS_IS_UNSTABLE

#include "gde2weather.h"

G_BEGIN_DECLS

#define GDE2WEATHER_TYPE_DIALOG		(gde2weather_dialog_get_type ())
#define GDE2WEATHER_DIALOG(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2WEATHER_TYPE_DIALOG, Gde2WeatherDialog))
#define GDE2WEATHER_DIALOG_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), GDE2WEATHER_TYPE_DIALOG, Gde2WeatherDialogClass))
#define GDE2WEATHER_IS_DIALOG(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2WEATHER_TYPE_DIALOG))
#define GDE2WEATHER_IS_DIALOG_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2WEATHER_TYPE_DIALOG))
#define GDE2WEATHER_DIALOG_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2WEATHER_TYPE_DIALOG, Gde2WeatherDialogClass))

typedef struct _Gde2WeatherDialog Gde2WeatherDialog;
typedef struct _Gde2WeatherDialogPrivate Gde2WeatherDialogPrivate;
typedef struct _Gde2WeatherDialogClass Gde2WeatherDialogClass;

struct _Gde2WeatherDialog
{
	GtkDialog parent;

	/* private */
	Gde2WeatherDialogPrivate *priv;
};


struct _Gde2WeatherDialogClass
{
	GtkDialogClass parent_class;
};

GType		 gde2weather_dialog_get_type	(void);
GtkWidget	*gde2weather_dialog_new		(Gde2WeatherApplet *applet);
void		 gde2weather_dialog_update		(Gde2WeatherDialog *dialog);

G_END_DECLS

#endif /* __GDE2WEATHER_DIALOG_H_ */

