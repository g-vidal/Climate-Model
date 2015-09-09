// generated 2007/1/29 22:24:42 CET by gama@buffy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to glext_waterlevel.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "glext_waterlevel.hh"
#include "glconfigutil.h"
#include <exceptions.h>
using namespace std;

glext_waterlevel::glext_waterlevel()
  : Gtk::GL::DrawingArea(glconfig)
{
    set_size_request(200,200);
}

glext_waterlevel::~glext_waterlevel()
{
}

void glext_waterlevel::on_realize()
{
    // We need to call the base on_realize()
    Gtk::GL::DrawingArea::on_realize();

    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    if (!glwindow->gl_begin(get_gl_context()))
	return;

    // *** OpenGL BEGIN ***

    printf("generating water-texture\n");
    glEnable(GL_DEPTH_TEST);  	//Active le depth test
    glEnable(GL_LIGHTING);  	// Active l'éclairage
    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHT0); 	// Allume la lumière n°1
#ifndef WIN32
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SINGLE_COLOR);
#endif
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,(float[]) {0.4,0.4,0.4,1.});
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,0); 

    glEnable(GL_TEXTURE_2D); 	//Active le texturing
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    data_sable.gl_init("textures/sable.rgba",256,256);
    data_sable.set_material((float[]){0.8f,0.8f,0.6f,1.f},
	    (float[]){0.8,0.8,0.5,1.},
	    (float[]){0.4,0.4,0.3,1.},
	    100.);
    data_neige.gl_init("textures/neige.rgba",256,256);
    data_neige.set_material((float[]) {1.,1.,1.,1.},
	    (float[]) {0.9,0.9,0.9,1.},
	    (float[]) {0.6,0.6,0.6,1.},
	    5.);
    data_eau.gl_init("textures/eau.rgba",256,256);
    data_eau.set_material((float[]) {0.0,0.9,1.,1.},
	    (float[]) {0.0,0.5,0.8,1.},
	    (float[]) {0.0,0.2,0.3,1.},
	    35.f);
    data_homme_chaud.gl_init("textures/bonhomme_chaud.rgba",128,256,true);
    data_homme_chaud.set_material((float[]) {1.,1.,1.,1.},
	(float[]) {0.8,0.8,0.8,1.},
	(float[]) {0.8,0.8,0.8,1.},
	95.);	
    data_homme_froid.gl_init("textures/bonhomme_froid.rgba",128,256,true);
    data_homme_chaud.set_material((float[]) {1.,1.,1.,1.},
	(float[]) {0.8,0.8,0.8,1.},
	(float[]) {0.8,0.8,0.8,1.},
	95.);	
    data_palmier_chaud.gl_init("textures/palmier-chaud.rgba",256,256,true);
    data_palmier_chaud.set_material((float[]) {1.,1.,1.,1.},
	(float[]) {0.8,0.8,0.8,1.},
	(float[]) {0.8,0.8,0.8,1.},
	95.);	
    data_palmier_froid.gl_init("textures/palmier-froid.rgba",256,256,true);
    data_palmier_froid.set_material((float[]) {1.,1.,1.,1.},
	(float[]) {0.8,0.8,0.8,1.},
	(float[]) {0.8,0.8,0.8,1.},
	95.);	

    printf("generating water mesh\n");
    glNewList(2,GL_COMPILE);
    {

	for (int i=0;i<50;i++)
	    carte[i]=carteraw+50*i;
	FILE* F = fopen("textures/ile.gray","rb");
	fread(carteraw,2500,1,F);

	for (int i=0;i<49;i++)
	{
	    glBegin(GL_TRIANGLE_STRIP);
	    for (int j=0;j<50;j++)
	    {
		waterlevel_output(i,j);
		waterlevel_output(i+1,j);
	    }
	    glEnd();
	}
    }
    glEndList();
    
    // *** OpenGL END ***
    glwindow->gl_end();
}

