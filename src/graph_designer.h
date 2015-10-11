#ifndef GRAPH_DESIGNER_H
#define GRAPH_DESIGNER_H

#include "tableau.h"
#include <glibmm/ustring.h>
#include <vector>
#include <cstdlib>

class graph_designer
{
    private:
	std::vector<const tableau*> tabs;
	double ymin;
	double ymax;
	double xtabmin; //ds le tableau
	double xtabmax;
	double xoffset; //gra(xoffset)=tab(0)
	double xgramin; //sur le graphique
	double xgramax;
	//ticks
	double xtickmin;
	double ytickmin;
	int xticknb;
	int yticknb;
	double xtickinterval;
	double ytickinterval;
	//x step
	double xstepmin;
	int xstepnb;
	double xstepinterval;
	//packed
	bool packed;

    public:
	//input
	void clear();
	void add(const tableau& t,double xstart=0.);
	void pack(double xoffset=0);
	inline bool is_ready() {return packed;}
	inline int nb_tabs() {return tabs.size();}

	//output
	double xvalue(double x_percent);
	double yvalue(int tab_id,double x_percent);
	double ypercent(int tab_id,double x_percent);
	Glib::ustring xticklabel(int tick_id);
	double xtickvalue(int tick_id);
	double xtickpercent(int tick_id);
	inline int nbxtick() {return xticknb;}
	inline int nbytick() {return yticknb;}
	Glib::ustring yticklabel(int tick_id);
	double ytickpercent(int tick_id);
	double ytickvalue(int tick_id);

	graph_designer();
	graph_designer(const graph_designer&);
	graph_designer& operator=(const graph_designer&);
	~graph_designer();

    private:
	void pop_back();
};

#endif // GRAPH_DESIGNER_H
