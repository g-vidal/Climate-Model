#include "tableau.h"
#include "globals.h"
#include "exceptions.h"
#include <cmath>
using namespace std;

double tableau::operator()(double x) const
{
    double a = x/resolution;
    double ainf = std::floor(a);
    double vinf = (*this)[static_cast<int>(ainf)];
    if (ainf==a) return vinf;
    double asup = ainf+1.;
    double vsup = (*this)[static_cast<int>(ainf)+1];
    return vsup*(a-ainf)+vinf*(asup-a);
}

tableau::tableau()
{
        init(experience_values.temps_elem(),
	    experience_values.indice_min(),
	    experience_values.indice_max());

}

tableau::tableau(double temps_elem,int indice_min,int indice_max)
{
    init(temps_elem,indice_min,indice_max);
}

void tableau::init(double temps_elem,int indice_min,int indice_max)
{
    //WARNING("nouveau tableau(" << temps_elem << "," << indice_min << "," << indice_max << ")");
    memset(data,0,sizeof(data));
    resolution=temps_elem;
    imin=indice_min;
    imax=indice_max;
}

void tableau::deep_copy(const tableau& t)
{
    memcpy(data,t.data,sizeof(data));
    resolution=t.resolution;
    imin=t.imin;
    imax=t.imax;
}

ostream& operator<<(ostream& out,const tableau& t)
{
    out << t.resolution << " " << t.imin << " " << t.imax << " [ ";
    for (int i=t.imin;i<=t.imax;i++)
	out << t[i] << " ";
    out << "]";
    return out;
}
istream& operator>>(istream& in,tableau& t)
{
    string tmp;
    in >> t.resolution >> t.imin >> t.imax >> tmp;
    for (int i=t.imin;i<=t.imax;i++)
	in >> t[i];
    in >> tmp;
    return in;
}


void tableau::recast_final_initial(const tableau& t,double temps_origin)
{
    assert(&t!=this); //interdit de s'auto-recaster
    //WARNING("Using temps_elem=" << experience_values.temps_elem());
    resolution = experience_values.temps_elem();
    imin = experience_values.indice_min();
    imax = experience_values.indice_max();
    memset(data,0,(2*NNN+1)*sizeof(double));
    for (int i=0;i>=imin;i--)
	(*this)[i] = t(temps_origin + this->resolution * i);
}

void tableau::recast_final_initial(const tableau& t)
{
    recast_final_initial(t,t.imax * t.resolution);
}

void tableau::minimax(double& current_min,double& current_max,int start_index,bool init) const
{
    if (init)
    {
	current_min = INFINITY;
	current_max = -INFINITY;
    }
    double cur_val;
    for (int i=start_index;i<=imax;i++)
    {
	cur_val = (*this)[i];
	if (cur_val>current_max) current_max=cur_val;
	if (cur_val<current_min) current_min=cur_val;
    }
}
