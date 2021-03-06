/* command.c:
 *
 * Copyright (C) 2013-2014 Stefano Karapetsas
 *
 * This file is part of GDE2 Applets.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Authors:
 *      Stefano Karapetsas <stefano@karapetsas.com>
 */

#include <config.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <libgde2-desktop/gde2-aboutdialog.h>

#include <gde2-panel-applet.h>
#include <gde2-panel-applet-gsettings.h>

/* Applet constants */
#define APPLET_ICON    "utilities-terminal"
#define ERROR_OUTPUT   "#"

/* GSettings constants */
#define COMMAND_SCHEMA "org.gde2.panel.applet.command"
#define COMMAND_KEY    "command"
#define INTERVAL_KEY   "interval"
#define SHOW_ICON_KEY  "show-icon"
#define WIDTH_KEY      "width"

/* GKeyFile constants */
#define GK_COMMAND_GROUP   "Command"
#define GK_COMMAND_OUTPUT  "Output"
#define GK_COMMAND_ICON    "Icon"

#if GTK_CHECK_VERSION (3, 0, 0)
#define gtk_hbox_new(X,Y) gtk_box_new(GTK_ORIENTATION_HORIZONTAL,Y)
#endif

typedef struct
{
    Gde2PanelApplet   *applet;

    GSettings         *settings;

    GtkLabel          *label;
    GtkImage          *image;
    GtkBox            *box;

    gchar             *command;
    gint               interval;
    gint               width;

    guint              timeout_id;
} CommandApplet;

static void command_about_callback (GtkAction *action, CommandApplet *command_applet);
static void command_settings_callback (GtkAction *action, CommandApplet *command_applet);
static gboolean command_execute (CommandApplet *command_applet);

static const GtkActionEntry applet_menu_actions [] = {
    { "Preferences", GTK_STOCK_PROPERTIES, N_("_Preferences"), NULL, NULL, G_CALLBACK (command_settings_callback) },
    { "About", GTK_STOCK_ABOUT, N_("_About"), NULL, NULL, G_CALLBACK (command_about_callback) }
};

static char *ui = "<menuitem name='Item 1' action='Preferences' />"
                  "<menuitem name='Item 2' action='About' />";

static void
command_applet_destroy (Gde2PanelApplet *applet_widget, CommandApplet *command_applet)
{
    g_assert (command_applet);

    if (command_applet->timeout_id != 0)
    {
        g_source_remove (command_applet->timeout_id);
        command_applet->timeout_id = 0;
    }

    if (command_applet->command != NULL)
    {
        g_free (command_applet->command);
        command_applet->command = NULL;
    }

    g_object_unref (command_applet->settings);
}

/* Show the about dialog */
static void
command_about_callback (GtkAction *action, CommandApplet *command_applet)
{
    const char* authors[] = { "Stefano Karapetsas <stefano@karapetsas.com>", NULL };

    gde2_show_about_dialog(NULL,
                          "version", VERSION,
                          "copyright", "Copyright © 2013-2014 Stefano Karapetsas",
                          "authors", authors,
                          "comments", _("Shows the output of a command"),
                          "translator-credits", _("translator-credits"),
                          "logo-icon-name", APPLET_ICON,
    NULL );
}

