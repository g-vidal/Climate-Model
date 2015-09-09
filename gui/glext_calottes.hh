// generated 2007/1/29 22:24:42 CET by gama@buffy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to glext_calottes.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef GLEXT_CALOTTES_HH
#define GLEXT_CALOTTES_HH

#include <iostream>
#include <cstdlib>

#include <gtkmm.h>

#include <gtkglmm.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>

#include "rgba_texture.h"

class glext_calottes : public Gtk::GL::DrawingArea
{  
    public:
	//initialisation statique (a faire dans main)
	static void init_glconfig();
	glext_calottes();
	virtual ~glext_calottes();

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
	//les planispheres
	static const int nb_earth_textures=5;
	RGBATexture calottes_texture[nb_earth_textures];

	int calotte_texture_select();

	//pour les animations
	sigc::connection m_ConnectionTimeout;

    private:
        //partie openGL
        static Glib::RefPtr<Gdk::GL::Config> glconfig;
	int display_list;
	
};

#endif //glext_calottes_HH
