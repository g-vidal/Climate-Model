// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MAIN_WINDOW_HH
#  include "main_window_glade.hh"
#  define _MAIN_WINDOW_HH
class main_window : public main_window_glade
{  
        
        void on_new1_activate();
        void on_superposer_menuitem_activate();
        void on_save1_activate();
        void on_quit1_activate();
        void on_animations_menuitem_activate();
        void on_about1_activate();
        void on_nouvelle_simulation_button_clicked();
        void on_superposer_button_clicked();
        void on_enregistrer_etat_final_button_clicked();
        void on_time_slider_hscale_value_changed();
        void on_graphe_two_combobox_changed();
        void on_graphe_three_combobox_changed();
        void on_graphe_four_combobox_changed();
        void on_graphe_one_combobox_changed();

    public:
	main_window();
	void redraw_all();
	void recompile_all();
	inline void show_choix_params_dialog() {
	    on_superposer_button_clicked();
	}
};
#endif
