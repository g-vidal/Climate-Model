#ifndef modele_constantes_h
#define modele_constantes_h
#include "cmath"

 // définition de constantes du modèle en lui-meme
 // cam, fin juin 2006 

// fonction de calcul de indice_min, indice_max et temps_elem:
void modele_calculindices();

// **constantes mathématiques
const double pi=M_PI;

// **constantes adiatives
const double puissance_recue_zero=1370/4.;
const double distance_ts_actuelle=1.5e11;
const double sigma=5.67e-8;

// constantes du calcul de l'albédo
const double albedo_froid=0.65;
const double albedo_chaud=0.325;
const double temperature_froid=262;
const double temperature_chaud=286;

extern double fin_chaud,fin_froid; // à supprimer

// constantes des GES
// 
// * conversions de Gt à ppm:
const double masse_atmosphere_Gt= 1.4e6;//5.13e6; //en Gt
const double masse_molaire_coo=44; // g/mol
const double masse_molaire_chhhh=16;
const double masse_molaire_air=29;

// * concentrations actuelles et naturelles
const double concentration_coo_actuel=370;
const double concentration_coo_1750=280;
const double concentration_coo_naturel=280;
const double concentration_coo_min=1e-1; // pour ne pas avoir de nan en prenant le log
const double coo_Gt_act=750; //masse de CO2 en Gt
const double concentration_coo_glaciaire=180; //ppm

// * constantes radiatives
//const double a_coo=13.7e-3;//5.35;
const double a_coo=18e-3;//5.35;
const double concentration_coo_limite=10000; //en ppm, la limite entre relation linéaire et log pour forcage serre
	// pour extrapolations lin pour hautes concentrations
const double concentration_coo_limite_bas=100; //en ppm,idem pour extrapolation pour basses concnetrations

const double G_min=1e-4; // forcage_serre min, pour eviter des nan

// * temps de résidence
const double t_res_coo_actuel=280/0.083/(concentration_coo_actuel/coo_Gt_act);
	// on calcul tel qu'a l'auilibre, sans emissions humaines, concentration en C02=emission*temps de résidence=280ppm
const double t_res_coo_90=t_res_coo_actuel*0.9;
const double t_res_coo_0=1.5e6;
const double niveau_calotte_critique_coo=20;
const double niveau_calottes_1750=60;	
const double t_res_coo_critique=t_res_coo_90
	+(90-niveau_calotte_critique_coo)*-(t_res_coo_90-t_res_coo_actuel)/(90-niveau_calottes_1750);
//const double facteur_alteration_0=1e-3;	
//const double facteur_alteration_90=1;	


// températures
const double tau_temperature=30; // en années
//const double temperature_actuelle=15.5722; // en °C // necessaire dans modele_reset
const double temperature_actuelle=15.3; 
// calculée à la main pour C02=370 et albédo=albédo_actuel
const double deltaT_last_century=0.8;
const double temperature_1900=temperature_actuelle-deltaT_last_century; // en °C // necessaire dans modele_reset
const double temperature_1750=14.4; 
const double temperature_LGM=10;
const double C_terre=5e9; // capacité calorifique de la Terre en J/K/m2

// données radiatives sur l'actuel
const double albedo_1750=0.33;
const double G0=puissance_recue_zero*(1-albedo_1750)/sigma/exp(4*log(273+temperature_1750)); //0.584;

// données et constantes de bidouille sur le niveau de la mer
const double p0=1.; // facteur de pondération de la température il y a deltat0 ans
const double p1=5.;
const double p2=3.;
const double p3=1.;
const double deltat0=0.; // retard en temps en année 
const double deltat1=5.;
const double deltat2=20.;
const double deltat3=50.;
const double C_niveau=100.; // orig=96
const double a_mer=140;
const double tau_niveau_mer=500.; //orig:40
const double T_ressentie_actuelle=(1./(p0+p1+p2+p3))*(p0*temperature_actuelle
						+p1*temperature_actuelle-deltaT_last_century/100*deltat1
						+p2*temperature_actuelle-deltaT_last_century/100*deltat2
						+p3*temperature_actuelle-deltaT_last_century/100*deltat3);
// niveau mer exprimé en m /t actuel
const double niveau_mer_LGM=-130;
const double niveau_mer_1750=-0.2; //en m


// niveau des calottes
const double niveau_calottes_LGM=45;
const double niveau_calottes_LGM_noinsol=52;
const double tau_niveau_calottes_englacement=4000.;
const double tau_niveau_calottes_deglacement=4000.;
const double a_calottes=(niveau_calottes_1750-niveau_calottes_LGM_noinsol)/(temperature_1750-temperature_LGM)*0.8; // on suppose qu'une partie de la variation du niveau de calotte est liÃ© Ã  l'effet de la tempÃ©rature (ici 40%), et l'autre est liÃ©e Ã  l'effet de la variation d'insolation.
// Une variation globale glaviaire-interglaciaire correspond Ã  environ 5 Ã  10Â°C.
const double b_calottes=niveau_calottes_1750-a_calottes*temperature_1750;	 
const double niveau_calottes_min=0;
const double niveau_calottes_max=90;
const double niveau_calottes_actuel=niveau_calottes_1750+(a_calottes*(temperature_actuelle)+b_calottes-niveau_calottes_1750)*(1-exp(-100/tau_niveau_calottes_deglacement));

