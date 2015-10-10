#include "experience_values.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "exceptions.h"
using namespace std;

void ExperienceValues::set_etat_initial(std::string filename,double echeance)
{
    while (!sv.empty()) {
	pop_back_simulation();	
    }
    calcul_indices(echeance);
    WARNING("entrée");
    SimulationValues s("initial");
    // SORTIE("input_file_name " << filename);
    ifstream ifs(filename.c_str());
    if (!ifs) {PLANTE("fichier inexistant");}	
    ifs >>s;
    ifs.close();
    WARNING("s lue");
    // SORTIE("s.nom_simulation=" << s.nom_simulation);
    WARNING("appel de recast_final_initial");
    etat_initial.recast_final_initial(s);
}

void ExperienceValues::set_etat_initial(const SimulationValues& final,double echeance)
{
    while (!sv.empty()) {
	pop_back_simulation();	
    }
    calcul_indices(echeance);
    WARNING("appel de recast_final_initial");
    etat_initial.recast_final_initial(final);
}

// écrit la simulation à enregistrer dans un fichier sous forme d'état finalont le nom est choisi par l'utilisateur.
void ExperienceValues::enregistre_etat_final(std::string filename,int numero)
{
    ofstream ofs(filename.c_str()); 
    ofs << *sv[numero];
    ofs.close();
}

void ExperienceValues::push_back_simulation(){
    sv.push_back(new SimulationValues(etat_initial));
    sv.back()->nom_simulation = SimulationValues::generate_name();
}
void ExperienceValues::pop_back_simulation(){
    delete sv.back();
    sv.pop_back();
}

ExperienceValues::~ExperienceValues() {
    while (!sv.empty()) {
	pop_back_simulation();	
    }
}


// subroutine de calcul de temps_elem, indice_min et indice_max, en fonction de current_values.echeance_value
// !!! cam, le 2 juillet 2006
//
void ExperienceValues::calcul_indices(double nouvelle_echeance){
    echeance_value=nouvelle_echeance;
    if (echeance_value<=100) {
	indice_max_priv=int(echeance_value);
	temps_elem_priv=1.;
	indice_min_priv=-99;
    }

    else {
	temps_elem_priv=echeance_value/100.;
	indice_max_priv=100;
	indice_min_priv=-int(100./temps_elem_priv);
    }	
}

void ExperienceValues::set_graph_displayed(int id,int value)
{
    GraphShown* gs=0;
    switch(id)
    {
	case 1:
	    gs=&graphe_one_displayed;
	    break;
	case 2:
	    gs=&graphe_two_displayed;
	    break;
	case 3:
	    gs=&graphe_three_displayed;
	    break;
	case 4:
	    gs=&graphe_four_displayed;
	    break;
	default:
	    PLANTE("bad index");
    }
    *gs=value;
}

GraphShown ExperienceValues::graph_displayed(int id) const
{
    switch(id)
    {
	case 1:
	    return graphe_one_displayed;
	case 2:
	    return graphe_two_displayed;
	case 3:
	    return graphe_three_displayed;
	case 4:
	    return graphe_four_displayed;
	default:
	    PLANTE("bad index");
    }
    return ALBEDO;
}

ExperienceValues::ExperienceValues() {}
