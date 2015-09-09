// using glademm V2.6.0
//
// newer (non customized) versions of this file go to choix_etat_initial_dialog.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _CHOIX_ETAT_INITIAL_DIALOG_HH
#  include "choix_etat_initial_dialog_glade.hh"
#  define _CHOIX_ETAT_INITIAL_DIALOG_HH
class choix_etat_initial_dialog : public choix_etat_initial_dialog_glade
{  
        
        void on_cancelbutton7_clicked();
        void on_okbutton7_clicked();
        void on_2007_radiobutton_toggled();
        void on_etat_initial_1750_radiobutton_toggled();
        void on_etat_initial_precedent_radiobutton_toggled();
        void on_etat_initial_autre_radiobutton_toggled();
        void on_filechooserbutton1_file_activated();
        void on_spinbutton1_value_changed();
    public:
	choix_etat_initial_dialog();

};
#endif
