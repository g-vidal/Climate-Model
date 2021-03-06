// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/camille/ubuntu/CIES/Atelier_projet/projet_climat_new/climat.glade
// for gtk 2.10.6 and gtkmm 2.10.2
//
// Please modify the corresponding derived classes in ./src/choix_des_parametres_dialog.hh and./src/choix_des_parametres_dialog.cc

#ifndef _CHOIX_DES_PARAMETRES_DIALOG_GLADE_HH
#  define _CHOIX_DES_PARAMETRES_DIALOG_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/dialog.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>

class choix_des_parametres_dialog_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::RadioButton * dist_terre_sol_actuel_radiobutton;
        class Gtk::RadioButton * dist_terre_sol_other_radiobutton;
        class Gtk::SpinButton * distance_terre_soleil_spinbutton;
        class Gtk::RadioButton * puissance_solaire_actuel_radiobutton;
        class Gtk::RadioButton * puissance_solaire_creation_radiobutton;
        class Gtk::RadioButton * puissance_solaire_other_radiobutton;
        class Gtk::SpinButton * puissance_solaire_spinbutton;
        class Gtk::RadioButton * excentricite_actuel_radiobutton;
        class Gtk::RadioButton * excentricite_min_radiobutton;
        class Gtk::RadioButton * excentricite_max_radiobutton;
        class Gtk::RadioButton * excenticite_other_radiobutton;
        class Gtk::SpinButton * excentricite_spinbutton;
        class Gtk::RadioButton * obliquite_actuel_radiobutton;
        class Gtk::RadioButton * obliquite_min_radiobutton;
        class Gtk::RadioButton * obliquite_max_radiobutton;
        class Gtk::RadioButton * obliquite_other_radiobutton;
        class Gtk::SpinButton * obliquite_spinbutton;
        class Gtk::RadioButton * precession_actuel_radiobutton;
        class Gtk::RadioButton * precession_min_radiobutton;
        class Gtk::RadioButton * precession_max_radiobutton;
        class Gtk::RadioButton * precession_autre_radiobutton;
        class Gtk::SpinButton * precession_spinbutton;
        class Gtk::RadioButton * simulation_type_concentration_radiobutton;
        class Gtk::RadioButton * simulation_type_emission_radiobutton;
        class Gtk::RadioButton * concentration_actuel_radiobutton;
        class Gtk::RadioButton * concentration_1750_radiobutton;
        class Gtk::RadioButton * concentration_cretace_radiobutton;
        class Gtk::RadioButton * concentration_terreinitiale_radiobutton;
        class Gtk::RadioButton * concentration_autre_radiobutton;
        class Gtk::SpinButton * concentration_autre_spinbutton;
        class Gtk::VBox * concentration_vbox;
        class Gtk::RadioButton * emissions_anthro_nulles_radiobutton;
        class Gtk::RadioButton * emissions_anthro_actuel_radiobutton;
        class Gtk::RadioButton * emissions_anthro_double_radiobutton;
        class Gtk::RadioButton * emissions_anthro_autres_radiobutton;
        class Gtk::SpinButton * emissions_anthro_autre_spinbutton;
        class Gtk::RadioButton * volcanisme_actuel_radiobutton;
        class Gtk::RadioButton * volcanisme_terre_init_radiobutton;
        class Gtk::RadioButton * volcanisme_autre_radiobutton;
        class Gtk::SpinButton * volcanisme_autre_spinbutton;
        class Gtk::RadioButton * alteration_actuel_radiobutton;
        class Gtk::RadioButton * alteration_autre_radiobutton;
        class Gtk::SpinButton * alteration_autre_spinbutton;
        class Gtk::RadioButton * stockahe_nul_radiobutton;
        class Gtk::RadioButton * stockage_carbonifere_radiobutton;
        class Gtk::RadioButton * stockage_autre_radiobutton;
        class Gtk::SpinButton * stockage_autre_spinbutton;
        class Gtk::VBox * emissions_vbox;
        class Gtk::RadioButton * retroaction_albedo_off_radiobutton;
        class Gtk::RadioButton * albedo_actuel_radiobutton;
        class Gtk::RadioButton * albedo_glace_radiobutton;
        class Gtk::RadioButton * albedo_terre_radiobutton;
        class Gtk::RadioButton * albedo_autre_radiobutton;
        class Gtk::SpinButton * albedo_autre_spinbutton;
        class Gtk::RadioButton * retroaction_albedo_on_radiobutton;
        class Gtk::RadioButton * retroaction_ocean_off_radiobutton;
        class Gtk::RadioButton * retroaction_ocean_fix_radiobutton;
        class Gtk::RadioButton * retroaction_ocean_fix_regler_actuel_radiobutton;
        class Gtk::RadioButton * retroaction_ocean_fix_autre_radiobutton;
        class Gtk::SpinButton * retroaction_ocean_fix_autre_spinbutton;
        class Gtk::RadioButton * retroaction_ocean_on_radiobutton;
        class Gtk::RadioButton * retroaction_vegetation_off_radiobutton;
        class Gtk::RadioButton * retroaction_vegetation_on_radiobutton;
        class Gtk::RadioButton * retroaction_vegetation_on_actuel_radiobutton;
        class Gtk::RadioButton * retroaction_vegetation_on_autre_radiobutton;
        class Gtk::SpinButton * retroaction_vegetation_fix_spinbutton;
        class Gtk::RadioButton * retroaction_vapeur_off_radiobutton;
        class Gtk::RadioButton * retroaction_vapeur_on_actuel_radiobutton;
        class Gtk::RadioButton * retroaction_vapeur_on_autre_radiobutton;
        class Gtk::SpinButton * retroaction_vapeur_on_autre_spinbutton;
        class Gtk::RadioButton * retroaction_vapeur_on_radiobutton;
        class Gtk::Entry * choix_nom_simulation_entry;
