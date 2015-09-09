// using glademm V2.6.0
//
// newer (non customized) versions of this file go to choix_etat_initial_dialog.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "climat.hh"
#include "choix_etat_initial_dialog.hh"
#include <globals.h>

#define ev experience_values
#define mocst modele_constants
void choix_etat_initial_dialog::on_cancelbutton7_clicked()
{
    this->hide();
}

void choix_etat_initial_dialog::on_okbutton7_clicked()
{
    double echeance = spinbutton1->get_value();
    this->hide();
    climat_interface.indice_courant=0;
    climat_interface.main_window->time_slider_hscale->set_value(0.);
    climat_interface.main_window->time_slider_hscale->set_sensitive(false);
    if (two007_radiobutton->get_active())
	ev.set_etat_initial(create_etat_2007(),echeance);
    else if (etat_initial_1750_radiobutton->get_active())
	ev.set_etat_initial(create_etat_1750(),echeance);
    else if (etat_initial_precedent_radiobutton->get_active())
	ev.set_etat_initial(ev.back(),echeance);
    else //if (etat_initial_autre_radiobutton->get_active())
    {
	//TODO: fichier inexistant
	std::string flnm = filechooserbutton1->get_filename();
	ev.set_etat_initial(flnm,echeance);
    }

    climat_interface.main_window->recompile_all();
    climat_interface.main_window->show_choix_params_dialog();
}

void choix_etat_initial_dialog::on_2007_radiobutton_toggled()
{ 
}

void choix_etat_initial_dialog::on_etat_initial_1750_radiobutton_toggled()
{  
}

void choix_etat_initial_dialog::on_etat_initial_precedent_radiobutton_toggled()
{  
}

void choix_etat_initial_dialog::on_etat_initial_autre_radiobutton_toggled()
{  
}

void choix_etat_initial_dialog::on_filechooserbutton1_file_activated()
{
    etat_initial_autre_radiobutton->set_active();
}

void choix_etat_initial_dialog::on_spinbutton1_value_changed()
{  
}

choix_etat_initial_dialog::choix_etat_initial_dialog()
{
	spinbutton1->set_range(mocst.echeance_min,mocst.echeance_max);
	spinbutton1->set_increments(10,100);
	spinbutton1->set_value(mocst.echeance_reset_value);
}

