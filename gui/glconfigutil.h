#ifndef GLCONFIGUTIL_H
#define GLCONFIGUTIL_H
#include <gtkmm.h>

#include <gtkglmm.h>

#include <GL/gl.h>
#include <GL/glu.h>

struct GLConfigUtil
{
  static void print_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig,
                              const char* attrib_str,
                              int attrib,
                              bool is_boolean);

  static void examine_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig);
};

#endif //GLCONFIGUTIL_H

