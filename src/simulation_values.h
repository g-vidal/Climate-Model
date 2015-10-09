#ifndef SIMULATION_VALUES_H
#define SIMULATION_VALUES_H

#include <string.h>
#include "tableau.h"

//current values
class SimulationValues
{
    public:
    static std::string generate_name();
    std::string nom_simulation;
	double annee_debut;

	tableau emissions_coo_data;
	tableau concentrations_coo_data;
	tableau temperature_data;
	tableau niveau_calottes_data;
	tableau niveau_mer_data;
	tableau albedo_data;

	// simulation_type_dialog
	bool fixed_concentration;

	//concentration_dialog
	double coo_concentr_value;

	//emission_dialog
	double emit_anthro_coo_value;
	double volcan_value;
	double alteration_value;
	double stockage_biologique_value; 

	//parametres_astronomiques_dialog
	double puissance_soleil_value;
	double distance_ts_value;
	double precession_value;
	double excentricite_value;
	double obliquite_value;

	// retroactions_dialog
	// 1)albedo
	bool fixed_albedo;
	double albedo_value;
	// 2) ocean
	bool debranche_ocean;
	bool fixed_ocean;
	double puit_oce_value;
	//3) vegetation	
	bool debranche_biologie;
	double puit_bio_value;
	//4) vapeur d'eau
	bool fixed_eau;
	double rapport_H2O_value;

        private:
    void init(const std::string& name);
    public:
	inline SimulationValues() 
	{
	    init("new Simulation Value");
	}
    inline SimulationValues(const std::string& name)
	{
	    init(name);
	}
	//ce constructeur est appelé pour créer des simulation 
	//values constants (1750 et/ou 2007)
    SimulationValues(const std::string& name,
		int indice_min,
		int indice_max,
		double temps_elem):
	emissions_coo_data(temps_elem,indice_min,indice_max),
	concentrations_coo_data(temps_elem,indice_min,indice_max),
	temperature_data(temps_elem,indice_min,indice_max),
	niveau_calottes_data(temps_elem,indice_min,indice_max),
	niveau_mer_data(temps_elem,indice_min,indice_max),
	albedo_data(temps_elem,indice_min,indice_max) {
	    init(name);
	}
	
	//entrees-sorties
	friend std::ostream& operator<<
	    (std::ostream& out,	const SimulationValues& sv);
	friend std::istream& operator>>
	    (std::istream& in,SimulationValues& sv);

	//copie et transforme sv en état initial
	void recast_final_initial(const SimulationValues& sv);

	SimulationValues& operator=(const SimulationValues& s)
	{
	    if (&s!=this) deep_copy(s);
	    return *this;
	}
	SimulationValues(const SimulationValues& s)
	{
	    deep_copy(s);
	}

    private:
	void deep_copy(const SimulationValues& s);
};
#endif // SIMULATION_VALUES_H
