#include "modele_constants.h"
#include "globals.h"
#include "modele_consts_physique.h"
#include "exceptions.h"
#include <iostream>
#include "traduction.h"
using namespace std;

ModeleConstants::ModeleConstants() 
{
    enable_gl_animations=0;//0 si pas d'animation, 1 si animation 
    echeance_min=100; // en année
    echeance_max=10e6; // en année
    echeance_reset_value=500; //en année 
    time_slider_reset_value=0; //en %age de l'échéance

    // *affichage des results
    graphe_one_init= TEMPERATURE; 
    graphe_two_init= CONCENTRATION_CO2;
    graphe_three_init= WATERLEVEL;
    graphe_four_init= CALOTTESLEVEL;

    //* simulation_type
    fixed_concentration_reset_value=1;

    //* concentrations en CO2 en ppm
    coo_concentr_terre_initiale=0.3e6;
    coo_concentr_cretace=1500;
    coo_concentr_1750=concentration_coo_1750;
    coo_concentr_today=concentration_coo_actuel;
    coo_concentr_min=0;
    coo_concentr_max=1e6;
    coo_concentr_reset_value=coo_concentr_1750;

    //* emissions de CO2, en Gt/an.
    //** emissions antropiques
    emit_anthro_coo_actuel=emit_anthro_coo_act; // en GT
    emit_anthro_coo_2xactuel=emit_anthro_coo_act*2;
    emit_anthro_coo_nul=0.;
    emit_anthro_coo_min=-2;
    emit_anthro_coo_max=50;
    emit_anthro_coo_reset_value=emit_anthro_coo_nul;

    //** volcanisme
    volcan_actuel=volcanisme_actuel;// volcanisme continental? 0.083
    volcan_terre_init=volcan_actuel*5; 
    // d'après les flux de chaleurs en fonction du temps depuis formation de la terre données sur www.geo.mtu.edu/svl/GE3320/LECTURE%206.ppt
    //volcan_terre_600ma=volcan_actuel*2; // d'après la même source
    volcan_min=0;
    volcan_max=volcan_terre_init*6;
    volcan_reset_value=volcan_actuel;

    //** alteration, en % de variation par rapport � la ref=C_alteration_naturel
    alteration_actuel=100.; //en Gt/an: transport par fleuves: 0.4
    alteration_min=0.0;
    alteration_max=1000.0; // alt�ration 10x plus forte
    alteration_reset_value=alteration_actuel;

    //** stockage biologique
    stockage_biologique_actuel=0.;
    stockage_biologique_carbonifere=-stockage_carbonifere*1e3; // en Mt/an/ppm
    stockage_biologique_min=0.;
    stockage_biologique_max=-stockage_max*1e3;// en Mt/an/ppm
    stockage_biologique_reset_value=0.;

    // * albédo
    fixed_albedo_reset_value=0;
    albedo_act=albedo_actuel*100;
    albedo_reset_value=albedo_actuel*100;
    albedo_glace=albedo_glace_const*100;
    albedo_terre=albedo_ter*100;
    albedo_min=0.;
    albedo_max=100.;

    //** puit biologique
    debranche_biologie_reset_value=0;
    puit_bio_actuel=puit_bio_act; // en fraction de l'excédent humain (emissions +deforest) absorbé
    puit_bio_min=-50;
    puit_bio_max=100.;
    puit_bio_reset_value=puit_bio_actuel;

    //** puit océanique
    fixed_ocean_reset_value=1;
    debranche_ocean_reset_value=0;
    puit_ocean_actuel=puit_ocean_act;// en fraction de l'excédent humain (emissions +deforest) absorbé
    puit_ocean_min=-50;
    puit_ocean_max=100.;
    puit_ocean_reset_value=puit_ocean_actuel;

    // vapeur d'eau
    fixed_eau_reset_value=0;
    rapport_H2O_reset_value=100.; // H20(t)/H20_actuel
    rapport_H2O_actuel=100.*rapport_H2O_actconst;
    rapport_H2O_min=0.;
    rapport_H2O_max=1000.;

    //* parametres orbitaux
    // en fraction d'augmentation par rapport à l'actuel, en %
    puissance_soleil_terre_init=-30; 
    puissance_soleil_actuel=100;
    puissance_soleil_min=0;
    puissance_soleil_max=1000;
    puissance_soleil_reset_value=puissance_soleil_actuel;
    distance_ts_actuel=100;// en fraction d'augmentation par rapport à l'actuel
    distance_ts_min=0;
    distance_ts_max=1000;
    distance_ts_reset_value=distance_ts_actuel;

    //* paramètres orbitaux
    excentricite_act=excentricite_actuel; // en fraction
    excentricite_reset_value=excentricite_act; // en fraction
    excentricite_valeur_min=0.;
    excentricite_valeur_max=0.06;
    excentricite_autre_min=0.;
    excentricite_autre_max=0.2;

    obliquite_act=obliquite_actuel; // en degrès
    obliquite_reset_value=obliquite_act; // en degrès
    obliquite_valeur_min=21.8;
    obliquite_valeur_max=24.4;
    obliquite_autre_min=0.;
    obliquite_autre_max=90.;

    precession_act=precession_actuel; // en degrès        
    precession_reset_value=precession_act; // en degrès
    // 31 janv 2009: on met les min et max � -90 et 90 respectivement, au lieu de -180 et 180, car c'est avec -90 et 90 qu'on a les �carts de temp�rature les plus fort.
    precession_valeur_min=90;
    precession_valeur_max=270;
    precession_autre_min=0;
    precession_autre_max=360;
}

Glib::ustring ModeleConstants::graph_type_title(GraphShown gs) const
{
    //TODO UTF-8
    switch(gs)
    {
	case TEMPERATURE:
	    return gettext("Température (en °C)");
	case WATERLEVEL:
	    return  gettext("Niveau de la mer (en m)");
	case CALOTTESLEVEL:
	    return  gettext("Latitude des calottes (en deg.)");
	case CONCENTRATION_CO2:
	    return  gettext("Concentration de CO2 (en ppm)");
	case EMISSIONS_CO2:
	    return  gettext("Émissions de CO2 (en Gt/an)");
	case ALBEDO:
	    return  gettext("Albédo (en %)");
	default:
	    PLANTE("type de graph inexistant");
    }
    return "";
}