/* Show the preferences dialog */
static void
command_settings_callback (GtkAction *action, CommandApplet *command_applet)
{
    GtkDialog *dialog;
    GtkTable *table;
    GtkWidget *widget;
    GtkWidget *command;
    GtkWidget *interval;
    GtkWidget *width;
    GtkWidget *showicon;

    dialog = GTK_DIALOG (gtk_dialog_new_with_buttons(_("Command Applet Preferences"),
                                                     NULL,
                                                     GTK_DIALOG_MODAL,
                                                     GTK_STOCK_CLOSE,
                                                     GTK_RESPONSE_CLOSE,
                                                     NULL));
    table = GTK_TABLE (gtk_table_new (4, 2, FALSE));
    gtk_table_set_row_spacings (table, 12);
    gtk_table_set_col_spacings (table, 12);

    gtk_window_set_default_size (GTK_WINDOW (dialog), 350, 150);
    gtk_container_set_border_width (GTK_CONTAINER (dialog), 10);

    widget = gtk_label_new (_("Command:"));
#if GTK_CHECK_VERSION (3, 16, 0)
    gtk_label_set_xalign (GTK_LABEL (widget), 1.0);
    gtk_label_set_yalign (GTK_LABEL (widget), 0.5);
#else
    gtk_misc_set_alignment (GTK_MISC (widget), 1.0, 0.5);
#endif
    gtk_table_attach (table, widget, 1, 2, 0, 1,
                      GTK_FILL, GTK_FILL,
                      0, 0);

    command = gtk_entry_new ();
    gtk_table_attach (table, command, 2, 3, 0, 1,
                      GTK_EXPAND | GTK_FILL | GTK_SHRINK, GTK_FILL,
                      0, 0);

    widget = gtk_label_new (_("Interval (seconds):"));
#if GTK_CHECK_VERSION (3, 16, 0)
    gtk_label_set_xalign (GTK_LABEL (widget), 1.0);
    gtk_label_set_yalign (GTK_LABEL (widget), 0.5);
#else
    gtk_misc_set_alignment (GTK_MISC (widget), 1.0, 0.5);
#endif
    gtk_table_attach (table, widget, 1, 2, 1, 2,
                      GTK_FILL, GTK_FILL,
                      0, 0);

    interval = gtk_spin_button_new_with_range (1.0, 600.0, 1.0);
    gtk_table_attach (table, interval, 2, 3, 1, 2,
                      GTK_EXPAND | GTK_FILL | GTK_SHRINK, GTK_FILL,
                      0, 0);

    widget = gtk_label_new (_("Maximum width (chars):"));
#if GTK_CHECK_VERSION (3, 16, 0)
    gtk_label_set_xalign (GTK_LABEL (widget), 1.0);
    gtk_label_set_yalign (GTK_LABEL (widget), 0.5);
#else
    gtk_misc_set_alignment (GTK_MISC (widget), 1.0, 0.5);
#endif
    gtk_table_attach (table, widget, 1, 2, 2, 3,
                      GTK_FILL, GTK_FILL,
                      0, 0);

    width = gtk_spin_button_new_with_range(1.0, 100.0, 1.0);
    gtk_table_attach (table, width, 2, 3, 2, 3,
                      GTK_EXPAND | GTK_FILL | GTK_SHRINK, GTK_FILL,
                      0, 0);

    showicon = gtk_check_button_new_with_label (_("Show icon"));
    gtk_table_attach (table, showicon, 2, 3, 3, 4,
                      GTK_EXPAND | GTK_FILL | GTK_SHRINK, GTK_FILL,
                      0, 0);

    gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (dialog)), GTK_WIDGET (table), TRUE, TRUE, 0);

    g_signal_connect (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);

    /* use g_settings_bind to manage settings */
    g_settings_bind (command_applet->settings, COMMAND_KEY, command, "text", G_SETTINGS_BIND_DEFAULT);
    g_settings_bind (command_applet->settings, INTERVAL_KEY, interval, "value", G_SETTINGS_BIND_DEFAULT);
    g_settings_bind (command_applet->settings, WIDTH_KEY, width, "value", G_SETTINGS_BIND_DEFAULT);
    g_settings_bind (command_applet->settings, SHOW_ICON_KEY, showicon, "active", G_SETTINGS_BIND_DEFAULT);

    gtk_widget_show_all (GTK_WIDGET (dialog));
}

/* GSettings signal callbacks */
static void
settings_command_changed (GSettings *settings, gchar *key, CommandApplet *command_applet)
{
    gchar *command;

    command = g_settings_get_string (command_applet->settings, COMMAND_KEY);

    if (command_applet->command)
        g_free (command_applet->command);

    if (command != NULL && command[0] != 0)
        command_applet->command = command;
    else
        command_applet->command = g_strdup ("");
}

static void
settings_width_changed (GSettings *settings, gchar *key, CommandApplet *command_applet)
{
    gint width;

    width = g_settings_get_int (command_applet->settings, WIDTH_KEY);

    command_applet->width = width;

    /* execute command to start new timer */
    command_execute (command_applet);
}

static void
settings_interval_changed (GSettings *settings, gchar *key, CommandApplet *command_applet)
{
    gint interval;

    interval = g_settings_get_int (command_applet->settings, INTERVAL_KEY);

    /* minimum interval */
    if (interval < 1)
        interval = 1;

    command_applet->interval = interval;

    /* stop current timer */
    if (command_applet->timeout_id != 0)
    {
        g_source_remove (command_applet->timeout_id);
        command_applet->timeout_id = 0;
    }

    /* execute command to start new timer */
    command_execute (command_applet);
}

