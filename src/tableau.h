#ifndef TABLEAU_H
#define TABLEAU_H

#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <memory.h>

#define NNN 100

class tableau
{
    private:
	double data[2*NNN+1];
	double resolution;
	int imin;
	int imax;

	bool is_in_bounds(int i) const
	{
	    return i>=imin && i<=imax;
	}

    public:
	tableau();
	tableau(double temps_elem,int indice_min,int indice_max);
	void init(double temps_elem,int indice_min,int indice_max);
	inline double& operator[](const int& i) 
	{
	    assert(is_in_bounds(i));
	    return data[NNN+i];
	}
	inline const double& operator[](const int& i) const 
	{
	    assert(is_in_bounds(i));
	    return data[NNN+i];
	}
	//interpole la valeur au temps x
	double operator()(double x) const;

	//retourne le minimum et le maximum du tableau
	//si init=true, initialise cur_min et cur_max a +/-INFINITY
	//par defaut, chercher dans tout le tableau, sinon preciser
	//start_index
	void minimax(double& current_min,double& current_max,
		int start_index,bool init=false) const;
	void minimax(double& current_min,double& current_max) const
	{
	    minimax(current_min,current_max,imin,true);
	}

	inline double xmin() const {return resolution * imin;}
	inline double xmax() const {return resolution * imax;}


	//conversion final-initial, précisant l'origine de la nouvelle
	//simulation
	void recast_final_initial(const tableau& t,double temps_origin);
	
	//convertit un etat final en etat initial, l'origine de la nouvelle
	// simulation est la fin de l'ancienne simulation
	void recast_final_initial(const tableau& t);
	
	//entrees-sorties
	friend std::ostream& operator<<(std::ostream& out,const tableau& t);
	friend std::istream& operator>>(std::istream& in,tableau& t);

	//copie
    private:
	void deep_copy(const tableau& t);
    public:
	inline tableau(const tableau& t) {deep_copy(t);}
	inline tableau& operator=(const tableau& t) 
	{
	    deep_copy(t); 
	    return *this;
	}
};
#endif// TABLEAU_H

