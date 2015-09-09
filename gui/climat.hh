#ifndef CLIMAT_GUI_HH
#define CLIMAT_GUI_HH

#include "choix_etat_initial_dialog.hh"
#include "choix_des_parametres_dialog.hh"
#include "enregister_etat_final_dialog.hh"
#include "main_window.hh"
#include "aboutdialog.hh"
#include <map>

class climat_gui
{
    public:
	class choix_etat_initial_dialog *choix_etat_initial_dialog;
   	class choix_des_parametres_dialog *choix_des_parametres_dialog;
   	class enregister_etat_final_dialog *enregister_etat_final_dialog;
   	class main_window *main_window;
	class aboutdialog* aboutdialog;
        int indice_courant;


	void init();
	climat_gui();
       ~climat_gui();
};

extern climat_gui climat_interface;

typedef std::map<std::string,std::string > StrDico;
extern StrDico globalprefs;

#endif//CLIMAT_GUI_HH
