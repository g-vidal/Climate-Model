#include "simulation_values.h"
#include <sstream>
#include "globals.h"
#include <iostream>
using namespace std;

string SimulationValues::generate_name()
{
    static int number_of_simul=0;
    ostringstream oss;
    oss << "simul" << ++number_of_simul;
    return oss.str();
}

void SimulationValues::init(const string& name)
{
    nom_simulation=name;
}



// recast la simulation s en la simulation dont on appelle le recast.
// par exemple, si on appelle etat_initial.recast_final_initial(s), alors etat_initial devient s, mais les tableaux sont recastés en états initiaux
void SimulationValues::recast_final_initial(const SimulationValues& s)
{
    //copie tout s brutalement
    *this=s;
    //traitement particulier
    annee_debut=s.annee_debut+s.temperature_data.xmax();
    emissions_coo_data.recast_final_initial(s.emissions_coo_data);
    concentrations_coo_data.recast_final_initial(s.concentrations_coo_data);
    temperature_data.recast_final_initial(s.temperature_data);
    niveau_calottes_data.recast_final_initial(s.niveau_calottes_data);
    niveau_mer_data.recast_final_initial(s.niveau_mer_data);
    albedo_data.recast_final_initial(s.albedo_data);
    /*
    fixed_concentration=s.fixed_concentration;
    emit_anthro_coo_value=s.emit_anthro_coo_value;
    volcan_value=s.volcan_value;
    alteration_value=s.alteration_value;
    stockage_biologique_value=s.stockage_biologique_value;
    puissance_soleil_value=s.puissance_soleil_value;
    distance_ts_value=s.distance_ts_value;
    precession_value=s.precession_value;
    excentricite_value=s.excentricite_value;
    obliquite_value=s.obliquite_value;
    fixed_albedo=s.fixed_albedo;
    albedo_value=s.albedo_value;
    debranche_ocean=s.debranche_ocean;
    fixed_ocean=s.fixed_ocean;
    puit_oce_value=s.puit_oce_value;
    debranche_biologie=s.debranche_biologie;
    puit_bio_value=s.puit_bio_value;
    fixed_eau=s.fixed_eau;
    rapport_H20_value=s.rapport_H20_value;
    */
}

std::ostream& operator<<(std::ostream& out,const SimulationValues& sv)
{
    out << sv.nom_simulation<<endl;
    out << sv.annee_debut<<endl;
    out << sv.emissions_coo_data<<endl;
    out << sv.concentrations_coo_data<<endl;
    out << sv.temperature_data <<endl;
    out << sv.niveau_calottes_data <<endl;
    out << sv.niveau_mer_data<<endl;
    out << sv.albedo_data<<endl;
    out << sv.fixed_concentration<<" ";
    out << sv.coo_concentr_value<<" ";
    out << sv.emit_anthro_coo_value<<" ";
    out << sv.volcan_value<<" ";
    out << sv.alteration_value<<" ";
    out << sv.stockage_biologique_value<<" ";
    out << sv.puissance_soleil_value<<" ";
    out << sv.distance_ts_value<<" ";
    out << sv.precession_value<<" ";
    out << sv.excentricite_value<<" ";
    out << sv.obliquite_value<<" ";
    out << sv.fixed_albedo<<" ";
    out << sv.albedo_value<<" ";
    out << sv.debranche_ocean<<" ";
    out << sv.fixed_ocean<<" ";
    out << sv.puit_oce_value<<" ";
    out << sv.debranche_biologie<<" ";
    out << sv.puit_bio_value<<" ";
    out << sv.fixed_eau<<" ";
    out << sv.rapport_H2O_value;
    return out;
}

std::istream& operator>>(std::istream& in,SimulationValues& sv)
{
    //lecture du nom de simulation
    std::string tmp_line;
    std::getline(in,tmp_line);
    sv.nom_simulation = tmp_line;
    //le reste
    in >> sv.annee_debut;
    in >> sv.emissions_coo_data;
    in >> sv.concentrations_coo_data;
    in >> sv.temperature_data;
    in >> sv.niveau_calottes_data;
    in >> sv.niveau_mer_data;
    in >> sv.albedo_data;
    in >> sv.fixed_concentration;
    in >> sv.coo_concentr_value;
    in >> sv.emit_anthro_coo_value;
    in >> sv.volcan_value;
    in >> sv.alteration_value;
    in >> sv.stockage_biologique_value;
    in >> sv.puissance_soleil_value;
    in >> sv.distance_ts_value;
    in >> sv.precession_value;
    in >> sv.excentricite_value;
    in >> sv.obliquite_value;
    in >> sv.fixed_albedo;
    in >> sv.albedo_value;
    in >> sv.debranche_ocean;
    in >> sv.fixed_ocean;
    in >> sv.puit_oce_value;
    in >> sv.debranche_biologie;
    in >> sv.puit_bio_value;
    in >> sv.fixed_eau;
    in >> sv.rapport_H2O_value;
    return in;
}

void SimulationValues::deep_copy(const SimulationValues& s)
{
    nom_simulation=s.nom_simulation.c_str();
    annee_debut=s.annee_debut;

    emissions_coo_data=s.emissions_coo_data;
    concentrations_coo_data=s.concentrations_coo_data;
    temperature_data=s.temperature_data;
    niveau_calottes_data=s.niveau_calottes_data;
    niveau_mer_data=s.niveau_mer_data;
    albedo_data=s.albedo_data;

    // simulation_type_dialog
    fixed_concentration=s.fixed_concentration;

    //concentration_dialog
    coo_concentr_value=s.coo_concentr_value;

    //emission_dialog
    emit_anthro_coo_value=s.emit_anthro_coo_value;
    volcan_value=s.volcan_value;
    alteration_value=s.alteration_value;
    stockage_biologique_value=s.stockage_biologique_value; 

    //parametres_astronomiques_dialog
    puissance_soleil_value=s.puissance_soleil_value;
    distance_ts_value=s.distance_ts_value;
    precession_value=s.precession_value;
    excentricite_value=s.excentricite_value;
    obliquite_value=s.obliquite_value;

    // retroactions_dialog
    // 1)albedo
    fixed_albedo=s.fixed_albedo;
    albedo_value=s.albedo_value;
    // 2) ocean
    debranche_ocean=s.debranche_ocean;
    fixed_ocean=s.fixed_ocean;
    puit_oce_value=s.puit_oce_value;
    //3) vegetation	
    debranche_biologie=s.debranche_biologie;
    puit_bio_value=s.puit_bio_value;
    //4) vapeur d'eau
    fixed_eau=s.fixed_eau;
    rapport_H2O_value=s.rapport_H2O_value;
}

