// using glademm V2.6.0
//
// newer (non customized) versions of this file go to aboutdialog.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef ABOUTDIALOG_HH
#define ABOUTDIALOG_HH

#include <gtkmm/aboutdialog.h>

class aboutdialog : public Gtk::AboutDialog
{  
public:
        
        aboutdialog();

        virtual ~aboutdialog() {}
};

#endif
