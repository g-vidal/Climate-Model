// using glademm V2.6.0
//
// newer (non customized) versions of this file go to choix_des_parametres_dialog.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "choix_des_parametres_dialog.hh"
//----------------LINK to kernel----------------
#include <globals.h>
#include <cmath>
#include "climat.hh"
#include <glibmm/ustring.h>
using namespace std;
using Glib::ustring;
#define ev experience_values
#define mocst modele_constants


void choix_des_parametres_dialog::on_cancelbutton8_clicked()
{ 
   //TODO pop back
   this->hide(); 
   ev.pop_back_simulation();
   if (ev.nb_simulations()>0)
   {
       class main_window* mw = climat_interface.main_window;
       mw->recompile_all();
       mw->time_slider_hscale->set_sensitive(true);
   }
}

static ustring legende_color(int i)
{
    switch(i)
    {
	case 0:
	    return "<span foreground=\"#FF0000\" weight=\"heavy\" strikethrough=\"true\">";
	case 1:
	    return "<span foreground=\"#00FF00\" weight=\"heavy\" strikethrough=\"true\">";
	case 2:
	    return "<span foreground=\"#0000FF\" weight=\"heavy\" strikethrough=\"true\">";
	case 3:
	    return "<span foreground=\"#FFFF00\" weight=\"heavy\" strikethrough=\"true\">";
	case 4:
	    return "<span foreground=\"#FF00FF\" weight=\"heavy\" strikethrough=\"true\">";
	case 5:
	    return "<span foreground=\"#00FFFF\" weight=\"heavy\" strikethrough=\"true\">";
	case 6:
	    return "<span foreground=\"#880000\" weight=\"heavy\" strikethrough=\"true\">";
	case 7:
	    return "<span foreground=\"#008800\" weight=\"heavy\" strikethrough=\"true\">";
	case 8:
	    return "<span foreground=\"#000088\" weight=\"heavy\" strikethrough=\"true\">";
	case 9:
	    return "<span foreground=\"#888800\" weight=\"heavy\" strikethrough=\"true\">";
	case 10:
	    return "<span foreground=\"#880088\" weight=\"heavy\" strikethrough=\"true\">";
    }
    return "<span foreground=\"#880088\">";
}
void choix_des_parametres_dialog::on_choix_parametres_okbutton_clicked()
{ 
    //TODO
    this->hide();
    store_to_SimulationValues();
    modele_execute();
    class main_window* mw = climat_interface.main_window;
    mw->recompile_all();
    mw->time_slider_hscale->set_value(100.);
    mw->time_slider_hscale->set_sensitive(true);
    ustring lgnd;
    for (int i=0;i<ev.nb_simulations();i++)
	lgnd += legende_color(i) 
	    + "----</span>   "
	    + ev.get_simulation(i).nom_simulation
	    + "\n";

    mw->legende_texte_label->set_markup(lgnd);
}

