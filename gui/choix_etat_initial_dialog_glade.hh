// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/camille/ubuntu/CIES/Atelier_projet/projet_climat_new/climat.glade
// for gtk 2.10.6 and gtkmm 2.10.2
//
// Please modify the corresponding derived classes in ./src/choix_etat_initial_dialog.hh and./src/choix_etat_initial_dialog.cc

#ifndef _CHOIX_ETAT_INITIAL_DIALOG_GLADE_HH
#  define _CHOIX_ETAT_INITIAL_DIALOG_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/dialog.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/tooltips.h>

class choix_etat_initial_dialog_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::RadioButton * two007_radiobutton;
        class Gtk::RadioButton * etat_initial_1750_radiobutton;
        class Gtk::RadioButton * etat_initial_precedent_radiobutton;
        class Gtk::RadioButton * etat_initial_autre_radiobutton;
        class Gtk::FileChooserButton * filechooserbutton1;
        class Gtk::SpinButton * spinbutton1;
protected:
        
        choix_etat_initial_dialog_glade();
        
        ~choix_etat_initial_dialog_glade();

	Gtk::Tooltips m_tooltips;
private:
        virtual void on_cancelbutton7_clicked() = 0;
        virtual void on_okbutton7_clicked() = 0;
        virtual void on_2007_radiobutton_toggled() = 0;
        virtual void on_etat_initial_1750_radiobutton_toggled() = 0;
        virtual void on_etat_initial_precedent_radiobutton_toggled() = 0;
        virtual void on_etat_initial_autre_radiobutton_toggled() = 0;
        virtual void on_filechooserbutton1_file_activated() = 0;
        virtual void on_spinbutton1_value_changed() = 0;
};
#endif
