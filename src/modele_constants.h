#ifndef MODELES_CONSTANTS_H
#define MODELES_CONSTANTS_H
#include "graphe_shown.h"
#include <string>


class ModeleConstants
{
    public:
	//main_window
	int enable_gl_animations;
	double echeance_min;
	double echeance_max;
	double echeance_reset_value;
	double time_slider_reset_value;

	//initialisation des combo-boxes
	GraphShown graphe_one_init;
	GraphShown graphe_two_init;
	GraphShown graphe_three_init;
	GraphShown graphe_four_init;

	// type de simulation (simulation_type-dialog)
	int fixed_concentration_reset_value;

	//concentration en CO2: utilisé dans concentration_dialog
	double coo_concentr_terre_initiale;
	double coo_concentr_cretace;
	double coo_concentr_1750;
	double coo_concentr_today;
	double coo_concentr_min;
	double coo_concentr_max;
	double coo_concentr_reset_value;

	//emission: utilisées dans emission_dialog
	double emit_anthro_coo_nul;
	double emit_anthro_coo_actuel;
	double emit_anthro_coo_2xactuel;
	double emit_anthro_coo_min;
	double emit_anthro_coo_max;
	double emit_anthro_coo_reset_value;

	double volcan_terre_init;
	double volcan_actuel;
	double volcan_min;
	double volcan_max;
	double volcan_reset_value;

	double alteration_actuel;
	double alteration_min;
	double alteration_max;
	double alteration_reset_value;

	double stockage_biologique_actuel;
	double stockage_biologique_carbonifere;
	double stockage_biologique_min;	
	double stockage_biologique_max;
	double stockage_biologique_reset_value;

	// retroactions climatiques (retroactions_dialog)
	// 1) albedo:
	int fixed_albedo_reset_value;
	double albedo_act;
	double albedo_glace;
	double albedo_terre;
	double albedo_min;
	double albedo_max;
	double albedo_reset_value;

	//2) ocean
	int fixed_ocean_reset_value;
	int debranche_ocean_reset_value;
	double puit_ocean_actuel;
	double puit_ocean_min;
	double puit_ocean_max;
	double puit_ocean_reset_value;

	//3) vegetation
	int debranche_biologie_reset_value;
	double puit_bio_actuel;
	double puit_bio_min;
	double puit_bio_max;
	double puit_bio_reset_value;

	//4) vapeur d'eau
	int fixed_eau_reset_value;
	double rapport_H2O_actuel;
	double rapport_H2O_min;
	double rapport_H2O_max;
	double rapport_H2O_reset_value;

	//param astro (parametres_astronomique_dialog)
	//1) distance
	double distance_ts_actuel;
	double distance_ts_min;
	double distance_ts_max;
	double distance_ts_reset_value;
	//2) puissance
	double puissance_soleil_terre_init;
	double puissance_soleil_actuel;
	double puissance_soleil_min;
	double puissance_soleil_max;
	double puissance_soleil_reset_value;	
	//3) excentricite
	double excentricite_act;
	double excentricite_valeur_min;
	double excentricite_valeur_max;
	double excentricite_autre_min;
	double excentricite_autre_max;
	double excentricite_reset_value;
	//4) obliquite
	double obliquite_act;
	double obliquite_valeur_min;
	double obliquite_valeur_max;
	double obliquite_autre_min;
	double obliquite_autre_max;
	double obliquite_reset_value;
	//5) precession	
	double precession_act;
	double precession_valeur_min;
	double precession_valeur_max;
	double precession_autre_min;
	double precession_autre_max;
	double precession_reset_value;

	ModeleConstants();
  std::string graph_type_title(GraphShown gs) const;
};
#endif // MODELES_CONSTANTS_H