static gboolean
command_execute (CommandApplet *command_applet)
{
    GError *error = NULL;
    gchar *output = NULL;
    gint ret = 0;

    if (g_spawn_command_line_sync (command_applet->command, &output, NULL, &ret, &error))
    {
        gtk_widget_set_tooltip_text (GTK_WIDGET (command_applet->label), command_applet->command);

        if ((output != NULL) && (output[0] != 0))
        {
            /* check if output is a custom GKeyFile */
            if (g_str_has_prefix (output, "[Command]"))
            {
                GKeyFile *file = g_key_file_new ();
                if (g_key_file_load_from_data (file, output, -1, G_KEY_FILE_NONE, NULL))
                {
                    gchar *goutput = g_key_file_get_string (file, GK_COMMAND_GROUP, GK_COMMAND_OUTPUT, NULL);
                    gchar *icon = g_key_file_get_string (file, GK_COMMAND_GROUP, GK_COMMAND_ICON, NULL);

                    if (goutput)
                    {
                        gtk_label_set_use_markup (command_applet->label, TRUE);
                        gtk_label_set_markup (command_applet->label, goutput);
                    }
                    if (icon)
                        gtk_image_set_from_icon_name (command_applet->image, icon, 24);

                    g_free (goutput);
                    g_free (icon);
                }
                else
                    gtk_label_set_text (command_applet->label, ERROR_OUTPUT);
                g_key_file_free (file);
            }
            else
            {
                /* check output length */
                if (strlen(output) > command_applet->width)
                {
                    GString *strip_output;
                    strip_output = g_string_new_len (output, command_applet->width);
                    g_free (output);
                    output = strip_output->str;
                    g_string_free (strip_output, FALSE);
                }
                /* remove last char if it is '\n' to avoid aligment problems */
                if (g_str_has_suffix (output, "\n"))
                {
                    output[strlen(output) - 1] = 0;
                }

                gtk_label_set_text (command_applet->label, output);
            }
        }
        else
            gtk_label_set_text (command_applet->label, ERROR_OUTPUT);
    }
    else
        gtk_label_set_text (command_applet->label, ERROR_OUTPUT);

    g_free (output);

    /* start timer for next execution */
    command_applet->timeout_id = g_timeout_add_seconds (command_applet->interval,
                                                        (GSourceFunc) command_execute,
                                                        command_applet);

    return FALSE;
}

static gboolean
command_applet_fill (Gde2PanelApplet* applet)
{
    CommandApplet *command_applet;

    g_set_application_name (_("Command Applet"));
    gtk_window_set_default_icon_name (APPLET_ICON);

    gde2_panel_applet_set_flags (applet, GDE2_PANEL_APPLET_EXPAND_MINOR);
    gde2_panel_applet_set_background_widget (applet, GTK_WIDGET (applet));

    command_applet = g_malloc0(sizeof(CommandApplet));
    command_applet->applet = applet;
    command_applet->settings = gde2_panel_applet_settings_new (applet, COMMAND_SCHEMA);

    command_applet->interval = g_settings_get_int (command_applet->settings, INTERVAL_KEY);
    command_applet->command = g_settings_get_string (command_applet->settings, COMMAND_KEY);
    command_applet->width = g_settings_get_int (command_applet->settings, WIDTH_KEY);

    command_applet->box = GTK_BOX (gtk_hbox_new (FALSE, 0));
    command_applet->image = GTK_IMAGE (gtk_image_new_from_icon_name (APPLET_ICON, 24));
    command_applet->label = GTK_LABEL (gtk_label_new (ERROR_OUTPUT));
    command_applet->timeout_id = 0;

    /* we add the Gtk label into the applet */
    gtk_box_pack_start (command_applet->box,
                        GTK_WIDGET (command_applet->image),
                        TRUE, TRUE, 0);
    gtk_box_pack_start (command_applet->box,
                        GTK_WIDGET (command_applet->label),
                        TRUE, TRUE, 0);

    gtk_container_add (GTK_CONTAINER (applet),
                       GTK_WIDGET (command_applet->box));

    gtk_widget_show_all (GTK_WIDGET (command_applet->applet));

    g_signal_connect(G_OBJECT (command_applet->applet), "destroy",
                     G_CALLBACK (command_applet_destroy),
                     command_applet);

    /* GSettings signals */
    g_signal_connect(command_applet->settings,
                     "changed::" COMMAND_KEY,
                     G_CALLBACK (settings_command_changed),
                     command_applet);
    g_signal_connect(command_applet->settings,
                     "changed::" INTERVAL_KEY,
                     G_CALLBACK (settings_interval_changed),
                     command_applet);
    g_signal_connect(command_applet->settings,
                     "changed::" WIDTH_KEY,
                     G_CALLBACK (settings_width_changed),
                     command_applet);
    g_settings_bind (command_applet->settings,
                     SHOW_ICON_KEY,
                     command_applet->image,
                     "visible",
                     G_SETTINGS_BIND_DEFAULT);

    /* set up context menu */
    GtkActionGroup *action_group = gtk_action_group_new ("Command Applet Actions");
    gtk_action_group_set_translation_domain (action_group, GETTEXT_PACKAGE);
    gtk_action_group_add_actions (action_group, applet_menu_actions,
                                  G_N_ELEMENTS (applet_menu_actions), command_applet);
    gde2_panel_applet_setup_menu (command_applet->applet, ui, action_group);

    /* first command execution */
    command_execute (command_applet);

    return TRUE;
}

/* this function, called by gde2-panel, will create the applet */
static gboolean
command_factory (Gde2PanelApplet* applet, const char* iid, gpointer data)
{
    gboolean retval = FALSE;

    if (!g_strcmp0 (iid, "CommandApplet"))
        retval = command_applet_fill (applet);

    return retval;
}

/* needed by gde2-panel applet library */
GDE2_PANEL_APPLET_OUT_PROCESS_FACTORY("CommandAppletFactory",
                                      PANEL_TYPE_APPLET,
                                      "Command applet",
                                      command_factory,
                                      NULL)
