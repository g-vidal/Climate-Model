// using glademm V2.6.0
//
// newer (non customized) versions of this file go to enregister_etat_final_dialog.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _ENREGISTER_ETAT_FINAL_DIALOG_HH
#  include "enregister_etat_final_dialog_glade.hh"
#  define _ENREGISTER_ETAT_FINAL_DIALOG_HH
class enregister_etat_final_dialog : public enregister_etat_final_dialog_glade
{  
        
        void on_cancelbutton8_clicked();
        void on_okbutton8_clicked();
        void on_enregistrer_choix_simulation_combobox_changed();
};
#endif
