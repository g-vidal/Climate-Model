// generated 2007/1/29 22:24:42 CET by gama@buffy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to glext_calottes.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "glext_calottes.hh"
#include "glconfigutil.h"

glext_calottes::glext_calottes()
  : Gtk::GL::DrawingArea(glconfig)
{
    set_size_request(200,200);
}

glext_calottes::~glext_calottes()
{
}

void glext_calottes::on_realize()
{
    // We need to call the base on_realize()
    Gtk::GL::DrawingArea::on_realize();

    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    if (!glwindow->gl_begin(get_gl_context()))
	return;

    // *** OpenGL BEGIN ***

    printf("generating texture\n");
    glEnable(GL_DEPTH_TEST);  	//Active le depth test
    glEnable(GL_LIGHTING);  	// Active l'éclairage
    glEnable(GL_LIGHT0); 	// Allume la lumière n°1
#ifndef WIN32
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
#endif
    glEnable(GL_TEXTURE_2D); 	//Active le texturing
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    calottes_texture[0].gl_init("textures/cam_earth0.rgba",512,256);
    calottes_texture[1].gl_init("textures/cam_earth10.rgba",512,256);
    calottes_texture[2].gl_init("textures/cam_earth30.rgba",512,256);
    calottes_texture[3].gl_init("textures/cam_earth50.rgba",512,256);
    calottes_texture[4].gl_init("textures/cam_earth70.rgba",512,256);

    printf("generating earth mesh\n");
    glNewList(1,GL_COMPILE);
    {
	int i,j;
	double theta1,theta2,phi;
	struct {float x;float y;float z;} e,p;
	double TWOPI=2*3.141592654;
	int n=24;
	double r=10.;

	for (j=0;j<n/2;j++) {
	    theta1 = j * TWOPI / n;
	    theta2 = (j + 1) * TWOPI / n;

	    glBegin(GL_QUAD_STRIP);
	    for (i=0;i<=n;i++) {
		phi = i * TWOPI / n;
		//glColor3f(i/(double)n,i/(double)n,i/(double)n);

		e.x = sin(theta2) * cos(phi);
		e.y = sin(theta2) * sin(phi);
		e.z = cos(theta2);
		p.x = r * e.x;
		p.y = r * e.y;
		p.z = r * e.z;

		glNormal3f(e.x,e.y,e.z);
		glTexCoord2f(i/(double)n,2*(j+1)/(double)n);
		glVertex3f(p.x,p.y,p.z);

		e.x = sin(theta1) * cos(phi);
		e.y = sin(theta1) * sin(phi);
		e.z = cos(theta1);
		p.x = r * e.x;
		p.y = r * e.y;
		p.z = r * e.z;

		glNormal3f(e.x,e.y,e.z);
		glTexCoord2f(i/(double)n,2*j/(double)n);
		glVertex3f(p.x,p.y,p.z);
	    }
	    glEnd();
	}
    }
    glEndList();

    // *** OpenGL END ***
    glwindow->gl_end();
}

bool glext_calottes::on_configure_event(GdkEventConfigure* event)
{
    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    if (!glwindow->gl_begin(get_gl_context()))
	return false;

    // *** OpenGL BEGIN ***

    int h = event->height;
    int w = event->width;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w<h)
	glOrtho(-12.0, 12.0, -(12.*h)/w, (12.*h)/w, -(12.*h)/w, (12.*h)/w);
    else
	glOrtho(-(12.0*w)/h, (12.0*w)/h, -12.0, 12.0, -12., 12.);
    glRotated(-90,1,0,0);

    // Choose the modelview matrix to be the matrix
    // manipulated by further calls
    glMatrixMode(GL_MODELVIEW);

    //glClearColor(0.0, 0.0, 0.0, 0.5);
    //glClear(GL_COLOR_BUFFER_BIT);
    
    // *** OpenGL END ***
    glwindow->gl_end();

    return true;
}

bool glext_calottes::on_expose_event(GdkEventExpose* event)
{
    return redraw();
}

bool glext_calottes::redraw()
{
    GLint paramiv[] = {-20,-10,0,0};
    GLfloat paramfv1[] = {0.9,0.9,0.8,1.};
    GLfloat paramfv2[] = {1.,1.,0.8,1.};
    GLfloat paramfv3[] = {0.7,0.8,0.8,1.};
    GLfloat paramfv4[] = {0.7,0.8,0.8,1.};
    GLfloat paramfv5[] = {0.0,0.0,0.0,1.};
    GLfloat paramfv6[] = {0.,0.0,0.2,1.};
    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    if (!glwindow->gl_begin(get_gl_context()))
	return false;
    // *** OpenGL BEGIN ***

    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLineWidth(1.0);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,(float[]) {0.1,0.1,0.1,1.});
    glLoadIdentity();
    glLightiv(GL_LIGHT0,GL_POSITION, paramiv);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,paramfv1);
    glLightfv(GL_LIGHT0,GL_SPECULAR,paramfv2);
    //glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,0.2);
    //glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,0.);
    //obliquité
    glRotated(-23,0,1,0);
    //Sélectionne ce n°
    glBindTexture(GL_TEXTURE_2D,calottes_texture[calotte_texture_select()].id); 	
    glMaterialfv(GL_FRONT,GL_SPECULAR,paramfv3);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,paramfv4);
    glMaterialfv(GL_FRONT,GL_AMBIENT,paramfv5);
    glMaterialfv(GL_FRONT,GL_EMISSION,paramfv6);
    glMaterialf(GL_FRONT,GL_SHININESS,10);
    //angle journalier
    static int angle_jour=0;
    angle_jour = (angle_jour+1)%360;
    glRotated(angle_jour,0,0,1.);
    glCallList(1);

    glwindow->swap_buffers();

    //queue_draw();

    // *** OpenGL END ***

    return true;
}

Glib::RefPtr<Gdk::GL::Config> glext_calottes::glconfig;

void glext_calottes::init_glconfig()
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
    //GLConfigUtil::examine_gl_attrib(glconfig);
}  

//-----------LIEN avec le kernel --------------------
#include <globals.h>
#include "climat.hh"

int glext_calottes::calotte_texture_select()
{
    ExperienceValues& ev = experience_values;
    double v = 70.;
    if (ev.nb_simulations()==0)
	v=ev.get_etat_initial().niveau_calottes_data[0];
    else
	v=ev.back().niveau_calottes_data[climat_interface.indice_courant];

    if (v>55.) return 4;
    if (v>45.) return 3;
    if (v>25.) return 2;
    if (v>1.) return 1;
    return 0;
}

//pour les animations
bool glext_calottes::on_timeout()
{
    redraw();
    return true;
}

void glext_calottes::enable_animations()
{
    if (!m_ConnectionTimeout.connected())
    {
	m_ConnectionTimeout = Glib::signal_timeout().connect(
		sigc::mem_fun(*this, &glext_calottes::on_timeout), 30);
    }
}

void glext_calottes::disable_animations()
{
    if (m_ConnectionTimeout.connected())
	m_ConnectionTimeout.disconnect();
}

