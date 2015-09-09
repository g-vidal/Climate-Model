// generated 2007/1/29 22:24:42 CET by gama@buffy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to glext_waterlevel.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef GLEXT_WATERLEVEL_HH
#define GLEXT_WATERLEVEL_HH

#include <iostream>
#include <cstdlib>

#include <gtkmm.h>
#include <gtkglmm.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "rgba_texture.h"

class tableau;

class glext_waterlevel : public Gtk::GL::DrawingArea
{  
    public:
	//initialisation statique (a faire dans main)
	static void init_glconfig();
	glext_waterlevel();
	virtual ~glext_waterlevel();

	bool redraw();
	void enable_animations();
	void disable_animations();

    protected:
	//les signaux (hérités)
	virtual void on_realize();
	virtual bool on_configure_event(GdkEventConfigure* event);
	virtual bool on_expose_event(GdkEventExpose* event);
	virtual bool on_timeout();

    private:
	RGBATexture data_sable;
	RGBATexture data_neige;
	RGBATexture data_eau;
	RGBATexture data_homme_chaud;
	RGBATexture data_homme_froid;
	RGBATexture data_palmier_chaud;
	RGBATexture data_palmier_froid;
	//pour construire la texture de sable
	unsigned char carteraw[2500];
	unsigned char* carte[50];
	void waterlevel_output(int i,int j);
	//pour les animations
	sigc::connection m_ConnectionTimeout;

    private:
	//partie openGL
	static Glib::RefPtr<Gdk::GL::Config> glconfig;
};

#endif //GLEXT_GRAPHE_HH
