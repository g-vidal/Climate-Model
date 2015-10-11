#include "globals.h"
#include "modele_consts_physique.h"
#include "exceptions.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include "graph_designer.h"
using namespace std;

int main() 
{

    // SORTIE("modele_test 10: début de main");

    // SORTIE("modele_test 17: appel de set_etat_initial");
    //set_etat_initial(fichier,echeance)
    // experience_values.set_etat_initial(create_etat_1750(),1e5);

    //Simulation de 2001 à 2100
    experience_values.set_etat_initial(create_etat_2001(),100);

    


    experience_values.push_back_simulation();
    // SORTIE("modele_test 21: annee_debut="<<experience_values.annee_debut());

    {
	SimulationValues& sv = experience_values.back();
	const ModeleConstants& mc = modele_constants;
	sv.fixed_eau=1;	
	sv.fixed_concentration=0;		
	sv.debranche_biologie=1;	
	sv.fixed_ocean=1;	
	sv.debranche_ocean=1;
	sv.fixed_albedo=0;
	//sv.rapport_H2O_value=1.;	
	sv.puit_bio_value=mc.puit_bio_reset_value;
	sv.puit_oce_value=mc.puit_ocean_reset_value;
	//sv.albedo_value=albedo_actuel*100;
	//sv.coo_concentr_value=concentration_coo_actuel;
	sv.puissance_soleil_value=mc.puissance_soleil_reset_value;
	sv.distance_ts_value=mc.distance_ts_reset_value;
	sv.obliquite_value=mc.obliquite_reset_value;
	sv.excentricite_value=mc.excentricite_reset_value;
	sv.precession_value=mc.precession_reset_value;
	sv.alteration_value=mc.alteration_reset_value;
	// GIEC: passer ici un tableau
	//sv.emit_anthro_coo_value=8;
	sv.volcan_value=mc.volcan_reset_value;
	//sv.stockage_biologique_value=-stockage_max*0.001;
    }
    modele_execute();


    // SORTIE("modele_test 23: simulation 1 terminée");

    //on veut afficher deux tableaux sur un meme graphique
    graph_designer gds;
    gds.add(experience_values.back().temperature_data);
    gds.add(experience_values.back().concentrations_coo_data);
    gds.add(experience_values.back().emissions_coo_data);
    gds.add(experience_values.back().niveau_mer_data);
    gds.add(experience_values.back().niveau_calottes_data);
    gds.add(experience_values.back().albedo_data);
    //on dit au graphe designer que c'est pret et qu'il faut calculer les
    //bornes, les ticks, etc...
    //le 0 des tableaux correspond a l'annee 2007
    gds.pack(experience_values.back().annee_debut);
    cerr << "xticks" << endl;
    for (int i=0;i<gds.nbxtick();i++)
	cerr << i << "\t" 
	    << gds.xtickpercent(i) << "\t" 
	    << gds.xtickvalue(i) << "\t" 
	    << gds.xticklabel(i) << endl;
    cerr << "yticks" << endl;
    for (int i=0;i<gds.nbytick();i++)
	cerr << i << "\t" 
	    << gds.ytickpercent(i) << "\t" 
	    << gds.ytickvalue(i) << "\t" 
	    << gds.yticklabel(i) << endl;

    // // SORTIE pour gnuplot dans gnuplot.txt
    // SORTIE("// SORTIE dans gnuplot.data");
    ofstream ofs("../figs/gnuplot.data");
    for (int i=0;i<100;i++) {
	ofs << gds.xvalue(i/100.) << "\t" 
	    << gds.yvalue(0,i/100.) << "\t" 
	    << gds.yvalue(1,i/100.) << "\t"
	    << gds.yvalue(2,i/100.) << "\t"
	    << gds.yvalue(3,i/100.) << "\t"
	    << gds.yvalue(4,i/100.) << "\t"
	    << gds.yvalue(5,i/100.) << endl;
    }
    ofs.close();

    // SORTIE("modele_test 93: nouvelle simulation");	
    gds.clear();
    experience_values.push_back_simulation();
    {
	SimulationValues& sv = experience_values.back();
	const ModeleConstants& mc = modele_constants;
	
	sv.fixed_eau=1;	
	sv.fixed_concentration=1;		
	sv.debranche_biologie=1;	
	sv.fixed_ocean=1;	
	sv.debranche_ocean=1;
	sv.fixed_albedo=0;
	sv.rapport_H2O_value=mc.rapport_H2O_reset_value;	
	sv.puit_bio_value=mc.puit_bio_reset_value;
	sv.puit_oce_value=mc.puit_ocean_reset_value;
	//sv.albedo_value=albedo_actuel*100;
	//sv.coo_concentr_value=concentration_coo_actuel;
	sv.puissance_soleil_value=mc.puissance_soleil_reset_value;
	sv.distance_ts_value=mc.distance_ts_reset_value;
	sv.obliquite_value=mc.obliquite_reset_value;
	sv.excentricite_value=mc.excentricite_reset_value;
	sv.precession_value=mc.precession_reset_value;
	sv.alteration_value=mc.alteration_reset_value;
	//GIEC: Passer ici un tableau (par valeur)
	//sv.emit_anthro_coo_value=0;
	sv.volcan_value=mc.volcan_reset_value*10;
	sv.stockage_biologique_value=-stockage_max;
    }
    modele_execute();
    // SORTIE("modele_test 98: simulation 2 terminée");

    //on veut afficher deux tableaux sur un meme graphique
    gds.add(experience_values.back().temperature_data);
    gds.add(experience_values.back().concentrations_coo_data);
    gds.add(experience_values.back().emissions_coo_data);
    gds.add(experience_values.back().niveau_mer_data);
    gds.add(experience_values.back().niveau_calottes_data);
    gds.add(experience_values.back().albedo_data);
    gds.pack(experience_values.back().annee_debut);
    // SORTIE("SORTIE dans gnuplot2.data");
    ofs.open("../figs/gnuplot2.data");
    for (int i=0;i<100;i++) {
	ofs << gds.xvalue(i/100.) << "\t" 
	    << gds.yvalue(0,i/100.) << "\t" 
	    << gds.yvalue(1,i/100.) << "\t"
	    << gds.yvalue(2,i/100.) << "\t"
	    << gds.yvalue(3,i/100.) << "\t"
	    << gds.yvalue(4,i/100.) << "\t"
	    << gds.yvalue(5,i/100.) << endl;
    }
    ofs.close();


    //tracé des graphes
    // SORTIE("tracer des graphes: taper:");
    // SORTIE("gnuplot ../figs/gnuplot.plot")

}

