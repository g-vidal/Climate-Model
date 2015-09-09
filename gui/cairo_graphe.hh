// generated 2007/1/29 22:24:42 CET by gama@buffy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to cairo_graphe.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef cairo_graphe_HH
#define cairo_graphe_HH

#include <iostream>
#include <cstdlib>

#include <gtkmm.h>

#include <vector>
#include <graph_designer.h>

class tableau;

class cairo_graphe : public Gtk::DrawingArea
{  
    public:
	//initialisation statique (a faire dans main)
	cairo_graphe(int numero);
	virtual ~cairo_graphe();

    protected:
	//les signaux (hérités)
	virtual void on_realize();
	virtual bool on_configure_event(GdkEventConfigure* event);
	virtual bool on_expose_event(GdkEventExpose* event);

    private:
	int numero_graphe;
	//préparation du gds
	graph_designer* pgds;
	double xtranscoef;
	double xtransoffset;
	double ytranscoef;
	double ytransoffset;
	inline double fx(double x) {return xtranscoef*x+xtransoffset;}
	inline double fy(double y) {return ytranscoef*y+ytransoffset;}


	static void set_color(Cairo::RefPtr<Cairo::Context> cr,int i);
	void compile_graph();
	void draw_graph(Cairo::RefPtr<Cairo::Context> cr,int w,int h);

    public:
	void recompile();
	bool redraw();

};

#endif //cairo_graphe_HH
