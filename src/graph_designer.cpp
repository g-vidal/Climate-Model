#include "graph_designer.h"
#include <cmath>
#include "exceptions.h"
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
using Glib::ustring;


void graph_designer::clear()
{
    xtabmin = INFINITY;
    xtabmax = -INFINITY;
    ymin = INFINITY;
    ymax = -INFINITY;
    while (!tabs.empty()) pop_back();
    packed=false;
}

void graph_designer::add(const tableau& t,double xstart)
{
    packed=false;

    //determination du min et du max en x
    if (xstart<t.xmin()) xstart=t.xmin();
    if (xstart<xtabmin) xtabmin=xstart;
    if (t.xmax()>xtabmax) xtabmax=t.xmax();
    //determination du min et du max en y
    t.minimax(ymin,ymax,0);
    tabs.push_back(&t);    
}

void graph_designer::pack(double xoffset)
{
    double tmp;
    //bounds en x sur le graphique
    this->xoffset=xoffset;
    this->xgramin=xtabmin+xoffset; 
    this->xgramax=xtabmax+xoffset;
    //bounds en y sur le graphique
    if (ymax-ymin<8)
    {
	tmp = (ymax+ymin)/2.;
	ymax=tmp+4.;
	ymin=tmp-4.;
    }
    
    //ticks en x
    tmp = log(xgramax-xgramin)/M_LN10;
    tmp = pow(10.,ceil(tmp)-1.);
    if ((xgramax-xgramin)/tmp<=5) tmp /=2.;
    if ((xgramax-xgramin)/tmp<=5) tmp /=2.;

    this->xtickinterval = tmp;
    this->xtickmin = tmp * ceil(xgramin/tmp);
    this->xticknb = static_cast<int>(floor((xgramax-xgramin)/tmp));
    
    //ticks en y
    tmp = log(ymax-ymin)/M_LN10;
    tmp = pow(10.,ceil(tmp)-1.);
    if ((ymax-ymin)/tmp<=5) tmp /=2.;
    if ((ymax-ymin)/tmp<=5) tmp /=2.;
    this->ytickinterval = tmp;
    this->ytickmin = tmp * ceil(ymin/tmp);
    this->yticknb = static_cast<int>(floor((ymax-ymin)/tmp));

    packed=true;
}


//output
double graph_designer::xvalue(double x_percent)
{
    return xgramin + x_percent * (xgramax - xgramin);
}
double graph_designer::yvalue(int tab_id,double x_percent)
{
    return (*tabs[tab_id])(xvalue(x_percent)-xoffset);
}
double graph_designer::ypercent(int tab_id,double x_percent)
{
    return (yvalue(tab_id,x_percent)-ymin)/(ymax-ymin);
}

double graph_designer::xtickvalue(int tick_id)
{
    return xtickmin + xtickinterval * tick_id;
}
double graph_designer::xtickpercent(int tick_id)
{
    return (xtickvalue(tick_id) - xgramin)/(xgramax - xgramin);
}

static inline void reformat_number(char* c, const int nbchs)
{
    c[nbchs]=0;
    int debutzerod = nbchs;
    for (int i=nbchs-1;i>=0;i--)
    {
	if (debutzerod==i+1 && c[i]=='0') debutzerod=i;
	if (c[i]<'0' || c[i]>'9') 
	{
	    if (debutzerod==i+1)
	    {
		c[i]=0;
		break;
	    }
	    else
	    {
		c[debutzerod]=0;
		c[i]=',';
		break;
	    }
	}
    }

}

Glib::ustring graph_designer::xticklabel(int tick_id)
{
    ostringstream c; c << setprecision(5) << xtickvalue(tick_id);    
    return ustring(c.str());
}
double graph_designer::ytickvalue(int tick_id)
{
    return ytickmin + ytickinterval * tick_id;
}
double graph_designer::ytickpercent(int tick_id)
{
    return (ytickvalue(tick_id)-ymin)/(ymax-ymin);
}
Glib::ustring graph_designer::yticklabel(int tick_id)
{
    ostringstream c; c << setprecision(5) << ytickvalue(tick_id);    
    return ustring(c.str());
}

graph_designer::graph_designer()
{
    clear();
}
graph_designer::graph_designer(const graph_designer&)
{
    PLANTE("interdit de copier un graphdesigner");
}
graph_designer& graph_designer::operator=(const graph_designer&)
{
    PLANTE("interdit de copier un graphdesigner");
    return *this;
}
graph_designer::~graph_designer()
{
    clear();
}

void graph_designer::pop_back()
{
    //delete tabs.back();
    tabs.pop_back();
}