void choix_des_parametres_dialog::on_dist_terre_sol_actuel_radiobutton_toggled()
{
    if (!dist_terre_sol_actuel_radiobutton->get_active())  return;
    distance_terre_soleil_spinbutton->set_value(mocst.distance_ts_actuel);
    distance_terre_soleil_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_dist_terre_sol_other_radiobutton_toggled()
{
    if (!dist_terre_sol_other_radiobutton->get_active()) return;
    distance_terre_soleil_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_distance_terre_soleil_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_puissance_solaire_actuel_radiobutton_toggled()
{ 
    if (!puissance_solaire_actuel_radiobutton->get_active()) return;
    puissance_solaire_spinbutton->set_value(mocst.puissance_soleil_actuel);
    puissance_solaire_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_puissance_solaire_creation_radiobutton_toggled()
{  
    if (!puissance_solaire_creation_radiobutton->get_active()) return;
    puissance_solaire_spinbutton->set_value(mocst.puissance_soleil_terre_init);
    puissance_solaire_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_puissance_solaire_other_radiobutton_toggled()
{  
    if (!puissance_solaire_other_radiobutton->get_active()) return;
    puissance_solaire_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_puissance_solaire_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_excentricite_actuel_radiobutton_toggled()
{
    if (!excentricite_actuel_radiobutton->get_active()) return;
    excentricite_spinbutton->set_value(mocst.excentricite_act);
    excentricite_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_excentricite_min_radiobutton_toggled()
{
    if (!excentricite_min_radiobutton->get_active()) return;
    excentricite_spinbutton->set_value(mocst.excentricite_valeur_min);
    excentricite_spinbutton->set_sensitive(false);

}

void choix_des_parametres_dialog::on_excentricite_max_radiobutton_toggled()
{
    if (!excentricite_max_radiobutton->get_active()) return;
    excentricite_spinbutton->set_value(mocst.excentricite_valeur_max);
    excentricite_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_excenticite_other_radiobutton_toggled()
{  
    if (!excenticite_other_radiobutton->get_active()) return;
    excentricite_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_excentricite_spinbutton_editing_done()
{  
}

void choix_des_parametres_dialog::on_obliquite_actuel_radiobutton_toggled()
{  
    if (!obliquite_actuel_radiobutton->get_active()) return;
    obliquite_spinbutton->set_value(mocst.obliquite_act);
    obliquite_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_obliquite_min_radiobutton_toggled()
{  
    if (!obliquite_min_radiobutton->get_active()) return;
    obliquite_spinbutton->set_value(mocst.obliquite_valeur_min);
    obliquite_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_obliquite_max_radiobutton_toggled()
{  
    if (!obliquite_max_radiobutton->get_active()) return;
    obliquite_spinbutton->set_value(mocst.obliquite_valeur_max);
    obliquite_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_obliquite_other_radiobutton_toggled()
{  
    if (!obliquite_other_radiobutton->get_active()) return;
    obliquite_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_obliquite_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_precession_actuel_radiobutton_toggled()
{  
    if (!precession_actuel_radiobutton->get_active()) return;
    precession_spinbutton->set_value(mocst.precession_act);
    precession_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_precession_min_radiobutton_toggled()
{  
    if (!precession_min_radiobutton->get_active()) return;
    precession_spinbutton->set_value(mocst.precession_valeur_min);
    precession_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_precession_max_radiobutton_toggled()
{  
    if (!precession_max_radiobutton->get_active()) return;
    precession_spinbutton->set_value(mocst.precession_valeur_max);
    precession_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_precession_autre_radiobutton_toggled()
{  
    if (!precession_autre_radiobutton->get_active()) return;
    precession_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_precession_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_simulation_type_concentration_radiobutton_toggled()
{  
    if (!simulation_type_concentration_radiobutton->get_active()) return;
    emissions_vbox->hide();
    concentration_vbox->show();
}

void choix_des_parametres_dialog::on_simulation_type_emission_radiobutton_toggled()
{  
    if (!simulation_type_emission_radiobutton->get_active()) return;
    concentration_vbox->hide();
    emissions_vbox->show();
}

void choix_des_parametres_dialog::on_concentration_actuel_radiobutton_toggled()
{  
    if (!concentration_actuel_radiobutton->get_active()) return;
    concentration_autre_spinbutton->set_value(mocst.coo_concentr_today);
    concentration_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_concentration_1750_radiobutton_toggled()
{  
    if (!concentration_1750_radiobutton->get_active()) return;
    concentration_autre_spinbutton->set_value(mocst.coo_concentr_1750);
    concentration_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_concentration_cretace_radiobutton_toggled()
{  
    if (!concentration_cretace_radiobutton->get_active()) return;
    concentration_autre_spinbutton->set_value(mocst.coo_concentr_cretace);
    concentration_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_concentration_terreinitiale_radiobutton_toggled()
{  
    if (!concentration_terreinitiale_radiobutton->get_active()) return;
    concentration_autre_spinbutton->set_value(mocst.coo_concentr_terre_initiale);
    concentration_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_concentration_autre_radiobutton_toggled()
{  
    if (!concentration_autre_radiobutton->get_active()) return;
    concentration_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_concentration_autre_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_emissions_anthro_nulles_radiobutton_toggled()
{  
    if (!emissions_anthro_nulles_radiobutton->get_active()) return;
    emissions_anthro_autre_spinbutton->set_value(mocst.emit_anthro_coo_nul);
    emissions_anthro_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_emissions_anthro_actuel_radiobutton_toggled()
{  
    if (!emissions_anthro_actuel_radiobutton->get_active()) return;
    emissions_anthro_autre_spinbutton->set_value(mocst.emit_anthro_coo_actuel);
    emissions_anthro_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_emissions_anthro_double_radiobutton_toggled()
{  
    if (!emissions_anthro_double_radiobutton->get_active()) return;
    emissions_anthro_autre_spinbutton->set_value(mocst.emit_anthro_coo_2xactuel);
    emissions_anthro_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_emissions_anthro_autres_radiobutton_toggled()
{  
    if (!emissions_anthro_autres_radiobutton->get_active()) return;
    emissions_anthro_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_emissions_anthro_autre_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_volcanisme_actuel_radiobutton_toggled()
{  
    if (!volcanisme_actuel_radiobutton->get_active()) return;
    volcanisme_autre_spinbutton->set_value(mocst.volcan_actuel);
    volcanisme_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_radiobutton28_toggled()
{  
    if (!volcanisme_terre_init_radiobutton->get_active()) return;
    volcanisme_autre_spinbutton->set_value(mocst.volcan_terre_init);
    volcanisme_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_volcanisme_autre_radiobutton_toggled()
{  
    if (!volcanisme_autre_radiobutton->get_active()) return;
    volcanisme_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_volcanisme_autre_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_alteration_actuel_radiobutton_toggled()
{  
    if (!alteration_actuel_radiobutton->get_active()) return;
    alteration_autre_spinbutton->set_value(mocst.alteration_actuel);
    alteration_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_alteration_autre_radiobutton_toggled()
{  
    if (!alteration_autre_radiobutton->get_active()) return;
    alteration_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_spinbutton10_value_changed()
{  
}

void choix_des_parametres_dialog::on_stockahe_nul_radiobutton_toggled()
{  
    if (!stockahe_nul_radiobutton->get_active()) return;
    stockage_autre_spinbutton->set_value(0.);
    stockage_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_stockage_carbonifere_radiobutton_toggled()
{  
    if (!stockage_carbonifere_radiobutton->get_active()) return;
    stockage_autre_spinbutton->set_value(mocst.stockage_biologique_carbonifere);
    stockage_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_stockage_autre_radiobutton_toggled()
{  
    if (!stockage_autre_radiobutton->get_active()) return;
    stockage_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_stockage_autre_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_retroaction_albedo_off_radiobutton_toggled()
{  
    if (!retroaction_albedo_off_radiobutton->get_active()) return;
    albedo_actuel_radiobutton->set_sensitive(true);
    albedo_glace_radiobutton->set_sensitive(true);
    albedo_terre_radiobutton->set_sensitive(true);
    albedo_autre_radiobutton->set_sensitive(true);
    albedo_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_albedo_actuel_radiobutton_toggled()
{  
    if (!albedo_actuel_radiobutton->get_active()) return;
    albedo_autre_spinbutton->set_value(mocst.albedo_act);
    albedo_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_albedo_glace_radiobutton_toggled()
{  
    if (!albedo_glace_radiobutton->get_active()) return;
    albedo_autre_spinbutton->set_value(mocst.albedo_glace);
    albedo_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_albedo_terre_radiobutton_toggled()
{  
    if (!albedo_terre_radiobutton->get_active()) return;
    albedo_autre_spinbutton->set_value(mocst.albedo_terre);
    albedo_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_albedo_autre_radiobutton_toggled()
{  
    if (!albedo_autre_radiobutton->get_active()) return;
    albedo_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_albedo_autre_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_retroaction_albedo_on_radiobutton_toggled()
{  
    if (!retroaction_albedo_on_radiobutton->get_active()) return;
    albedo_actuel_radiobutton->set_sensitive(false);
    albedo_glace_radiobutton->set_sensitive(false);
    albedo_terre_radiobutton->set_sensitive(false);
    albedo_autre_radiobutton->set_sensitive(false);
    albedo_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_retroaction_ocean_off_radiobutton_toggled()
{  
    //if (!->get_active()) return;
    //TODO
}

void choix_des_parametres_dialog::on_retroaction_ocean_fix_radiobutton_toggled()
{  
    //if (!->get_active()) return;
    //TODO
}

void choix_des_parametres_dialog::on_retroaction_ocean_fix_regler_actuel_radiobutton_toggled()
{  
    if (!retroaction_ocean_fix_regler_actuel_radiobutton->get_active()) return;
    retroaction_ocean_fix_autre_spinbutton->set_value(mocst.puit_ocean_actuel);
    retroaction_ocean_fix_autre_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_retroaction_ocean_fix_autre_radiobutton_toggled()
{  
    if (!retroaction_ocean_fix_autre_radiobutton->get_active()) return;
    retroaction_ocean_fix_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_retroaction_ocean_fix_autre_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_retroaction_ocean_on_radiobutton_toggled()
{  
    //if (!->get_active()) return;
    //TODO
}

void choix_des_parametres_dialog::on_retroaction_vegetation_off_radiobutton_toggled()
{  
    if (!retroaction_vegetation_off_radiobutton->get_active()) return;
    retroaction_vegetation_on_actuel_radiobutton->set_sensitive(false);
    retroaction_vegetation_on_autre_radiobutton->set_sensitive(false);
    retroaction_vegetation_fix_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_retroaction_vegetation_on_radiobutton_toggled()
{  
    if (!retroaction_vegetation_on_radiobutton->get_active()) return;
    retroaction_vegetation_on_actuel_radiobutton->set_sensitive(true);
    retroaction_vegetation_on_autre_radiobutton->set_sensitive(true);
    retroaction_vegetation_fix_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_retroaction_vegetation_on_actuel_radiobutton_toggled()
{  
    if (!retroaction_vegetation_on_actuel_radiobutton->get_active()) return;
    retroaction_vegetation_fix_spinbutton->set_value(mocst.puit_bio_actuel);
    retroaction_vegetation_fix_spinbutton->set_sensitive(false);
}

void choix_des_parametres_dialog::on_retroaction_vegetation_on_autre_radiobutton_toggled()
{  
    if (!retroaction_vegetation_on_autre_radiobutton->get_active()) return;
    retroaction_vegetation_fix_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_retroaction_vegetation_fix_spinbutton_value_changed()
{  
}

void choix_des_parametres_dialog::on_retroaction_vapeur_off_radiobutton_toggled()
{  
    if (!retroaction_vapeur_off_radiobutton->get_active()) return;
    retroaction_vapeur_on_actuel_radiobutton->set_sensitive(true);
    retroaction_vapeur_on_autre_radiobutton->set_sensitive(true);
    retroaction_vapeur_on_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_retroaction_vapeur_on_actuel_radiobutton_toggled()
{  
    if (!retroaction_vapeur_on_actuel_radiobutton->get_active()) return;
    retroaction_vapeur_on_autre_spinbutton->set_value(mocst.rapport_H2O_actuel);
    retroaction_vapeur_on_autre_spinbutton->set_sensitive(false);

}

void choix_des_parametres_dialog::on_retroaction_vapeur_on_autre_radiobutton_toggled()
{  
    if (!retroaction_vapeur_on_autre_radiobutton->get_active()) return;
    retroaction_vapeur_on_autre_spinbutton->set_sensitive(true);
}

void choix_des_parametres_dialog::on_spinbutton11_value_changed()
{  
}

void choix_des_parametres_dialog::on_retroaction_vapeur_on_radiobutton_toggled()
{  
    if (!retroaction_vapeur_on_radiobutton->get_active()) return;
    retroaction_vapeur_on_actuel_radiobutton->set_sensitive(false);
    retroaction_vapeur_on_autre_radiobutton->set_sensitive(false);
    retroaction_vapeur_on_autre_spinbutton->set_sensitive(false);
}

static void set_spinbutton_range(Gtk::SpinButton& s,double vmin,double vmax)
{
    double interval = vmax-vmin;
    double pwr = ceil(log(interval)/M_LN10);
    int nb_digits = 4-static_cast<int>(pwr);
    if (nb_digits<0) nb_digits=0;
    s.set_range(vmin,vmax);
    s.set_digits(nb_digits);
    s.set_increments(interval/500.,interval/50.);
}

choix_des_parametres_dialog::choix_des_parametres_dialog()
{
    //concentration_dialog
    set_spinbutton_range(*concentration_autre_spinbutton,
	    mocst.coo_concentr_min,mocst.coo_concentr_max);

    //emission_dialog
    set_spinbutton_range(*emissions_anthro_autre_spinbutton,
	    mocst.emit_anthro_coo_min,mocst.emit_anthro_coo_max);
    set_spinbutton_range(*volcanisme_autre_spinbutton,
	    mocst.volcan_min,mocst.volcan_max);
    set_spinbutton_range(*alteration_autre_spinbutton,
	    mocst.alteration_min,mocst.alteration_max);
    set_spinbutton_range(*stockage_autre_spinbutton,
	    mocst.stockage_biologique_min,mocst.stockage_biologique_max); 

    //parametres_astronomiques_dialog
    set_spinbutton_range(*distance_terre_soleil_spinbutton,
	    mocst.distance_ts_min,mocst.distance_ts_max);
    set_spinbutton_range(*puissance_solaire_spinbutton,
	    mocst.puissance_soleil_min,mocst.puissance_soleil_max);
    set_spinbutton_range(*precession_spinbutton,
	    mocst.precession_autre_min,mocst.precession_autre_max);
    set_spinbutton_range(*excentricite_spinbutton,
	    mocst.excentricite_autre_min,mocst.excentricite_autre_max);
    set_spinbutton_range(*obliquite_spinbutton,
	    mocst.obliquite_autre_min,mocst.obliquite_autre_max);

    // retroactions_dialog
    // 1)albedo
    set_spinbutton_range(*albedo_autre_spinbutton,
	    mocst.albedo_min,mocst.albedo_max);
    // 2) ocean
    set_spinbutton_range(*retroaction_ocean_fix_autre_spinbutton,
	    mocst.puit_ocean_min,mocst.puit_ocean_max);
    //3) vegetation	
    set_spinbutton_range(*retroaction_vegetation_fix_spinbutton,
	    mocst.puit_bio_min,mocst.puit_bio_max);
    //4) vapeur d'eau
    set_spinbutton_range(*retroaction_vapeur_on_autre_spinbutton,
	    mocst.rapport_H2O_min,mocst.rapport_H2O_max);
}

void choix_des_parametres_dialog::read_from_SimulationValues()
{
    const SimulationValues& sv=ev.back();
    choix_nom_simulation_entry->set_text(sv.nom_simulation);
    // simulation_type_dialog
    if (sv.fixed_concentration)
    {
	concentration_vbox->show();
	emissions_vbox->hide();
	simulation_type_concentration_radiobutton->set_active();
    }
    else
    {
	concentration_vbox->hide();
	emissions_vbox->show();
	simulation_type_emission_radiobutton->set_active();
    }

    //concentration_dialog
    concentration_autre_radiobutton->set_active();
    concentration_autre_spinbutton->set_value(sv.coo_concentr_value);

    //emission_dialog
    emissions_anthro_autres_radiobutton->set_active();
    //GIEC Attention, la céfo
    emissions_anthro_autre_spinbutton->set_value(sv.emit_anthro_coo_value[0]);
    volcanisme_autre_radiobutton->set_active();
    volcanisme_autre_spinbutton->set_value(sv.volcan_value);
    alteration_autre_radiobutton->set_active();
    alteration_autre_spinbutton->set_value(sv.alteration_value);
    stockage_autre_radiobutton->set_active();
    stockage_autre_spinbutton->set_value(sv.stockage_biologique_value); 

    //parametres_astronomiques_dialog
    dist_terre_sol_other_radiobutton->set_active();
    distance_terre_soleil_spinbutton->set_value(sv.distance_ts_value);
    puissance_solaire_other_radiobutton->set_active();
    puissance_solaire_spinbutton->set_value(sv.puissance_soleil_value);
    precession_autre_radiobutton->set_active();
    precession_spinbutton->set_value(sv.precession_value);
    excenticite_other_radiobutton->set_active();
    excentricite_spinbutton->set_value(sv.excentricite_value);
    obliquite_other_radiobutton->set_active();
    obliquite_spinbutton->set_value(sv.obliquite_value);

    // retroactions_dialog
    // 1)albedo
    if (sv.fixed_albedo)
    {
	retroaction_albedo_off_radiobutton->set_active();
    }
    else
    {
	retroaction_albedo_on_radiobutton->set_active();
    }
    albedo_autre_radiobutton->set_active();
    albedo_autre_spinbutton->set_value(sv.albedo_value);
    // 2) ocean
    if (sv.debranche_ocean)
    {
	retroaction_ocean_off_radiobutton->set_active();
    }
    else if(sv.fixed_ocean)
    {
	retroaction_ocean_fix_radiobutton->set_active();
    }
    else
    {
	retroaction_ocean_on_radiobutton->set_active();
    }
    retroaction_ocean_fix_autre_radiobutton->set_active();
    retroaction_ocean_fix_autre_spinbutton->set_value(sv.puit_oce_value);
    //3) vegetation	
    if (sv.debranche_biologie)
    {
	retroaction_vegetation_off_radiobutton->set_active();
    }
    else
    {
	retroaction_vegetation_on_radiobutton->set_active();
    }
    retroaction_vegetation_on_autre_radiobutton->set_active();
    retroaction_vegetation_fix_spinbutton->set_value(sv.puit_bio_value);
    //4) vapeur d'eau
    if (sv.fixed_eau)
    {
	retroaction_vapeur_off_radiobutton->set_active();
    }
    else
    {
	retroaction_vapeur_on_radiobutton->set_active();
    }
    retroaction_vapeur_on_autre_radiobutton->set_active();
    retroaction_vapeur_on_autre_spinbutton->set_value(sv.rapport_H2O_value);
}

void choix_des_parametres_dialog::store_to_SimulationValues()
{
    SimulationValues& sv=ev.back();
    sv.nom_simulation=choix_nom_simulation_entry->get_text();
    // simulation_type_dialog
    sv.fixed_concentration=
	simulation_type_concentration_radiobutton->get_active();

    //concentration_dialog
    sv.coo_concentr_value=concentration_autre_spinbutton->get_value();

    //emission_dialog
    sv.emit_anthro_coo_value[0]=emissions_anthro_autre_spinbutton->get_value();
    sv.volcan_value=volcanisme_autre_spinbutton->get_value();
    sv.alteration_value=alteration_autre_spinbutton->get_value();
    sv.stockage_biologique_value=stockage_autre_spinbutton->get_value(); 

    //parametres_astronomiques_dialog
    sv.distance_ts_value=distance_terre_soleil_spinbutton->get_value();
    sv.puissance_soleil_value=puissance_solaire_spinbutton->get_value();
    sv.precession_value=precession_spinbutton->get_value();
    sv.excentricite_value=excentricite_spinbutton->get_value();
    sv.obliquite_value=obliquite_spinbutton->get_value();

    // retroactions_dialog
    // 1)albedo
    sv.fixed_albedo=
	retroaction_albedo_off_radiobutton->get_active();
    sv.albedo_value=albedo_autre_spinbutton->get_value();
    // 2) ocean
    sv.debranche_ocean=
	retroaction_ocean_off_radiobutton->get_active();
    sv.fixed_ocean=
	retroaction_ocean_fix_radiobutton->get_active();
    sv.puit_oce_value=retroaction_ocean_fix_autre_spinbutton->get_value();
    //3) vegetation	
    sv.debranche_biologie=
	retroaction_vegetation_off_radiobutton->get_active();
    sv.puit_bio_value=retroaction_vegetation_fix_spinbutton->get_value();
    //4) vapeur d'eau
    sv.fixed_eau=
	retroaction_vapeur_off_radiobutton->get_active();
    sv.rapport_H2O_value=retroaction_vapeur_on_autre_spinbutton->get_value();
}