bool glext_waterlevel::on_configure_event(GdkEventConfigure* event)
{
    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    if (!glwindow->gl_begin(get_gl_context()))
	return false;

    // *** OpenGL BEGIN ***
    int w = event->width;
    int h = event->height;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-25.0, 25.0, -20.0, 20.0, -45., 45.);
    glRotated(-80,1,0,0);

    // Choose the modelview matrix to be the matrix
    // manipulated by further calls
    glMatrixMode(GL_MODELVIEW);

    //glClearColor(0.0, 0.0, 0.0, 0.5);
    //glClear(GL_COLOR_BUFFER_BIT);

    // *** OpenGL END ***
    glwindow->gl_end();

    return true;
}

double current_waterlevel();
double current_temperature();
double current_calotteslevel();

bool glext_waterlevel::on_expose_event(GdkEventExpose* event)
{
    return redraw();
}

bool glext_waterlevel::redraw()
{
    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    if (!glwindow->gl_begin(get_gl_context()))
	return false;
    // *** OpenGL BEGIN ***

    double niveau_eau=5*current_waterlevel();
    //WARNING("niveau eau = "<<niveau_eau);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLineWidth(1.0);
    glLoadIdentity();
    //obliquité
    //glRotated(28,0,1,0);
    glLightiv(GL_LIGHT0,GL_POSITION,(int[]) {-20,-15,20,0});
    glLightfv(GL_LIGHT0,GL_AMBIENT,(float[]) {0.3,0.3,0.3,1.});
    glLightfv(GL_LIGHT0,GL_DIFFUSE,(float[]) {1.,1.,1.,1.});
    glLightfv(GL_LIGHT0,GL_SPECULAR,(float[]) {1.,1.,1.,1.});
    //glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,0.);
    static int b=0;
    b = (b+1)%300;
    glRotated(280 + 30*(1+sin(2.*M_PI*(b/300.))),0,0,1.);

    if (current_calotteslevel()>15)
    {
	data_sable.gl_bind();
    }
    else
    {
	data_neige.gl_bind();
    }
    glCallList(2);

    //palmier
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER,0.01);
    if (current_calotteslevel()>15)
	data_palmier_chaud.gl_bind();
    else
	data_palmier_froid.gl_bind();
    glBegin(GL_QUADS);
    glNormal3f(-0.68,-0.68,0.2);
    glTexCoord2f(1.,1.);
    glVertex3f(-4-9,-3+12,6);
    glTexCoord2f(0.,1.);
    glVertex3f(4-9,3+12,6);
    glTexCoord2f(0.,0.);
    glVertex3f(4-9,3+12,20);
    glTexCoord2f(1.,0.);
    glVertex3f(-4-9,-3+12,20);
    glEnd();

    //bonhomme
    if (current_temperature()>10)
	data_homme_chaud.gl_bind();
    else	
	data_homme_froid.gl_bind();

    glBegin(GL_QUADS);
    glNormal3f(-0.68,-0.68,0.2);
    glTexCoord2f(1.,1.);
    glVertex3f(-4,-2.5,0);
    glTexCoord2f(0.,1.);
    glVertex3f(0,0.5,0);
    glTexCoord2f(0.,0.);
    glVertex3f(0,0.5,10);
    glTexCoord2f(1.,0.);
    glVertex3f(-4,-2.5,10);
    glEnd();
    glDisable(GL_ALPHA_TEST);


    if (niveau_eau>-6)
    {
	if (niveau_eau>30) niveau_eau=30;
	data_eau.gl_bind();

	glBegin(GL_QUADS);
	glNormal3f(0.,0.,1.);
	glTexCoord2f(0.,0.);
	glVertex3f(-25,-25,niveau_eau);
	glTexCoord2f(0.,1.);
	glVertex3f(-25,25,niveau_eau);
	glTexCoord2f(1.,1.);
	glVertex3f(25,25,niveau_eau);
	glTexCoord2f(1.,0.);
	glVertex3f(25,-25,niveau_eau);


	//glNormal3f(-0.33,0.,0.9);
	glTexCoord2f(0.,0.);
	glVertex3f(-25,-25,niveau_eau);
	glTexCoord2f(0.,1.);
	glVertex3f(-25,25,niveau_eau);
	glTexCoord2f(0.5,1.);
	glVertex3f(-25,25,-6.);
	glTexCoord2f(0.5,0.);
	glVertex3f(-25,-25,-6.);

	//glNormal3f(0.,0.33,0.9);
	glTexCoord2f(0.,1.);
	glVertex3f(-25,25,niveau_eau);
	glTexCoord2f(1.,1.);
	glVertex3f(25,25,niveau_eau);
	glTexCoord2f(1.,0.5);
	glVertex3f(25,25,-6.);
	glTexCoord2f(0.,0.5);
	glVertex3f(-25,25,-6.);

	//glNormal3f(0.33,0.,0.9);
	glTexCoord2f(1.,1.);
	glVertex3f(25,25,niveau_eau);
	glTexCoord2f(1.,0.);
	glVertex3f(25,-25,niveau_eau);
	glTexCoord2f(0.5,0.);
	glVertex3f(25,-25,-6.);
	glTexCoord2f(0.5,1.);
	glVertex3f(25,25,-6.);

	//glNormal3f(0.,-0.33,0.9);
	glTexCoord2f(1.,0.);
	glVertex3f(25,-25,niveau_eau);
	glTexCoord2f(0.,0.);
	glVertex3f(-25,-25,niveau_eau);
	glTexCoord2f(0.,0.5);
	glVertex3f(-25,-25,-6.);
	glTexCoord2f(1.,0.5);
	glVertex3f(25,-25,-6.);
	glEnd();
    }


    // *** OpenGL END ***
    glwindow->swap_buffers();
    glwindow->gl_end();

    return true;
}

