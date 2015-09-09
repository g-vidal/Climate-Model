// using glademm V2.6.0
//
// newer (non customized) versions of this file go to enregister_etat_final_dialog.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "enregister_etat_final_dialog.hh"
#include <string>
#include <globals.h>
#define ev experience_values

void enregister_etat_final_dialog::on_cancelbutton8_clicked()
{  
    this->hide();
}

void enregister_etat_final_dialog::on_okbutton8_clicked()
{  
    this->hide();
    int id = enregistrer_choix_simulation_combobox->get_active_row_number();
    std::string fichier = 
	enregistrer_etat_final_filechooserwidget->get_filename();
    ev.enregistre_etat_final(fichier,id);
}

void enregister_etat_final_dialog::on_enregistrer_choix_simulation_combobox_changed()
{  
}
