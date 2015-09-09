#include "modele_consts_physique.h"
#include "exceptions.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

int main(){

    double Fin,Fout;
    double zphig,zrapport_H2O,zalbedo;
    double forcage_serre_CO2,forcage_serre_eau,forcage_serre,G;
    double calcul_forcage_serre_CO2(double zCO2);
    double insol65N=insol_actuel;
    double Fin0=puissance_recue_zero;
    double calcul_forcage_serre_H2O(double zrapport_H2O);
    double calcul_rapport_H2O(double zT);
    double calcul_phieq(double zT,double insol65N);
    double calcul_albedo(double zphig);

    
    ofstream ofsin("../../figs/debug_eqrad_in.txt");
    ofstream ofsout("../../figs/debug_eqrad_out.txt");
    ofsin << "T" ;
    ofsout << "T" ;
    for (double zCO2=100;zCO2<=4e5;zCO2*=5) {
	ofsin <<"\t" << "CO2=" <<zCO2;
	ofsout <<"\t" << "CO2=" <<zCO2;
	
    }
    ofsin <<endl;
	ofsout <<endl;

    for (double zT=100;zT<=350.;zT+=5) {
	cout <<endl;
	cout <<"*** zT="<<zT<<endl;
	ofsin <<zT;
	ofsout <<zT;
	for (double zCO2=100;zCO2<=4e5;zCO2*=5) {
	    cout <<"** zCO2="<<zCO2<<endl;
	    forcage_serre_CO2=calcul_forcage_serre_CO2(zCO2);
	    zrapport_H2O=calcul_rapport_H2O(zT);
	    forcage_serre_eau=calcul_forcage_serre_H2O(zrapport_H2O);
	    forcage_serre=forcage_serre_CO2+forcage_serre_eau;
	    G=G0-forcage_serre;
	    if (G<G_min) {
			G=G_min;
		    }
		    if (G>1) {
			G=1;
		    }
	    Fout=G*sigma*exp(4*log(zT));

	    zphig=calcul_phieq(zT,insol65N);
	    zalbedo=calcul_albedo(zphig);
	    Fin=Fin0*(1-zalbedo);		
	    
	    cout <<"Fin="<<Fin<<endl;;
	    cout <<"Fout="<<Fout<<endl;
	    ofsin<<"\t" <<Fin;
	    ofsout<<"\t" <<Fout;
	}
	ofsin <<endl;
	ofsout <<endl;
    }
    ofsin.close();
ofsout.close();

}


