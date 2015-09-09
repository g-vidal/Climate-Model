// using glademm V2.6.0
//
// newer (non customized) versions of this file go to aboutdialog.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "aboutdialog.hh"
#include <glibmm/ustring.h>
#include <vector>
using Glib::ustring;

aboutdialog::aboutdialog(): Gtk::AboutDialog()
{
    std::vector<ustring> v;
    v.push_back("Nicolas Gama");
    v.push_back("Camille Risi");
    set_authors(v);
    set_comments("commentaires");
    set_copyright ("Nicolas Gama and Camille Risi");
    set_license ("GPL?");
    //set_logo_icon_name ("");
    set_name ("Modèle-climat");
    set_version ("2.0");
    set_website ("bientot.com");
    set_website_label ("bientôt");
}

