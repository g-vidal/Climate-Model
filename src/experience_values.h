#ifndef EXPERIENCE_VALUES_H
#define EXPERIENCE_VALUES_H
#include <string>
#include <vector>
#include "graphe_shown.h"
#include "simulation_values.h"
#include <cstdlib>

class ExperienceValues
{
    private:
	SimulationValues etat_initial;
        std::vector<SimulationValues* > sv;

	    //etat
	    double echeance_value;
	    double temps_elem_priv;
	    int indice_min_priv;
	    int indice_max_priv;

    	    // graphe_choser_dialog
	    GraphShown graphe_one_displayed;
	    GraphShown graphe_two_displayed;
	    GraphShown graphe_three_displayed;
	    GraphShown graphe_four_displayed;

    public:
	    void calcul_indices(double nouvelle_echeance);
    public:
	    inline const double& temps_elem() const {return temps_elem_priv;}
	    inline const int& indice_min() const {return indice_min_priv;}
	    inline const int& indice_max() const {return indice_max_priv;}
	    inline const double& annee_debut() const {
		return etat_initial.annee_debut;}

	    //renvoie la derniere SimulationValue
	    inline SimulationValues& back() {return *sv.back();}
	    inline const SimulationValues& back() const {return *sv.back();}
	    //accede (en lecture) a une simulation par index
            inline int nb_simulations() const {return sv.size();}
            inline const SimulationValues& get_simulation(const int& i) const 
	    {
		return *sv[i];
	    }

	    //appelé avant d'ouvrir la fenetre de choix des 
	    //paramètres
	    void push_back_simulation();

	    //appelé en cas de cancel dans les choix des 
	    //parametres
	    void pop_back_simulation();

	    //type de graphe affiche
	    GraphShown graph_displayed(int id) const;
	    void set_graph_displayed(int id,int value);


    public:
	    ExperienceValues();

	    //lit l'etat initial depuis le fichier
	    void set_etat_initial(std::string filename,double echeance);

	    //lit l'etat initial depuis cette simulation
	    void set_etat_initial(const SimulationValues& input_as_final,
		    double echeance);

	    void enregistre_etat_final(std::string filename,int numero);
	    void enregistre_etat_final(std::string filename);

	    inline const SimulationValues& get_etat_initial() const {
		return etat_initial; }

	    //destructeur
	    ~ExperienceValues();

	    //constructeur de copie et d'affectation
	    inline ExperienceValues(const ExperienceValues& e)
	    {
		std::cerr << "interdit de copier ExperienceValue" << std::endl;
		abort();
	    }
	    inline ExperienceValues& operator=(const ExperienceValues& e)
	    {
		std::cerr << "interdit de copier ExperienceValue" << std::endl;
		abort();
		return *this;
	    }

};


#endif //EXPERIENCE_VALUES_H