// nouveau traitement niveau de la mer:
const double Hmer_tot=3.8e3; // en m
const double dilat=2.4e-4; //en /°C
const double Tressentie_act=temperature_actuelle-0.7; // orig -0.75
// const double fphig1=0.521e-3;
// const double fphig2=9.016e-5;
// const double fphig3=-2.76e-7;
const double fphig1=0.0;
const double fphig2=0.10e-4;
const double fphig3=-2e-7;
	// tel que l'on soit à l'équilibre à niveau_mer_1750 en 1750
	// et tel que -120m au LGM
	
const double Hmeract=Hmer_tot*(1
		- fphig1*(niveau_calottes_actuel-niveau_calottes_max)
		- fphig2*pow(niveau_calottes_actuel-niveau_calottes_max,2)
		- fphig3*pow(niveau_calottes_actuel-niveau_calottes_max,3));

//* flux de carbone
//const double CO2_biologique_eq=concentration_coo_naturel;
// calcul CO2_ocean_eq en fonction température
const double a_CO2_eq=20; //ppm/°C		
const double emit_anthro_coo_act=8; //GT
const double volcanisme_actuel=0.083; //en Gt/an
const double puit_ocean_act=20.0; // en fraction des emissions anthro absorbées
//const double B_ocean=-puit_ocean_act*emit_anthro_coo_act/
//	(concentration_coo_actuel-concentration_coo_1750
//	 	-a_CO2_eq*(temperature_actuelle-temperature_1750));
const double C_alteration_naturel=-volcanisme_actuel/concentration_coo_1750;	
const double Tlim_oce=10; // en °K
//const double rel_CO2_temperature=emit_anthro_coo_act/Tlim_oce;
const double b_ocean=1/5000.0;
const double Tlim_oce_froid=275;
const double A_oce=3e-2;
const double deltaT_poce=0.5/A_oce;
const double Tcrit_oce=35;
const double puit_oce_max=40;
const double dFdegaz=0.05;
const double q_CO2=0.26; // CO2=26% de l'effet de serre

//* retroactions vapeur d'eau
const double q_H2O=0.6; // eau=60% de l'effet de serre
const double a_H2O=-q_H2O*(1-G0);
const double tau_T=200; //en K
const double rapport_H2O_actconst=1.05719; // rapport pour la température actuelle
const double a_rankine=13.7;
//const double b_rankine=5120.; // valeur standard
//const double pow_H2O=0.18; // valeur standard
const double b_rankine=5120.;
const double pow_H2O=0.23; // normallement: 0.18

// paramétrisation de A_biologique en fonction 	de la température
const double puit_bio_act=35; // en pourcent
const double Tlim_bio_froid=temperature_froid;
const double Tlim_bio_chaud=340; // en K
//const double A_biologique_act=-puit_bio_act*emit_anthro_coo_act
//		/(concentration_coo_actuel-concentration_coo_1750); // en an-1

//** parametres orbitaux
const double lat_Mil=65;
const double c_calottes=0.2;
//const double precession_actuel=-90;
const double precession_actuel=102.7; // modif 31 janv 2009: on prend la même precession que LMDZ
// la formule de insol65N n'a pas été modifiée car 2 bugs se compensaient
const double obliquite_actuel=23.5;
const double excentricite_actuel=0.0167;
const double delta_angle_actuel=(lat_Mil-obliquite_actuel)/360*2*pi;
const double insol_actuel=puissance_recue_zero*cos(delta_angle_actuel);

//** albédo
const double albedo_phi_min=0.60;
const double albedo_phi_max=0.2;
const double albedo_glace_const=0.90;
const double phig_crit=30.0; //30
const double albedo_ter=0.25;
const double albedo_crit=(albedo_1750-albedo_ter*
	(niveau_calottes_1750-phig_crit)/(niveau_calottes_max-phig_crit))
    	/(1-(niveau_calottes_1750-phig_crit)/(niveau_calottes_max-phig_crit)); //0.41
//const double albedo_actuel=albedo_crit
//			+(niveau_calottes_actuel-phig_crit)/(niveau_calottes_max-phig_crit)
//			*(albedo_ter-albedo_crit);	
//const double albedo_actuel=0.327;
const double albedo_actuel=albedo_crit
		    +(niveau_calottes_actuel-phig_crit)/(niveau_calottes_max-phig_crit)
		    *(albedo_ter-albedo_crit);

//	const double albedo_ter=
//	(albedo_actuel-albedo_glace_const*(1-sin(niveau_calottes_actuel/180*pi)))
//    	/sin(niveau_calottes_actuel/180*pi); //=0.2571

//** calcule de la température
const double capacite_calorifique=0.1;	

//* stockage biologique
const double flux_co2_stockage_max=-10; //GT/an-1
const double stockage_max=flux_co2_stockage_max/concentration_coo_1750;
const double flux_co2_stockage_carbonifere=-0.396; // en Gt par an d'apres R.A. Berner et D.E. Canfield (1989)
const double concentration_coo_carbonifere=concentration_coo_1750;
const double stockage_carbonifere=flux_co2_stockage_carbonifere/concentration_coo_carbonifere;

//* logicals
//
const int echantillonage=1;
	//if 1: echantillonage direct au pas de temps
	//if 2: echantillonage en moyennant sur les pas de temps autour du point d'échantillonage
	
const int calcul_carbone=1;
	// si 1: calcul Euler explicite
	// si 2: calcul par decroissance vers équilibre


 #endif //modele_constantes.h
