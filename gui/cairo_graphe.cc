// generated 2007/1/29 22:24:42 CET by gama@buffy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to cairo_graphe.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "cairo_graphe.hh"
#include "exceptions.h"
#include "traduction.h"
#include "climat.hh"
#include <cairomm/cairomm.h>
using namespace std;

double current_index();


cairo_graphe::cairo_graphe(int numero)
  : Gtk::DrawingArea()
{
    set_size_request(400,200);
    numero_graphe = numero;
    pgds=0;
}

cairo_graphe::~cairo_graphe()
{
}

void cairo_graphe::on_realize()
{
    // We need to call the base on_realize()
    Gtk::DrawingArea::on_realize();

    compile_graph();
}

bool cairo_graphe::on_configure_event(GdkEventConfigure* event)
{
    return true;
}

bool cairo_graphe::on_expose_event(GdkEventExpose* event)
{
    return redraw();
}

bool cairo_graphe::redraw()
{
    Glib::RefPtr<Gdk::Window> window = get_window();
    if (!window) return false;
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

    draw_graph(cr,width,height);

    cr->set_source_rgb(0.,0.,0.);
    cr->set_line_width(1);
    double cur_index = 2.*current_index();
    cr->move_to(fx(cur_index),fy(0.));
    cr->line_to(fx(cur_index),fy(100.));
    cr->stroke();

    return true;
}

// ---------------LIEN avec kernel-------------------
#include <globals.h>
#include "climat.hh"
#include <graph_designer.h>
#define ev experience_values

double current_index()
{
    return climat_interface.indice_courant;
}

void cairo_graphe::recompile()
{
    compile_graph();
    redraw();
    return;
}

void cairo_graphe::set_color(Cairo::RefPtr<Cairo::Context> cr,int i)
{
    switch(i)
    {
	case 0:
	    cr->set_source_rgb(1.,0.,0.);  break;
	case 1:
	    cr->set_source_rgb(0.,1.,0.);  break;
	case 2:
	    cr->set_source_rgb(0.,0.,1.);  break;
	case 3:
	    cr->set_source_rgb(1.,1.,0.);  break;
	case 4:
	    cr->set_source_rgb(1.,0.,1.);  break;
	case 5:
	    cr->set_source_rgb(0.,1.,1.);  break;
	case 6:
	    cr->set_source_rgb(0.5,0.,0.);  break;
	case 7:
	    cr->set_source_rgb(0.,0.5,0.);  break;
	case 8:
	    cr->set_source_rgb(0.,0.,0.5);  break;
	case 9:
	    cr->set_source_rgb(0.5,0.5,0.);  break;
	case 10:
	    cr->set_source_rgb(0.5,0.,0.5);  break;
    }
}


void cairo_graphe::compile_graph()
{
    if (pgds) delete pgds;
    pgds = new graph_designer();
    graph_designer& gds = *pgds;
    //gds.clear();
    for (int i=0;i<ev.nb_simulations();i++)
	switch(ev.graph_displayed(numero_graphe))
	{
	    case TEMPERATURE:
		    gds.add(ev.get_simulation(i).temperature_data);
		    break;
	    case WATERLEVEL:
		    gds.add(ev.get_simulation(i).niveau_mer_data);
		    break;
	    case CALOTTESLEVEL:
		    gds.add(ev.get_simulation(i).niveau_calottes_data);
		    break;
	    case CONCENTRATION_CO2:
		    gds.add(ev.get_simulation(i).concentrations_coo_data);
		    break;
	    case EMISSIONS_CO2:
		    gds.add(ev.get_simulation(i).emissions_coo_data);
		    break;
	    case ALBEDO:
		    gds.add(ev.get_simulation(i).albedo_data);
		    break;
	    default:
		    PLANTE("invalid graphe");
	}
    gds.pack(ev.annee_debut());
    //dessin des graphes
}

void cairo_graphe::draw_graph(Cairo::RefPtr<Cairo::Context> cr,int w,int h)
{

    // Clear the window
    cr->rectangle(0,0,w,h);
    cr->set_source_rgb(0.9, 0.9, 1.);
    cr->fill();
    if (!pgds->is_ready()) return;
    
    //calcule la matrice de transformation
    xtranscoef=w/225.;
    ytranscoef=-h/120.;
    xtransoffset=15.*xtranscoef;
    ytransoffset=-110*ytranscoef;
  
    //
    int i;
    
    // Set the drawing color
    cr->set_source_rgb(0., 0., 0.);
    cr->set_line_width(1.0);
    
    // Axes ticks et et fleches
    // y
    cr->move_to(fx(0),fy( 0));
    cr->line_to(fx(0),fy( 100));
    cr->move_to(fx(0),fy( 100));
    cr->line_to(fx(-2),fy( 98));
    cr->move_to(fx(0),fy( 100));
    cr->line_to(fx(2),fy( 98));
    for (i=0;i<pgds->nbytick();i++)
    {
	double y=100.*pgds->ytickpercent(i);
	cr->move_to(fx(0),fy(y));
	cr->line_to(fx(2),fy(y));
    }
    // x
    cr->move_to(fx(0),fy( 0));
    cr->line_to(fx(200),fy( 0));
    cr->move_to(fx(200),fy( 0));
    cr->line_to(fx(198),fy( 2));
    cr->move_to(fx(200),fy( 0));
    cr->line_to(fx(198),fy( -2));
    for (i=0;i<pgds->nbxtick();i++)
    {
	double x=200.*pgds->xtickpercent(i);
	cr->move_to(fx(x),fy(0));
	cr->line_to(fx(x),fy(2));
    }
    cr->stroke();

    //la courbe elle-meme
    cr->set_line_width(2.0);
 
    for (int i=0;i<pgds->nb_tabs();i++)
    {
	set_color(cr,i);
	cr->move_to(fx(0),fy(100.*pgds->ypercent(i,0.)));
	for (int j=1;j<200;j++)	
	    cr->line_to(fx(j),fy(100.*pgds->ypercent(i,j/200.)));
	cr->stroke();
    }

    Cairo::TextExtents textents;
    cr->select_font_face ("Sans", Cairo::FONT_SLANT_NORMAL,
                               Cairo::FONT_WEIGHT_NORMAL);
    cr->set_font_size (8);

    
    //legendes
    cr->set_source_rgb(0.0, 0.0, 0.0);
    for (i=0;i<pgds->nbytick();i++)
    {
	double y=100.*pgds->ytickpercent(i);
	cr->get_text_extents(pgds->yticklabel(i),textents);
        cr->move_to(fx(-2)-textents.width,fy(y)+textents.height/2.);
        cr->show_text(pgds->yticklabel(i));
    }
    //legendes x
    for (i=0;i<pgds->nbxtick();i++)
    {
	double x=200.*pgds->xtickpercent(i);
        cr->get_text_extents(pgds->xticklabel(i),textents);
        cr->move_to(fx(x)-textents.width/2.,fy(-2)+textents.height);
        cr->show_text(pgds->xticklabel(i));
    }

     cr->set_font_size (10);
     cr->get_text_extents(gettext("temps (en années)"),textents);
     cr->move_to(fx(200)-textents.width,fy(3));
     cr->show_text(gettext("temps (en années)"));
}

