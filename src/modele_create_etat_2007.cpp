#include "globals.h"
#include "modele_consts_physique.h"
#include "cmath"
#include <iostream>
#include <fstream>

using namespace std;

#define mc modele_constants 

#define ID_MIN -100
#define ID_MAX 100
#define TEMPS_ELEM 1.
#define INTERN_ECHEANCE 100.

SimulationValues create_etat_2007() 
{
    SimulationValues s("le monde en 2007",ID_MIN,ID_MAX,TEMPS_ELEM);
    s.annee_debut=1907.;
    s.fixed_eau=0;	
    s.fixed_concentration=0;		
    s.debranche_biologie=0;	
    s.fixed_ocean=0;	
    s.debranche_ocean=0;
    s.fixed_albedo=0;		
    s.rapport_H2O_value=mc.rapport_H2O_actuel;	
    s.puit_bio_value=mc.puit_bio_reset_value;
    s.puit_oce_value=mc.puit_ocean_reset_value;
    s.albedo_value=mc.albedo_reset_value;
    s.coo_concentr_value=concentration_coo_actuel;
    s.puissance_soleil_value=mc.puissance_soleil_reset_value;
    s.distance_ts_value=mc.distance_ts_reset_value;
    s.obliquite_value=mc.obliquite_reset_value;
    s.excentricite_value=mc.excentricite_reset_value;
    s.precession_value=mc.precession_reset_value;
    s.alteration_value=mc.alteration_reset_value;
    s.emit_anthro_coo_value=emit_anthro_coo_act;
    s.volcan_value=mc.volcan_reset_value;
    s.stockage_biologique_value=mc.stockage_biologique_reset_value;

    for (int t=ID_MIN;t<=ID_MAX;t++) {
	s.temperature_data[t]=temperature_actuelle
	    +(TEMPS_ELEM*(t-ID_MAX)*deltaT_last_century)
	    /INTERN_ECHEANCE;
	s.niveau_mer_data[t]=0.;
	s.niveau_calottes_data[t]=niveau_calottes_actuel;
	s.concentrations_coo_data[t]=concentration_coo_actuel;
	s.emissions_coo_data[t]=emit_anthro_coo_act*(1-puit_bio_act-puit_ocean_act);
	s.albedo_data[t]=albedo_actuel*100;
    }
    return s;
}