Glib::RefPtr<Gdk::GL::Config> glext_waterlevel::glconfig;

void glext_waterlevel::init_glconfig()
{
    // Try double-buffered visual
    glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGBA    |
	    Gdk::GL::MODE_DEPTH |
	    Gdk::GL::MODE_DOUBLE);
    if (!glconfig)
    {
	std::cerr << "*** Cannot find the double-buffered visual.\n";
	std::exit(1);
    }

    // print frame buffer attributes.
    GLConfigUtil::examine_gl_attrib(glconfig);
}  

void glext_waterlevel::waterlevel_output(int i,int j)
{
    double dx,dy;
    double v;
    if (i==0) dx=carte[1][j]-carte[0][j];
    else if (i==49) dx=carte[49][j]-carte[48][j];
    else dx=carte[i+1][j]-carte[i-1][j];
    if (i==0) dy=carte[i][1]-carte[i][0];
    else if (i==49) dy=carte[i][49]-carte[i][48];
    else dy=carte[i][j+1]-carte[i][j-1];
    v=carte[i][j];
    double norm=dx*dx+dy*dy+4;
    norm=sqrt(norm);

    glNormal3f(dx/norm,dy/norm,2./norm);
    //glNormal3f(0,0,1.);
    glTexCoord2f(j/49.,i/49.);
    glVertex3f(i-25.,j-25.,((127-v)/20.));
}

//-------------lien avec kernel
#include <globals.h>
#include "climat.hh"
#define icur climat_interface.indice_courant
#define sv experience_values.back()
#define ei experience_values.get_etat_initial()
#define ev experience_values

double current_waterlevel() 
{
    if (ev.nb_simulations()==0)
	return ei.niveau_mer_data[0];
    else
	return sv.niveau_mer_data[icur];
}
double current_temperature() 
{
    if (ev.nb_simulations()==0)
	return ei.temperature_data[0];
    else
	return sv.temperature_data[icur];
}
double current_calotteslevel() 
{
    if (ev.nb_simulations()==0)
	return ei.niveau_calottes_data[0];
    else
	return sv.niveau_calottes_data[icur];
}


//pour les animations
bool glext_waterlevel::on_timeout()
{
    redraw();
    return true;
}

void glext_waterlevel::enable_animations()
{
    WARNING("plouf");
    if (!m_ConnectionTimeout.connected())
    {
	    WARNING("plaf");
	m_ConnectionTimeout = Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &glext_waterlevel::on_timeout), 30);
    }
}

void glext_waterlevel::disable_animations()
{
    if (m_ConnectionTimeout.connected())
	m_ConnectionTimeout.disconnect();
}

