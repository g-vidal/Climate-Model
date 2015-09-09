// using glademm V2.6.0
//
// newer (non customized) versions of this file go to climat.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include <gtkmm/main.h>

#include "choix_etat_initial_dialog.hh"
#include "choix_des_parametres_dialog.hh"
#include "enregister_etat_final_dialog.hh"
#include "main_window.hh"

#include <gtkglmm.h>
#include "cairo_graphe.hh"
#include "glext_calottes.hh"
#include "glext_waterlevel.hh"
#include <globals.h>
#include <exceptions.h>
#include "climat.hh"
#include "traduction.h"
#include <fstream>
#include <cstdlib>

using namespace std;

StrDico globalprefs;

int main(int argc, char **argv)
{  

    //lecture des fichiers de prefs globaux
    globalprefs["lang"]="";
    globalprefs["font"]="Sans";
    //lecture du fichier climat.ini
    ifstream ifs("climat.ini");
    std::string line;
    while(ifs)
    {
	std::getline(ifs,line);
	if (line[0]=='#') continue;
	std::string::size_type eqsi = line.find('=');
	if (eqsi == std::string::npos) continue;
	std::string::size_type endi = line.find_last_not_of(" \t\f\v\n\r");
	globalprefs[line.substr(0,eqsi)]=line.substr(eqsi+1,endi-eqsi);
    }
    for (StrDico::iterator it = globalprefs.begin(); it!=globalprefs.end(); ++it)
    {
	cerr << "PREF: " << it->first << " := \"" << it->second  << "\""<< endl;
    }
    //traitement special windows pour la langue...
    //y'a que les variables d'environnement qui marchent?

#ifdef WIN32
    string bou = "LANG="+globalprefs["lang"];
    putenv(const_cast<char*> (bou.c_str()));
#endif

    setlocale(LC_ALL,globalprefs["lang"].c_str());

    bindtextdomain("climat","./locale");
    textdomain("climat");	

    //initialisation principale de GTK
    Gtk::Main m(&argc, &argv,false);
    Gtk::GL::init(argc, argv);


    cerr << "getting locale ";
    cerr << setlocale(LC_MESSAGES,0) << endl;
    //exit(0);


    //iniialisation particulière des composants statiques opengl
    //glext_graphe::init_glconfig();
    glext_calottes::init_glconfig();
    glext_waterlevel::init_glconfig();


    WARNING("debut simulation");
    experience_values.set_etat_initial(create_etat_2007(),1000.);
    climat_interface.indice_courant=0;

    WARNING("fin simulation");



    climat_interface.init();
    m.run(*climat_interface.main_window);
    return 0;
}

climat_gui climat_interface;

climat_gui::climat_gui():
    choix_etat_initial_dialog(0),
    choix_des_parametres_dialog(0),
    enregister_etat_final_dialog(0),
    main_window(0)
{
}

void climat_gui::init() 
{
    choix_etat_initial_dialog = new class choix_etat_initial_dialog();
    choix_des_parametres_dialog = new class choix_des_parametres_dialog();
    enregister_etat_final_dialog = new class enregister_etat_final_dialog();
    aboutdialog = new class aboutdialog();
    main_window = new class main_window();
    main_window->show();
    //aboutdialog->show();
}

climat_gui::~climat_gui() 
{
    delete choix_etat_initial_dialog;
    delete choix_des_parametres_dialog;
    delete enregister_etat_final_dialog;
    delete aboutdialog;
    delete main_window;
}