protected:
        
        choix_des_parametres_dialog_glade();
        
        ~choix_des_parametres_dialog_glade();
private:
        virtual void on_cancelbutton8_clicked() = 0;
        virtual void on_choix_parametres_okbutton_clicked() = 0;
        virtual void on_dist_terre_sol_actuel_radiobutton_toggled() = 0;
        virtual void on_dist_terre_sol_other_radiobutton_toggled() = 0;
        virtual void on_distance_terre_soleil_spinbutton_value_changed() = 0;
        virtual void on_puissance_solaire_actuel_radiobutton_toggled() = 0;
        virtual void on_puissance_solaire_creation_radiobutton_toggled() = 0;
        virtual void on_puissance_solaire_other_radiobutton_toggled() = 0;
        virtual void on_puissance_solaire_spinbutton_value_changed() = 0;
        virtual void on_excentricite_actuel_radiobutton_toggled() = 0;
        virtual void on_excentricite_min_radiobutton_toggled() = 0;
        virtual void on_excentricite_max_radiobutton_toggled() = 0;
        virtual void on_excenticite_other_radiobutton_toggled() = 0;
        virtual void on_excentricite_spinbutton_editing_done() = 0;
        virtual void on_obliquite_actuel_radiobutton_toggled() = 0;
        virtual void on_obliquite_min_radiobutton_toggled() = 0;
        virtual void on_obliquite_max_radiobutton_toggled() = 0;
        virtual void on_obliquite_other_radiobutton_toggled() = 0;
        virtual void on_obliquite_spinbutton_value_changed() = 0;
        virtual void on_precession_actuel_radiobutton_toggled() = 0;
        virtual void on_precession_min_radiobutton_toggled() = 0;
        virtual void on_precession_max_radiobutton_toggled() = 0;
        virtual void on_precession_autre_radiobutton_toggled() = 0;
        virtual void on_precession_spinbutton_value_changed() = 0;
        virtual void on_simulation_type_concentration_radiobutton_toggled() = 0;
        virtual void on_simulation_type_emission_radiobutton_toggled() = 0;
        virtual void on_concentration_actuel_radiobutton_toggled() = 0;
        virtual void on_concentration_1750_radiobutton_toggled() = 0;
        virtual void on_concentration_cretace_radiobutton_toggled() = 0;
        virtual void on_concentration_terreinitiale_radiobutton_toggled() = 0;
        virtual void on_concentration_autre_radiobutton_toggled() = 0;
        virtual void on_concentration_autre_spinbutton_value_changed() = 0;
        virtual void on_emissions_anthro_nulles_radiobutton_toggled() = 0;
        virtual void on_emissions_anthro_actuel_radiobutton_toggled() = 0;
        virtual void on_emissions_anthro_double_radiobutton_toggled() = 0;
        virtual void on_emissions_anthro_autres_radiobutton_toggled() = 0;
        virtual void on_emissions_anthro_autre_spinbutton_value_changed() = 0;
        virtual void on_volcanisme_actuel_radiobutton_toggled() = 0;
        virtual void on_radiobutton28_toggled() = 0;
        virtual void on_volcanisme_autre_radiobutton_toggled() = 0;
        virtual void on_volcanisme_autre_spinbutton_value_changed() = 0;
        virtual void on_alteration_actuel_radiobutton_toggled() = 0;
        virtual void on_alteration_autre_radiobutton_toggled() = 0;
        virtual void on_spinbutton10_value_changed() = 0;
        virtual void on_stockahe_nul_radiobutton_toggled() = 0;
        virtual void on_stockage_carbonifere_radiobutton_toggled() = 0;
        virtual void on_stockage_autre_radiobutton_toggled() = 0;
        virtual void on_stockage_autre_spinbutton_value_changed() = 0;
        virtual void on_retroaction_albedo_off_radiobutton_toggled() = 0;
        virtual void on_albedo_actuel_radiobutton_toggled() = 0;
        virtual void on_albedo_glace_radiobutton_toggled() = 0;
        virtual void on_albedo_terre_radiobutton_toggled() = 0;
        virtual void on_albedo_autre_radiobutton_toggled() = 0;
        virtual void on_albedo_autre_spinbutton_value_changed() = 0;
        virtual void on_retroaction_albedo_on_radiobutton_toggled() = 0;
        virtual void on_retroaction_ocean_off_radiobutton_toggled() = 0;
        virtual void on_retroaction_ocean_fix_radiobutton_toggled() = 0;
        virtual void on_retroaction_ocean_fix_regler_actuel_radiobutton_toggled() = 0;
        virtual void on_retroaction_ocean_fix_autre_radiobutton_toggled() = 0;
        virtual void on_retroaction_ocean_fix_autre_spinbutton_value_changed() = 0;
        virtual void on_retroaction_ocean_on_radiobutton_toggled() = 0;
        virtual void on_retroaction_vegetation_off_radiobutton_toggled() = 0;
        virtual void on_retroaction_vegetation_on_radiobutton_toggled() = 0;
        virtual void on_retroaction_vegetation_on_actuel_radiobutton_toggled() = 0;
        virtual void on_retroaction_vegetation_on_autre_radiobutton_toggled() = 0;
        virtual void on_retroaction_vegetation_fix_spinbutton_value_changed() = 0;
        virtual void on_retroaction_vapeur_off_radiobutton_toggled() = 0;
        virtual void on_retroaction_vapeur_on_actuel_radiobutton_toggled() = 0;
        virtual void on_retroaction_vapeur_on_autre_radiobutton_toggled() = 0;
        virtual void on_spinbutton11_value_changed() = 0;
        virtual void on_retroaction_vapeur_on_radiobutton_toggled() = 0;
};
#endif
