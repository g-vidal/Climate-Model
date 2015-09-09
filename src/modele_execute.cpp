#include "globals.h"
#include "modele_consts_physique.h"
#include "exceptions.h"
#include "cmath"
#include <iostream>
#include <iomanip>
using namespace std;

// calcul les tableaux globaux d'évolution du climat:
// * concentrations_gaz_data
// * temperature_data !!! en Kelvin
// necessite en entrée:
// * emissions_gaz_data ou concentrations_gaz_data
// * indice_max
// * temps_elem

// cam, 3 juillet 2006
//modifs le 13 juillet
//
// declarations des subroutines:

int modele_execute(){
    SimulationValues& s=experience_values.back();
    SORTIE("modele_execute 22: entrée dans execute");
    // ** declarations
    // * pour l'integration temporelle
    int oscillation;
    double zT,zT_ancien, zT_ancien_prec;	// température
    double zCO2, zCO2_ancien, zCO2_ancien_prec; // CO2
    double zphig,zphig_ancien, zphig_ancien_prec; // niveau calotte
    double zT_moy,zCO2_moy,zphig_moy;
    double zT_moy1,zCO2_moy1,zphig_moy1;
    double zT_moy2,zCO2_moy2,zphig_moy2;
    double zT_moy2save,zCO2_moy2save,zphig_moy2save;
    double zTeq;
    double zsomme_flux;
    int niter;
    int nmid;
    double dt;
    // * variables intermédiaires
    double G;
    //double phieq;
    //double tau_niveau_calottes;
    //double Teq;
    double alteration_max;
    double zC_alteration;
    double zC_stockage;
    double forcage_serre_eau;
    double forcage_serre_CO2;
    double forcage_serre;
    //double zA_biologique;
    double zB_ocean;
    //double zCO2_ocean_eq;
    double zalbedo;
    double Fin0, insol65N;
    double emission_coo_ppm;
    double zrapport_H2O;
    double delta_angle;	
    double Fin, Fout;
    //double Foce, Fbio;
    double zpuit_oce, zpuit_bio;
    double phieq;
    double tau_niveau_calottes;
    double zCO2eq, tau_CO2_eq;
    double zCO2eq_oce;
    double B_ocean;
    double Fdegaz;
    double zsomme_flux_const, zsomme_C;
    //double poce,poce_prec;
    //* declaration des fonctions
    double calcul_zA_biologique(double zT, double A);
    //double calcul_zCO2_ocean_eq(double zT);
    double calcul_forcage_serre_CO2(double zCO2);
    double calcul_forcage_serre_H2O(double zrapport_H2O);
    double calcul_rapport_H2O(double zT);
    double calcul_phieq(double zT,double insol65N);
    double calcul_albedo(double zphig);
    double calcul_zC_alteration(double Cmax, double zphig);
    double calcul_niveau_mer(double niveau_mer_ancien,double zphig, double zphig_ancien, int t);
    double calcul_niveau_mer_new(double zphig, double zT, int t);
    double calculT(double vareq, double varprec, double tau, double dt);
    double calcul_tau_niveau_calottes(double zphieq,double zphieq_ancien);
    double abs(double x);
    double calcul_zCO2eq(double zT);
    //double calcul_poce(double zT);
    double calcul_zpuit_oce(double zT);
    double calcul_Fdegaz(double zT);



    // ** end declarations

    SORTIE("");
    // prend en compte la nouvelle echeance et calcul indiciation des tableaux
    niter=max(4,int(3*exp(0.3*log(experience_values.temps_elem()))));
    nmid=int(niter/2.+0.5);
    SORTIE("niter="<<niter);
    dt=experience_values.temps_elem()/double(niter);    
    SORTIE("dt="<<dt);

    // remplit les tableaux des emissions de GES ou leurs concentration à partir des params de l'interface
    //if (current_values.simulation_type==FIXED_CONCENTRATIONS){
    SORTIE("fixed_concentration="<<s.fixed_concentration);
    if (s.fixed_concentration) {
	SORTIE("fixed_concentration");
	// on remplit les tableaux de concentrations de GES entre 1 et indice_max
	for (int t=0;t<=experience_values.indice_max();t++){
	    s.concentrations_coo_data[t]=s.coo_concentr_value; // en ppm
	    //SORTIE("t="<<t);
	    zCO2=s.coo_concentr_value;

	    forcage_serre_CO2=calcul_forcage_serre_CO2(zCO2);
	    s.emissions_coo_data[t]=0.;
	}
	SORTIE("zCO2="<<zCO2);
	SORTIE("concentrations_coo_data[1]="<<s.concentrations_coo_data[1]);

    } //endif if (current_values.simulation_type==FIXED_CONCENTRATIONS){

    else { //endif if (current_values.simulation_type==FIXED_CONCENTRATIONS){
	if (s.debranche_biologie) {
	    //zA_biologique=0.;
	    zpuit_bio=0;
	}
	else {
	    //zA_biologique=current_values.A_biologique;
	    zpuit_bio=s.puit_bio_value/100.0;
	}
	if (s.debranche_ocean) {
	    //zB_ocean=0;
	    //zCO2_ocean_eq=concentration_coo_1750;
	    zpuit_oce=0;	

	}
	else {
	    //zB_ocean=current_values.B_ocean;
	    zpuit_oce=s.puit_oce_value/100.0;
	    if (s.fixed_ocean) {
		B_ocean=0;		
	    }
	    else {
		B_ocean=b_ocean;
	    }	    
	}
    } //endif if (current_values.simulation_type==FIXED_CONCENTRATIONS){
    SORTIE("modÃ¨le_excecute 146: zpuit_oce="<<zpuit_oce);
    SORTIE("modÃ¨le_excecute 146: zpuit_bio="<<zpuit_bio);


    // attribution de variables dans le cas où elles sont en mode fixé:
    // les variables précédées de z sont celles qui sont calculées aussi bien dans les cas
    // avec et sans rétroaction

    SORTIE("fixed_eau="<<s.fixed_eau);
    if (s.fixed_eau) {
	forcage_serre_eau=calcul_forcage_serre_H2O(s.rapport_H2O_value/100.0);
    }	    

    if (s.fixed_albedo) {
	zalbedo=s.albedo_value/100.; // conversion albedo en % en albedo en unité
	for (int t=0;t<=experience_values.indice_max();t++){	
	    s.albedo_data[t]=s.albedo_value;
	}
    }
    else {
	s.albedo_data[0]=calcul_albedo(s.niveau_calottes_data[0])*100.;
    }



    Fin0=puissance_recue_zero*(s.puissance_soleil_value/100.)
	/(s.distance_ts_value/100)
	/(s.distance_ts_value/100);
    delta_angle=abs(lat_Mil-s.obliquite_value)/360*2*pi;
    insol65N=Fin0	    
	*cos(delta_angle)
	*exp(2*log((1-excentricite_actuel*0.5*sin(-precession_actuel/180*pi))
		    /(1-(0.3*s.excentricite_value+0.7*excentricite_actuel)*0.5*sin(-s.precession_value/180*pi))));
    //		    /(1-s.excentricite_value*0.5*sin(s.precession_value/180*pi))));
    //		    on fait une bidouille pour réduire l'éffet de l'excentricité.


    SORTIE(" ");
    SORTIE("Fin0="<<Fin0);
    SORTIE("Fin0*cos(delta_angle)="<<Fin0*cos(delta_angle));
    SORTIE("delta_angle_actuel="<<delta_angle_actuel);
    SORTIE("delta_angle="<<delta_angle);
    SORTIE("puissance_recue_zero="<<puissance_recue_zero);
    SORTIE("insol65N="<<insol65N);
    SORTIE("insol_actuel="<<insol_actuel);
    SORTIE("G0="<<G0);
    SORTIE("albedo_actuel="<<albedo_actuel);
    SORTIE("niveau_calottes_actuel="<<niveau_calottes_actuel);


    // mettons toutes les températures de indice_min à 0 en K:
    for (int t=experience_values.indice_min();t<=0;t++){
	s.temperature_data[t]=s.temperature_data[t]+273;
    }
    // mettons les albédo entre 0 et 1


    // variables nécessaires pour intégration temporelle:


    zT_ancien=s.temperature_data[0];
    zT_ancien_prec=zT_ancien;
    zCO2_ancien=s.concentrations_coo_data[0];
    zCO2_ancien_prec=zCO2_ancien;
    zphig_ancien=s.niveau_calottes_data[0];

    // intégration temporelle
    for (int t=1;t<=experience_values.indice_max();t++){

	SORTIE(" ");
	SORTIE("**** boucle d'integration, t="<<t);
	oscillation=0;

	SORTIE("s.temperature_data[t-1]="<<s.temperature_data[t-1]);	
	SORTIE("zT_ancien="<<zT_ancien);

	zT_moy1=0.;
	zCO2_moy1=0.;
	zphig_moy1=0.;
	zT_moy2=0.;
	zCO2_moy2=0.;
	zphig_moy2=0.;	

	for (int iter=1;iter<=niter;iter++) {
	    SORTIE("**boucle d'integration, iter="<<iter);
	    //if (current_values.simulation_type==FIXED_EMISSIONS) {
	    if (!s.fixed_concentration) {
		// *calculs des flux de CO2

		SORTIE("zphig_ancien="<<zphig_ancien);
		alteration_max=C_alteration_naturel*(s.alteration_value/100.);
		zC_alteration=calcul_zC_alteration(alteration_max,zphig_ancien);
		SORTIE("zC_alteration="<<zC_alteration);
		ASSERT(zC_alteration<=0);
		zC_stockage=calcul_zC_alteration(-s.stockage_biologique_value*1e-3,zphig_ancien);
		SORTIE("zC_stockage="<<zC_stockage);
		ASSERT(zC_stockage<=0);
		Fdegaz=0.;
		zB_ocean=calcul_zC_alteration(B_ocean,zphig_ancien);

		if ((!s.debranche_ocean)&&(!s.fixed_ocean)) {
		    zpuit_oce=calcul_zpuit_oce(zT_ancien);
		    ASSERT(zpuit_oce>=0.);
		    ASSERT(zpuit_oce<=puit_oce_max);
		    Fdegaz=calcul_Fdegaz(zT_ancien);
		}
		
				
		SORTIE("modÃ¨le_excecute 254: zB_ocean="<<zB_ocean);
		SORTIE("modÃ¨le_excecute 254: zpuit_oce="<<zpuit_oce);
		SORTIE("modÃ¨le_excecute 254: zpuit_bio="<<zpuit_bio);
		SORTIE("modÃ¨le_excecute 254: Fdegaz="<<Fdegaz);
		SORTIE("modÃ¨le_excecute 254: zCO2_ancien="<<zCO2_ancien);

		// ** calculs des emissions en Gt/an
		SORTIE("s.emit_anthro_coo_value="<<s.emit_anthro_coo_value);
		SORTIE("s.volcan_value="<<s.volcan_value);
		SORTIE("zC_alteration*zCO2_ancien="<<zC_alteration*zCO2_ancien);		
		SORTIE("zC_stockage*zCO2_ancien="<<zC_stockage*zCO2_ancien);
		SORTIE("zpuit_oce="<<zpuit_oce);

		zCO2eq_oce=calcul_zCO2eq(zT_ancien);
		SORTIE("zCO2eq_oce="<<zCO2eq_oce);

		// attention, on met des min et max pour Ã©viter les pbs.
		zsomme_flux_const=max(min(1.0-zpuit_oce-zpuit_bio,1.0),0.0)*
		    (s.emit_anthro_coo_value
		     +s.volcan_value)
		     +max(min(1-zpuit_bio,1.0),0.0)*zB_ocean*zCO2eq_oce
		     +Fdegaz;
		zsomme_C=max(min(1-zpuit_oce-zpuit_bio,1.0),0.0)*(zC_alteration+zC_stockage)
		    -max(min(1-zpuit_bio,1.0),0.0)*zB_ocean;
		SORTIE("zsomme_flux_const="<<zsomme_flux_const);
		SORTIE("zsomme_C="<<zsomme_C);		
		ASSERT(zsomme_flux_const>=0);
		ASSERT(zsomme_C<=0);

		zsomme_flux=zsomme_flux_const+zCO2_ancien*zsomme_C;
		SORTIE("zsomme_flux="<<zsomme_flux);


		if (calcul_carbone==1) {
		    // ** calcul concentration en CO2
		    SORTIE("méthode Euler:")
		    emission_coo_ppm=zsomme_flux*(concentration_coo_actuel/coo_Gt_act); //en ppm/an
		    SORTIE("zCO2_ancien="<<zCO2_ancien);
		    SORTIE("emission_coo_ppm="<<emission_coo_ppm);
		    SORTIE("dt="<<dt);
		    zCO2=zCO2_ancien+emission_coo_ppm*dt;
		    zCO2=max(0.0,zCO2);
		    SORTIE("zCO2="<<zCO2);
		}

		else if (calcul_carbone==2) {
		    //** calcul par zCO2eq: méthode directe:
		    if (zsomme_C>0) {
			SORTIE("méthode equilibre: cas general")
		    zCO2eq=-zsomme_flux_const/zsomme_C;
		    tau_CO2_eq=-1./zsomme_C;
		    SORTIE("zCO2eq="<<zCO2eq);
		    SORTIE("tau_CO2_eq="<<tau_CO2_eq);
		    zCO2=calculT(zCO2eq,zCO2_ancien,tau_CO2_eq,dt);
		    ASSERT(zCO2>=0.);
		    SORTIE("zCO2="<<zCO2);
		    }
		    else
		    {
			SORTIE("méthode equilibre: cas zsomme_C>O");
			SORTIE("emission_coo_ppm="<<emission_coo_ppm);
			emission_coo_ppm=zsomme_flux_const*(concentration_coo_actuel/coo_Gt_act);
			zCO2=zCO2_ancien+emission_coo_ppm*dt;
			ASSERT(zCO2>=0.);
		    	SORTIE("zCO2="<<zCO2);
		    }
		}



		// **calcul de l'effet de serre en t
		SORTIE("calcul de l'effet de serre");

		forcage_serre_CO2=calcul_forcage_serre_CO2(zCO2);
	    } //if (current_values.simulation_type==FIXED_EMISSIONS) {

	    if (!s.fixed_eau) {
		zrapport_H2O=calcul_rapport_H2O(zT_ancien);
		forcage_serre_eau=calcul_forcage_serre_H2O(zrapport_H2O);
	    }		    	

	    forcage_serre=forcage_serre_CO2+forcage_serre_eau;
	    G=G0-forcage_serre;
	    if (G<G_min) {
		G=G_min;
	    }
	    if (G>1) {
		G=1;
	    }

	    SORTIE("forcage_serre="<<forcage_serre);
	    SORTIE("G="<<G);

	    //** calcul de la latitude de glace


	    phieq=calcul_phieq(zT_ancien,insol65N);
	    SORTIE("calcul_phig: zphig_ancien="<<zphig_ancien);
	    tau_niveau_calottes=calcul_tau_niveau_calottes(phieq,zphig_ancien);

	    SORTIE("calcul_phig: dt="<<dt);			
	    zphig=calculT(phieq,zphig_ancien,tau_niveau_calottes,dt);
	    zphig=min(max(0.0,zphig),90.0);
	    SORTIE("calcul_phig: zphig="<<zphig);
	    SORTIE("zphig="<<zphig);

	    //** calcul de l'albédo
	    SORTIE("fixed_albedo="<<s.fixed_albedo);
	    if (!s.fixed_albedo) {
		SORTIE("calcul_albedo: albedo_ter="<<albedo_ter);
		zalbedo=calcul_albedo(zphig);
	    }
	    SORTIE("zalbedo="<<zalbedo);

	    //** déduction de la température

	    //Teq=exp(0.25*log(Fin0*(1-zalbedo)/G/sigma));
	    //zT=Teq;		
	    //zT=calculT(Teq,temperature_data[t-1],tau_temperature,temps_elem);
	    Fin=Fin0*(1-zalbedo);		
	    Fout=G*sigma*exp(4*log(zT_ancien));
	    SORTIE("zT_ancien="<<setprecision(8)<<zT_ancien);
	    SORTIE("Fin="<<setprecision(8)<<Fin);
	    SORTIE("Fout="<<setprecision(8)<<Fout);

	    //zT=zT_ancien+min(max(capacite_calorifique*(Fin-Fout)*dt,-100.),100.);
	    zTeq=exp(0.25*log(Fin/(G*sigma)));
	    SORTIE("zTeq="<<setprecision(8)<<zTeq);
	    zT=calculT(zTeq,zT_ancien,tau_temperature,dt);
	    zT=max(0.0,min(1e6,zT));
	    SORTIE("dT="<<setprecision(8)<<capacite_calorifique*(Fin-Fout)*dt);
	    SORTIE("zT="<<setprecision(8)<<setprecision(8)<<zT);
	    SORTIE("zT_ancien="<<setprecision(8)<<zT_ancien);
	    SORTIE("zT_ancien_prec="<<setprecision(8)<<zT_ancien_prec);

	    // fin des calculs
	    if ((iter>=3) && (oscillation==0)) {
		if (zT_ancien<zT_ancien_prec) {
		    if (zT>zT_ancien) { oscillation=1; }
		}
		else if (zT_ancien>zT_ancien_prec) {
		    if (zT<zT_ancien) { oscillation=1; }
		} 
	    }
	    //if (current_values.simulation_type==FIXED_EMISSIONS) {
	    if (!s.fixed_concentration) {
		if ((iter>=3) && (oscillation==0)) {
		    if (zCO2_ancien<zCO2_ancien_prec) {
			if (zCO2>zCO2_ancien) { oscillation=1; }
		    }
		    else if (zCO2_ancien>zCO2_ancien_prec) {
			if (zCO2<zCO2_ancien) { oscillation=1; }
		    } 
		}
	    } //if (current_values.simulation_type==FIXED_EMISSIONS) {
	    SORTIE("oscillation="<<oscillation);
	    if (oscillation==1) {
		zT=(zT+zT_ancien+0.5*zT_ancien_prec)/2.5;
		//if (current_values.simulation_type==FIXED_EMISSIONS) {
		if (!s.fixed_concentration) {
		    zCO2=(zCO2+zCO2_ancien+0.5*zCO2_ancien_prec)/2.5;
		}
		zphig=(zphig+zphig_ancien+0.5*zphig_ancien_prec)/2.5;	
	    }
	    zCO2_ancien_prec=zCO2_ancien;
	    zT_ancien_prec=zT_ancien;
	    zphig_ancien_prec=zphig_ancien;
	    zT_ancien=zT;
	    zCO2_ancien=zCO2;
	    zphig_ancien=zphig;				    

	    if (echantillonage==2) {
		if (iter<=nmid) {
		    zT_moy1=zT_moy1+zT;
		    zCO2_moy1=zCO2_moy1+zCO2;
		    zphig_moy1=zphig_moy1+zphig;
		}
		else {
		    zT_moy2=zT_moy2+zT;
		    zCO2_moy2=zCO2_moy2+zCO2;
		    zphig_moy2=zphig_moy2+zphig;
		}
	    }


	    } //for (int iter=1;iter<=niter;iter++) {

	    if (echantillonage==1) {
		s.temperature_data[t]=zT;
		SORTIE("s.temperature_data[t]="<<s.temperature_data[t]);
	    }

	    SORTIE("fin de la sous boucle, zT="<<zT);		    

	    if ((echantillonage==2)&&(t>1)) {

		zT_moy=(zT_moy1+zT_moy2save)/double(niter);
		SORTIE("zT_moy="<<zT_moy);
		s.temperature_data[t-1]=zT_moy;	
		SORTIE("s.temperature_data[t-1]="<<s.temperature_data[t-1]);

		if (t==experience_values.indice_max()) {
		    zT_moy=zT;
		    s.temperature_data[t]=zT_moy;
		    SORTIE("s.temperature_data[t]="<<s.temperature_data[t]);
		}
	    }



	    if (!s.fixed_concentration) {

		SORTIE("zCO2="<<zCO2);		        
		if (echantillonage==1) s.concentrations_coo_data[t]=zCO2;

		if (echantillonage==2) {
		    if (t>1) {
			SORTIE("zCO2_moy1="<<zCO2_moy2save);
			SORTIE("zCO2_moy1="<<zCO2_moy2save);
			SORTIE("double(niter)="<<double(niter));			
			zCO2_moy=(zCO2_moy1+zCO2_moy2save)/double(niter);
			SORTIE("zCO2_moy="<<zCO2_moy);			
			s.concentrations_coo_data[t-1]=zCO2_moy; 
			SORTIE("s.concentrations_coo_data[t-1]="<<s.concentrations_coo_data[t-1]);

			if (t==experience_values.indice_max()) {
			    zCO2_moy=zCO2;
			    s.concentrations_coo_data[t]=zCO2_moy;
			}
		    }
		}			


		if (echantillonage==1) {
		    s.emissions_coo_data[t-1]=
			(s.concentrations_coo_data[t]-s.concentrations_coo_data[t-1])
			/experience_values.temps_elem() //en ppm/an
			/(concentration_coo_actuel/coo_Gt_act); // conversion en Gt/an
		}
		else if (echantillonage==2) {
		    s.emissions_coo_data[t-1]=(zCO2_moy2/double(niter-nmid)-zCO2_moy1/double(nmid))
			/experience_values.temps_elem()*2 //en ppm/an
			/(concentration_coo_actuel/coo_Gt_act); // conversion en Gt/an
		    SORTIE("zCO2_moy2="<<zCO2_moy2);
		    SORTIE("zCO2_moy1="<<zCO2_moy1);
		    SORTIE("zCO2_moy2/double(nmid)="<<zCO2_moy2/double(niter-nmid));
		    SORTIE("zCO2_moy1/double(niter-nmid))="<<zCO2_moy1/double(nmid));
		    SORTIE("nmid="<<nmid);
		    SORTIE("niter-nmid="<<niter-nmid);
		}
		SORTIE("emissions_coo_data[t]"<<s.emissions_coo_data[t]);
		SORTIE("concentrations_coo_data[t]"<<s.concentrations_coo_data[t]);
	    }	  

	    SORTIE("zphig="<<zphig);

	    if (echantillonage==1) s.niveau_calottes_data[t]=zphig;

	    if ((echantillonage==2)&&(t>1)) {
		zphig_moy=(zphig_moy1+zphig_moy2save)/double(niter);
		s.niveau_calottes_data[t-1]=zphig_moy;			
		if (t==experience_values.indice_max()) { 
		    zphig_moy=zphig;
		    s.niveau_calottes_data[t]=zphig_moy;
		}
		SORTIE("zphig_moy="<<zphig_moy);
	    }

	    if ((echantillonage==2)&&(t<experience_values.indice_max())) {
		zT_moy2save=zT_moy2;
		zCO2_moy2save=zCO2_moy2;
		zphig_moy2save=zphig_moy2;
	    }


	    if (!s.fixed_albedo) {

		if (echantillonage==1) {s.albedo_data[t]=zalbedo*100.;}
		SORTIE("zalbedo="<<zalbedo);

		if ((echantillonage==2)&&(t>1)) {
		    s.albedo_data[t-1]=calcul_albedo(s.niveau_calottes_data[t-1])*100.;
		    SORTIE("s.albedo_data[t-1]="<<s.albedo_data[t-1]);
		    if (t==experience_values.indice_max()) {
			s.albedo_data[t]=calcul_albedo(s.niveau_calottes_data[t])*100.;
		    }
		}



	    }

	    //** calcul niveau de la mer
	    if (echantillonage==1) {
		//s.niveau_mer_data[t]=calcul_niveau_mer(s.niveau_mer_data[t-1],s.niveau_calottes_data[t],s.niveau_calottes_data[t-1],t);
		s.niveau_mer_data[t]=calcul_niveau_mer_new(s.niveau_calottes_data[t],
			s.temperature_data[t],t);
		SORTIE("s.niveau_mer_data[t]="<<s.niveau_mer_data[t]);
	    }
	    else if ((echantillonage==2)&&(t>1)) {
		//s.niveau_mer_data[t-1]=calcul_niveau_mer(s.niveau_mer_data[t-2],s.niveau_calottes_data[t-1],s.niveau_calottes_data[t-2],t-1);
		s.niveau_mer_data[t-1]=calcul_niveau_mer_new(s.niveau_calottes_data[t-1],
			s.temperature_data[t-1],t);
		SORTIE("s.niveau_mer_data[t-1]="<<s.niveau_mer_data[t-1]);
		if (t==experience_values.indice_max()) {
		    //s.niveau_mer_data[t]=calcul_niveau_mer(s.niveau_mer_data[t-1],s.niveau_calottes_data[t],s.niveau_calottes_data[t-1],t);
		    s.niveau_mer_data[t]=calcul_niveau_mer_new(s.niveau_calottes_data[t],
			s.temperature_data[t],t);
		}
	    }




	} //for (int t=1;t<=indice_max;t++){

	s.emissions_coo_data[experience_values.indice_max()]=s.emissions_coo_data[experience_values.indice_max()-1];


	// met la température en °C
	for (int t=0;t<=experience_values.indice_max();t++){
	    s.temperature_data[t]=s.temperature_data[t]-273;
	}
	// met l'albédo en %
	for (int t=0;t<=experience_values.indice_max();t++){
	    s.albedo_data[t]=s.albedo_data[t];
	}


	return 1;

	}




	// **************** fin de modele execute ***************//

	// *********** fonctions utiles *************//
	//*******************************************//

	double calculT(double Teq, double Tprec, double tau, double dt) {
	    double T;
	    T=Tprec+(Teq-Tprec)*(1-exp(-dt/tau));
	    return T;
	}

	double calcul_forcage_serre_H2O(double zrapport_H2O) {
	    double forcage_serre_H2O;
	    //forcage_serre_H2O=a_H2O*log(zrapport_H2O);
	    SORTIE("calcul_forcage_serre_H2O: zrapport_H2O="<<zrapport_H2O);
	    //forcage_serre_H2O=a_H2O*(1-sqrt(zrapport_H2O));
	    if (zrapport_H2O>0.0) { 		
	    	forcage_serre_H2O=a_H2O*(1-exp(pow_H2O*log(zrapport_H2O)));
	    }
	    else {
		forcage_serre_H2O=a_H2O;
	    }
	    SORTIE("calcul_forcage_serre_H2O: forcage_serre_H2O="<<forcage_serre_H2O);
	    return forcage_serre_H2O;
	}

	double calcul_forcage_serre_CO2(double zCO2) {
	    // ** input
	    //double zCO2;
	    // ** output
	    double forcage_serre_CO2;
	    if (zCO2<concentration_coo_limite_bas) {
		SORTIE("relation linéaire, extrapolation basse");
		//forcage_serre_CO2=a_coo
		//*(log(concentration_coo_limite_bas/concentration_coo_actuel)
		//+zCO2/concentration_coo_limite_bas-1);
		forcage_serre_CO2=-0.2*G0
		    +zCO2/concentration_coo_limite_bas
		    *(0.2*G0
			    +a_coo*log(concentration_coo_limite_bas/concentration_coo_1750));
		SORTIE("forcage_serre_CO2="<<forcage_serre_CO2);
	    }
	    else if  (zCO2>concentration_coo_limite){
		SORTIE("relation lin, extrapol haute");
		forcage_serre_CO2=a_coo*(log(concentration_coo_limite/concentration_coo_1750)
			+zCO2/concentration_coo_limite-1);
		SORTIE("forcage_serre_CO2="<<forcage_serre_CO2);
	    }
	    else {// reltion log
		SORTIE("relation log");
		forcage_serre_CO2=a_coo*log(zCO2/concentration_coo_1750) ;
		SORTIE("forcage_serre_CO2="<<forcage_serre_CO2);
	    }
	    return forcage_serre_CO2;

	}



	double calcul_phieq(double zT,double insol65N) {
	    //** inputs
	    //double zT, insol65N,zphig_ancien, dt;
	    //** ouptut 
	    //double zphig;
	    //** locals
	    double zphieq;
	    //double tau_niveau_calottes;
	    //** calculs
	    SORTIE("calcul_phig: zT="<<zT);
	    SORTIE("calcul_phig: a_calottes="<<a_calottes);
	    SORTIE("calcul_phig: b_calottes="<<b_calottes);
	    zphieq=a_calottes*(zT-273.0)+b_calottes
		+c_calottes*(insol65N-insol_actuel);
	    if (zphieq>niveau_calottes_max) {
		zphieq=niveau_calottes_max;
	    }
	    if (zphieq<niveau_calottes_min) {
		zphieq=niveau_calottes_min;
	    }

	    SORTIE("calcul_phig: a_calottes*(zT-273.0)="<<a_calottes*(zT-273.0));
	    SORTIE("calcul_phig: c_calottes*(insol65N-insol_actuel)="<<c_calottes*(insol65N-insol_actuel));
	    SORTIE("calcul_phig: zphieq="<<zphieq);


	    return zphieq;
	}
	double calcul_tau_niveau_calottes(double phieq,double zphig_ancien) {
	    double tau_niveau_calottes;
	    if (zphig_ancien<phieq) {
		SORTIE("désenglacement");
		tau_niveau_calottes=tau_niveau_calottes_deglacement;
	    }
	    else {
		SORTIE("englacement");
		tau_niveau_calottes=tau_niveau_calottes_englacement;
	    }
	    SORTIE("calcul_phig: tau_niveau_calottes="<<tau_niveau_calottes);
	    return tau_niveau_calottes;

	}

	double calcul_niveau_mer_new(double zphig,double zT,int t) {

	    SimulationValues& s=experience_values.back();
	    double niveau_mer;
	    double Tressentie;
	    int index=max(experience_values.indice_min(),t-int(tau_niveau_mer));
	    Tressentie=zT*0.2
	    		+s.temperature_data[index]*0.8;
	    SORTIE("calcul niveau mer: zT="<<zT<<"; Tressentie="<<Tressentie);
	    double dilatation=dilat*(Tressentie-273-Tressentie_act);
	    SORTIE("calcul niveau mer: Tressentie_act="<<Tressentie_act);
	    SORTIE("calcul niveau mer: Hmer_tot="<<Hmer_tot);
	SORTIE("calcul niveau mer: dilatation="<<dilatation);
	SORTIE("calcul niveau mer: zphig="<<zphig);
	SORTIE("calcul niveau mer: fmax*F(phig_act)="<<-3.8827e-7*pow(niveau_calottes_actuel,3)+1.2689e-4*pow(niveau_calottes_actuel,2)-0.0134*niveau_calottes_actuel+0.4615);
	SORTIE("calcul niveau mer: fmax*F(phig)="<<-3.8827e-7*pow(zphig,3)+1.2689e-4*pow(zphig,2)-0.0134*zphig+0.4615);
		double Hmer=Hmer_tot*(1+dilatation)*
		    (1-(-3.8827e-7*pow(zphig,3)+1.2689e-4*pow(zphig,2)-0.0134*zphig+0.4615));
		double Hmeract=Hmer_tot*
		    (1-(-3.8827e-7*pow(niveau_calottes_actuel,3)+1.2689e-4*pow(niveau_calottes_actuel,2)-0.0134*niveau_calottes_actuel+0.4615));
	SORTIE("calcul niveau mer: Hmer="<<Hmer);
	SORTIE("calcul niveau mer: Hmeract="<<Hmeract);	
	    niveau_mer=Hmer-Hmeract;
	    SORTIE("calcul niveau mer: niveau_mer="<<niveau_mer);
	    return niveau_mer;

	}

	double calcul_niveau_mer(double niveau_mer_ancien,double zphig, double zphig_ancien,
				int t) {
	    // calcul du niveau de la mer: remplissage du tableau niveau_mer_data
	    // utilise pour cela temperature_data[-99:t]
	    // **input
	    //double niveau_mer_ancien; 
	    //** output
	    double niveau_mer; 
	    // **locals
	    double T_ressentie; // temperature ressentie en t
	    double niveau_mer_eq; 		

	    SORTIE("calcul niveau mer, t="<<t);
	    SimulationValues& s=experience_values.back();
	    double dt=experience_values.temps_elem();
	    if (dt<deltat3) {
		T_ressentie=(1./(p0+p1+p2+p3))*(p0*s.temperature_data[t-int(deltat0/dt)]
			+p1*s.temperature_data[t-int(deltat1/dt)]
			+p2*s.temperature_data[t-int(deltat2/dt)]
			+p3*s.temperature_data[t-int(deltat3/dt)]);				    
	    } //if (temps_elem<deltat3) {
	    else {
		T_ressentie=s.temperature_data[t];
		SORTIE("T_ressentie=temperature_data[t]="<<s.temperature_data[t]<<"K");

	    }   //else { //if (temps_elem<deltat3) {
	    SORTIE("T_ressentie_actuelle="<<T_ressentie_actuelle);
	    // T_ressentie_actuelle en °C
	    // on calcul d'abord niveau d'équilibre lié à dilitation
	    niveau_mer_eq=niveau_mer_1750+C_niveau*log(T_ressentie/(temperature_1750+273))
		+a_mer*(sin((zphig-niveau_calottes_max)*pi/180.)
			-sin((niveau_calottes_1750-niveau_calottes_max)*pi/180.));
				 	    
	    
	    SORTIE("term1="<<C_niveau*log(T_ressentie/(temperature_1750+273)));
	    SORTIE("niveau_mer_eq="<<niveau_mer_eq);
	    
	    // niveau mer lié à dilitation: on ajoute retard
	    niveau_mer=calculT(
		    niveau_mer_eq,niveau_mer_ancien,tau_niveau_mer,experience_values.temps_elem());

	    SORTIE("niveau_mer_ancien="<<niveau_mer_ancien);
	    SORTIE("tau_niveau_mer="<<tau_niveau_mer);
	    SORTIE("niveau_mer="<<niveau_mer);
	    		    	
	    // pour zphig=90, on a term2=a_mer*0.5
	    // or si tout deglace, le niveau monterait à 70m
	    // -> a_mer=140m
	    SORTIE("zphig="<<zphig);
	    SORTIE("term2="<<a_mer*(sin((zphig-niveau_calottes_max)*pi/180.)
			-sin((niveau_calottes_1750-niveau_calottes_max)*pi/180.)));
	    SORTIE("niveau_mer="<<niveau_mer);
	    
	    SORTIE("experience_values.temps_elem()="<<experience_values.temps_elem());
	    return niveau_mer;
	}


	double calcul_zA_biologique(double zT, double A) {
	    double zA;
	    if (zT<Tlim_bio_froid) { 
		zA=0;
	    }
	    else if (zT>Tlim_bio_chaud) {
		zA=0;
	    }
	    else {
		zA=A;
	    }
	    return zA;
	}

	double calcul_zCO2eq(double zT){
	    double zCO2eq;

	    SORTIE("calcul zCO2eq_oce: entrée: zT="<<zT) 
		double c=15;
		double b=(concentration_coo_glaciaire-concentration_coo_1750)
	    		/(atan(temperature_LGM-c)-atan(temperature_1750-c));
		double a=concentration_coo_glaciaire-b*atan(temperature_LGM-c)	;
		//zCO2eq=a+b*atan(zT-273-c);
		//modif de 24 fev 2007: il faut que zCO2 eq continue à augmenter
		zCO2eq=a+b*atan(zT-273-c)+max(0.0,5*(zT-273-c));

//	    if (zT>Tlim_oce_froid && zT<Tlim_bio_chaud) {
//	    //if (zT>Tlim_oce_froid) {
//	        if (zT<=temperature_actuelle+273) {
//		SORTIE("calcul zCO2eq_oce: cas frais")    
//		zCO2eq= concentration_coo_1750+
//		    (zT-temperature_1750-273)*2
//		    *(concentration_coo_1750-concentration_coo_glaciaire)
//		    /(temperature_1750-temperature_LGM);
//		}
//		else {
//		SORTIE("calcul zCO2eq_oce: cas doux")      
//		zCO2eq= concentration_coo_1750+
//		    (zT-temperature_1750-273)
//		    *(concentration_coo_1750-concentration_coo_glaciaire)
//		    /(temperature_1750-temperature_LGM);
//		}
//		zCO2eq=max(0.,zCO2eq);
//
//	    }
//	    else if (zT<Tlim_oce_froid) {
//		SORTIE("calcul zCO2eq_oce: cas froid")    
//		zCO2eq= concentration_coo_1750+
//		    (Tlim_oce_froid-temperature_1750-273)
//		    *(concentration_coo_1750-concentration_coo_glaciaire)
//		    /(temperature_1750-temperature_LGM);
//	    }
//	    else if (zT>Tlim_bio_chaud) {
//		SORTIE("calcul zCO2eq_oce: cas chaud")    
//		zCO2eq= concentration_coo_1750+
//		    (Tlim_bio_chaud-temperature_1750-273)
//		    *(concentration_coo_1750-concentration_coo_glaciaire)
//		    /(temperature_1750-temperature_LGM);
//	    }
//	    else {
//		SORTIE("calcul_zCO2eq: zT="<<zT);
//		ASSERT(false);
//	    }

	    return zCO2eq;
	    SORTIE("calcul_zCO2eq: zT="<<zT<<", zCO2eq="<<zCO2eq);
	}

	double calcul_zCO2_ocean_eq(double zT){
	    //** output 
	    double zCO2_ocean_eq;
	    cout <<"calcul_zCO2_ocean_eq:zT="<<zT<<endl;
	    zCO2_ocean_eq=concentration_coo_naturel+a_CO2_eq*(zT-(temperature_1750+273));
	    cout <<"calcul_zCO2_ocean_eq:zCO2_ocean_eq="<<zCO2_ocean_eq<<endl;
	    return zCO2_ocean_eq;
	}

	double calcul_zC_alteration(double Cmax, double zphig){
	    //** output 
	    double zC_alteration;
	    SORTIE("calcul_zC_alteration: Cmax="<<Cmax);
	    SORTIE("calcul_zC_alteration: zphig="<<zphig);
	    if (zphig>niveau_calotte_critique_coo) {
		zC_alteration=Cmax;
	    }
	    else if (zphig>1e-2) {
		zC_alteration=Cmax*zphig/niveau_calotte_critique_coo;
	    }
	    else {
		zC_alteration=0.;
	    }

	    return zC_alteration;
	}

	double calcul_rapport_H2O(double zT){
	    double zrapport_H2O;
	    SORTIE("calcul_rapport_H2O: zT="<<zT);
	    SORTIE("calcul_rapport_H2O: temperature_1750+273="<<temperature_1750+273);
	    SORTIE("calcul_rapport_H2O: tau_T="<<tau_T);
	    //zrapport_H2O=exp((zT-(temperature_1750+273))/tau_T);	
	    //utilisation de la formule de Rankine donnant Psat	:
	    zrapport_H2O=(exp(a_rankine-b_rankine/zT))
			/(exp(a_rankine-b_rankine/(temperature_1750+273)));
	    SORTIE("calcul_rapport_H2O: zrapport_H2O="<<zrapport_H2O);
	    return zrapport_H2O;
	}

	double calcul_albedo(double zphig){
	    double zalbedo;
	    //zalbedo=albedo_phi_min+(zphig-niveau_calottes_min)
	    //    	*(albedo_phi_max-albedo_phi_min)/(niveau_calottes_max-niveau_calottes_min);
	    //zalbedo=albedo_glace-sin(zphig/180*pi)*(albedo_glace-albedo_ter);

	    //cout <<"sin(zphig/180*pi)="<<sin(zphig/180*pi)<<endl;
	    if (zphig>phig_crit) {
		zalbedo=albedo_crit
		    +(zphig-phig_crit)/(niveau_calottes_max-phig_crit)
		    *(albedo_ter-albedo_crit);
		SORTIE("calcul_albedo: albedo_crit="<<albedo_crit);
		SORTIE("calcul_albedo: albedo_actuel="<<albedo_actuel);
		SORTIE("calcul_albedo: zphig>phig_crit");
		SORTIE("B="<<(niveau_calottes_actuel-phig_crit)/(niveau_calottes_max-phig_crit));
		SORTIE("1-B="<<(1-(niveau_calottes_actuel-phig_crit)/(niveau_calottes_max-phig_crit)));
		SORTIE("Aact-B.Ater="<<albedo_actuel-albedo_ter*
			(niveau_calottes_actuel-phig_crit)/(niveau_calottes_max-phig_crit));

	    }
	    else {
		zalbedo=albedo_glace_const
		    +(zphig-niveau_calottes_min)/(phig_crit-niveau_calottes_min)
		    *(albedo_crit-albedo_glace_const);
	    }

	    SORTIE("calcul_albedo: zphig="<<zphig);
	    SORTIE("calcul_albedo: zalbedo="<<zalbedo);
	    //ASSERT(zalbedo>0);
	    //ASSERT(zalbedo<1);

	    return zalbedo;
	}

	double calcul_poce(double zT) {
	    double zpoce;
	    double poce_act=1-puit_ocean_act;

	    //* ancienne version, qui donne des rétroactions trop violentes:
	    //zpoce=poce_act*exp(A_oce*(zT-temperature_actuelle-273));
	    //* nouvelle version:
	    if (zT>temperature_actuelle-273) {
		zpoce=poce_act+(1-poce_act)*(1-exp(-(zT-temperature_actuelle-273)/deltaT_poce));
	    }
	    else {
		zpoce=poce_act*exp((zT-temperature_actuelle-273)/deltaT_poce);
	    }
	    return zpoce;	    
	}

	double calcul_zpuit_oce(double zT){
	    double zpuit_oce;
		zpuit_oce=(zT-Tcrit_oce-273)/(temperature_actuelle-Tcrit_oce)*puit_ocean_act/100.0;
		SORTIE("calcul_zpuit_oce: zpuit_oce="<<zpuit_oce);
		zpuit_oce=max(0.,zpuit_oce);
		zpuit_oce=min(puit_oce_max,zpuit_oce);
		SORTIE("calcul_zpuit_oce: zpuit_oce="<<zpuit_oce);
		ASSERT(zpuit_oce>=0.);
		ASSERT(zpuit_oce<=puit_oce_max);
	    return zpuit_oce;
	}

	double calcul_Fdegaz(double zT){
	    double Fdegaz;
		if (zT-273>Tcrit_oce) {
			 Fdegaz=(zT-Tcrit_oce-273)*dFdegaz;
		}
		else Fdegaz=0;
		ASSERT(Fdegaz>=0.);
	    return Fdegaz;
	}

	double abs(double x) {
	    double y;
	    if (x<0) {y=-x;}
	    else {y=x;}		    
	    return y;
	}



