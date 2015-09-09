// using glademm V2.6.0
//
// newer (non customized) versions of this file go to choix_des_parametres_dialog.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _CHOIX_DES_PARAMETRES_DIALOG_HH
#  include "choix_des_parametres_dialog_glade.hh"
#  define _CHOIX_DES_PARAMETRES_DIALOG_HH
class choix_des_parametres_dialog : public choix_des_parametres_dialog_glade
{  
    public:
	choix_des_parametres_dialog();
	void read_from_SimulationValues();
	void store_to_SimulationValues();
        
    private:        
        void on_cancelbutton8_clicked();
        void on_choix_parametres_okbutton_clicked();
        void on_dist_terre_sol_actuel_radiobutton_toggled();
        void on_dist_terre_sol_other_radiobutton_toggled();
        void on_distance_terre_soleil_spinbutton_value_changed();
        void on_puissance_solaire_actuel_radiobutton_toggled();
        void on_puissance_solaire_creation_radiobutton_toggled();
        void on_puissance_solaire_other_radiobutton_toggled();
        void on_puissance_solaire_spinbutton_value_changed();
        void on_excentricite_actuel_radiobutton_toggled();
        void on_excentricite_min_radiobutton_toggled();
        void on_excentricite_max_radiobutton_toggled();
        void on_excenticite_other_radiobutton_toggled();
        void on_excentricite_spinbutton_editing_done();
        void on_obliquite_actuel_radiobutton_toggled();
        void on_obliquite_min_radiobutton_toggled();
        void on_obliquite_max_radiobutton_toggled();
        void on_obliquite_other_radiobutton_toggled();
        void on_obliquite_spinbutton_value_changed();
        void on_precession_actuel_radiobutton_toggled();
        void on_precession_min_radiobutton_toggled();
        void on_precession_max_radiobutton_toggled();
        void on_precession_autre_radiobutton_toggled();
        void on_precession_spinbutton_value_changed();
        void on_simulation_type_concentration_radiobutton_toggled();
        void on_simulation_type_emission_radiobutton_toggled();
        void on_concentration_actuel_radiobutton_toggled();
        void on_concentration_1750_radiobutton_toggled();
        void on_concentration_cretace_radiobutton_toggled();
        void on_concentration_terreinitiale_radiobutton_toggled();
        void on_concentration_autre_radiobutton_toggled();
        void on_concentration_autre_spinbutton_value_changed();
        void on_emissions_anthro_nulles_radiobutton_toggled();
        void on_emissions_anthro_actuel_radiobutton_toggled();
        void on_emissions_anthro_double_radiobutton_toggled();
        void on_emissions_anthro_autres_radiobutton_toggled();
        void on_emissions_anthro_autre_spinbutton_value_changed();
        void on_volcanisme_actuel_radiobutton_toggled();
        void on_radiobutton28_toggled();
        void on_volcanisme_autre_radiobutton_toggled();
        void on_volcanisme_autre_spinbutton_value_changed();
        void on_alteration_actuel_radiobutton_toggled();
        void on_alteration_autre_radiobutton_toggled();
        void on_spinbutton10_value_changed();
        void on_stockahe_nul_radiobutton_toggled();
        void on_stockage_carbonifere_radiobutton_toggled();
        void on_stockage_autre_radiobutton_toggled();
        void on_stockage_autre_spinbutton_value_changed();
        void on_retroaction_albedo_off_radiobutton_toggled();
        void on_albedo_actuel_radiobutton_toggled();
        void on_albedo_glace_radiobutton_toggled();
        void on_albedo_terre_radiobutton_toggled();
        void on_albedo_autre_radiobutton_toggled();
        void on_albedo_autre_spinbutton_value_changed();
        void on_retroaction_albedo_on_radiobutton_toggled();
        void on_retroaction_ocean_off_radiobutton_toggled();
        void on_retroaction_ocean_fix_radiobutton_toggled();
        void on_retroaction_ocean_fix_regler_actuel_radiobutton_toggled();
        void on_retroaction_ocean_fix_autre_radiobutton_toggled();
        void on_retroaction_ocean_fix_autre_spinbutton_value_changed();
        void on_retroaction_ocean_on_radiobutton_toggled();
        void on_retroaction_vegetation_off_radiobutton_toggled();
        void on_retroaction_vegetation_on_radiobutton_toggled();
        void on_retroaction_vegetation_on_actuel_radiobutton_toggled();
        void on_retroaction_vegetation_on_autre_radiobutton_toggled();
        void on_retroaction_vegetation_fix_spinbutton_value_changed();
        void on_retroaction_vapeur_off_radiobutton_toggled();
        void on_retroaction_vapeur_on_actuel_radiobutton_toggled();
        void on_retroaction_vapeur_on_autre_radiobutton_toggled();
        void on_spinbutton11_value_changed();
        void on_retroaction_vapeur_on_radiobutton_toggled();
	bool on_delete_event(GdkEventAny *) {on_cancelbutton8_clicked(); return false;} 
};
#endif
