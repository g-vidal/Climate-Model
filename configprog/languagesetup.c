#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

//#include "callbacks.h"
//#include "interface.h"
//#include "support.h"
#include "stdio.h"

GtkWidget *dialog1;
GtkWidget *langdef;
GtkWidget *langfr;
GtkWidget *langen;


void on_ok(GtkButton *button, gpointer user_data)
{
    FILE* cnf = fopen("climat.ini","w");
    fprintf(cnf,"# Veuillez indiquer ici vos préférences pour la langue\n");
    fprintf(cnf,"# Langue par défaut: lang=\n");
    fprintf(cnf,"# Anglais: lang=en\n");
    fprintf(cnf,"# Français: lang=fr\n");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(langfr)))
    	fprintf(cnf,"lang=fr\n");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(langen)))
    	fprintf(cnf,"lang=en\n");
    else
    	fprintf(cnf,"lang=\n");
    fclose(cnf);
    gtk_main_quit();
}


int main (int argc, char * argv[])
{
    GtkWidget *dialog1;

    gtk_set_locale ();
    gtk_init (&argc, &argv);


    GtkWidget *dialog_vbox1;
    GtkWidget *vbox1;
    GtkWidget *label1;
    GtkWidget *vbox2;
    GSList *langdef_group = NULL;
    GtkWidget *dialog_action_area1;
    GtkWidget *button1;
    GtkWidget *button2;

    dialog1 = gtk_dialog_new ();
    gtk_container_set_border_width (GTK_CONTAINER (dialog1), 8);
    gtk_window_set_title (GTK_WINDOW (dialog1), ("Simclimat Configuration"));
    gtk_window_set_position (GTK_WINDOW (dialog1), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_icon_name (GTK_WINDOW (dialog1), "gtk-execute");
    gtk_window_set_type_hint (GTK_WINDOW (dialog1), GDK_WINDOW_TYPE_HINT_DIALOG);
    gtk_dialog_set_has_separator (GTK_DIALOG (dialog1), FALSE);

    dialog_vbox1 = GTK_DIALOG (dialog1)->vbox;
    gtk_widget_show (dialog_vbox1);

    vbox1 = gtk_vbox_new (FALSE, 0);
    gtk_widget_show (vbox1);
    gtk_box_pack_start (GTK_BOX (dialog_vbox1), vbox1, TRUE, TRUE, 0);

    label1 = gtk_label_new (("Simclimat Language settings"));
    gtk_widget_show (label1);
    gtk_box_pack_start (GTK_BOX (vbox1), label1, FALSE, FALSE, 0);
    gtk_label_set_justify (GTK_LABEL (label1), GTK_JUSTIFY_CENTER);

    vbox2 = gtk_vbox_new (FALSE, 0);
    gtk_widget_show (vbox2);
    gtk_box_pack_start (GTK_BOX (vbox1), vbox2, TRUE, FALSE, 0);

    langdef = gtk_radio_button_new_with_mnemonic (NULL, ("System default"));
    gtk_widget_show (langdef);
    gtk_box_pack_start (GTK_BOX (vbox2), langdef, TRUE, TRUE, 0);
    gtk_radio_button_set_group (GTK_RADIO_BUTTON (langdef), langdef_group);
    langdef_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (langdef));
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (langdef), TRUE);

    langfr = gtk_radio_button_new_with_mnemonic (NULL, ("French"));
    gtk_widget_show (langfr);
    gtk_box_pack_start (GTK_BOX (vbox2), langfr, TRUE, TRUE, 0);
    gtk_radio_button_set_group (GTK_RADIO_BUTTON (langfr), langdef_group);
    langdef_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (langfr));
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (langfr), TRUE);

    langen = gtk_radio_button_new_with_mnemonic (NULL, ("English"));
    gtk_widget_show (langen);
    gtk_box_pack_start (GTK_BOX (vbox2), langen, TRUE, TRUE, 0);
    gtk_radio_button_set_group (GTK_RADIO_BUTTON (langen), langdef_group);
    langdef_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (langen));
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (langen), TRUE);

    dialog_action_area1 = GTK_DIALOG (dialog1)->action_area;
    gtk_widget_show (dialog_action_area1);
    gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

    button1 = gtk_button_new_from_stock ("gtk-ok");
    gtk_widget_show (button1);
    gtk_dialog_add_action_widget (GTK_DIALOG (dialog1), button1, 0);

    button2 = gtk_button_new_from_stock ("gtk-cancel");
    gtk_widget_show (button2);
    gtk_dialog_add_action_widget (GTK_DIALOG (dialog1), button2, 1);

    g_signal_connect ((gpointer) button1, "clicked",
	    G_CALLBACK (on_ok),
	    NULL);
    g_signal_connect ((gpointer) button2, "clicked",
	    G_CALLBACK (gtk_main_quit),
	    NULL);

    gtk_widget_show (dialog1);

    gtk_main ();

    execl("./climat.exe",0x0);
    return 0;
}


