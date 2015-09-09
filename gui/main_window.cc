// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "main_window.hh"
#include <gtkmm/comboboxtext.h>
#include <globals.h>
#include "climat.hh"
#define ev experience_values
#define mocst modele_constants

static void initialize_graphe_combobox(Gtk::ComboBoxText& cbb)
{
    cbb.append_text(mocst.graph_type_title(TEMPERATURE));
    cbb.append_text(mocst.graph_type_title(WATERLEVEL));
    cbb.append_text(mocst.graph_type_title(CALOTTESLEVEL));
    cbb.append_text(mocst.graph_type_title(CONCENTRATION_CO2));
    cbb.append_text(mocst.graph_type_title(EMISSIONS_CO2));
    cbb.append_text(mocst.graph_type_title(ALBEDO));
}

main_window::main_window()
{
    initialize_graphe_combobox(*this->graphe_one_combobox);
    initialize_graphe_combobox(*this->graphe_two_combobox);  
    initialize_graphe_combobox(*this->graphe_three_combobox);  
    initialize_graphe_combobox(*this->graphe_four_combobox);  
    graphe_one_combobox->set_active(mocst.graphe_one_init); 
    graphe_two_combobox->set_active(mocst.graphe_two_init); 
    graphe_three_combobox->set_active(mocst.graphe_three_init); 
    graphe_four_combobox->set_active(mocst.graphe_four_init);
}

void main_window::on_new1_activate()
{  
   on_nouvelle_simulation_button_clicked(); 
}

void main_window::on_superposer_menuitem_activate()
{  
    on_superposer_button_clicked();
}

void main_window::on_save1_activate()
{  
    on_enregistrer_etat_final_button_clicked();
}

void main_window::on_quit1_activate()
{  
    exit(0);
}

void main_window::on_animations_menuitem_activate()
{  
    if (animations_menuitem->get_active())
    {
	niveau_mer_drawingarea->enable_animations();
	calotte_drawingarea->enable_animations();
    }
    else
    {
	niveau_mer_drawingarea->disable_animations();
	calotte_drawingarea->disable_animations();
    }
}

void main_window::on_about1_activate()
{
    climat_interface.aboutdialog->run();
    climat_interface.aboutdialog->hide();
}

void main_window::on_nouvelle_simulation_button_clicked()
{
    climat_interface.choix_etat_initial_dialog
	->etat_initial_precedent_radiobutton
	->set_sensitive(ev.nb_simulations()>0);
    climat_interface.choix_etat_initial_dialog->show();
}

void main_window::on_superposer_button_clicked()
{ 
    ev.push_back_simulation();
    climat_interface.choix_des_parametres_dialog->read_from_SimulationValues();
    time_slider_hscale->set_value(0);
    time_slider_hscale->set_sensitive(false);
    climat_interface.choix_des_parametres_dialog->show();
}

void main_window::on_enregistrer_etat_final_button_clicked()
{  
    Gtk::ComboBoxText& cbt = 
	*climat_interface.enregister_etat_final_dialog->
	enregistrer_choix_simulation_combobox;
    cbt.clear_items();
    for (int i=0;i<ev.nb_simulations();i++)
	cbt.append_text(ev.get_simulation(i).nom_simulation);
    cbt.set_active(ev.nb_simulations()-1);
    climat_interface.enregister_etat_final_dialog->show();
}

void main_window::on_time_slider_hscale_value_changed()
{  
    double value = time_slider_hscale->get_value();
    climat_interface.indice_courant=static_cast<int>(value);
    redraw_all();
}

void main_window::on_graphe_two_combobox_changed()
{  
    ev.set_graph_displayed(2,graphe_two_combobox->get_active_row_number());
    graphe_two_drawingarea->recompile();
    //graphe_two_drawingarea->queue_draw();
}

void main_window::on_graphe_three_combobox_changed()
{  
    ev.set_graph_displayed(3,graphe_three_combobox->get_active_row_number());
    graphe_three_drawingarea->recompile();
    //graphe_three_drawingarea->queue_draw();
}

void main_window::on_graphe_one_combobox_changed()
{  
    ev.set_graph_displayed(1,graphe_one_combobox->get_active_row_number());
    graphe_one_drawingarea->recompile();
    //graphe_one_drawingarea->queue_draw();
}

void main_window::on_graphe_four_combobox_changed()
{  
    ev.set_graph_displayed(4,graphe_four_combobox->get_active_row_number());
    graphe_four_drawingarea->recompile();
    //graphe_four_drawingarea->queue_draw();
}

void main_window::redraw_all()
{
    graphe_one_drawingarea->redraw();
    graphe_two_drawingarea->redraw();
    graphe_three_drawingarea->redraw();
    graphe_four_drawingarea->redraw();
    niveau_mer_drawingarea->redraw();
    calotte_drawingarea->redraw();
}    

void main_window::recompile_all()
{
    graphe_one_drawingarea->recompile();
    graphe_two_drawingarea->recompile();
    graphe_three_drawingarea->recompile();
    graphe_four_drawingarea->recompile();
    niveau_mer_drawingarea->redraw();
    calotte_drawingarea->redraw();
}    
