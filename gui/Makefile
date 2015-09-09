include ../Makefile.conf

PACKAGES=gtkglextmm-1.2
INCLUDES=-I../src `pkg-config --cflags ${PACKAGES}` 
LIBS=-L../src -lclimat `pkg-config --libs ${PACKAGES}`


OBJS=choix_des_parametres_dialog.o \
choix_des_parametres_dialog_glade.o \
choix_etat_initial_dialog.o \
choix_etat_initial_dialog_glade.o \
climat.o \
enregister_etat_final_dialog.o \
enregister_etat_final_dialog_glade.o \
main_window.o \
main_window_glade.o \
cairo_graphe.o \
glext_calottes.o \
glext_waterlevel.o \
glconfigutil.o \
aboutdialog.o

HEADERS= \
choix_des_parametres_dialog_glade.hh \
choix_des_parametres_dialog.hh \
choix_etat_initial_dialog_glade.hh \
choix_etat_initial_dialog.hh \
config.h \
enregister_etat_final_dialog_glade.hh \
enregister_etat_final_dialog.hh \
glconfigutil.h \
glext_calottes.hh \
cairo_graphe.hh \
glext_waterlevel.hh \
main_window_glade.hh \
main_window.hh \
rgba_texture.h \
aboutdialog.hh

all: ${gui_target_all}

clean: 
	rm -f ${OBJS}
	rm -f climat

climat: ${OBJS} ../src/libclimat.a
	${CXX} -o $@ ${CXXFLAGS} ${OBJS} ${LIBS}

climat.exe: ${OBJS} ../src/libclimat.a icon.o
	${CXX} -o $@ ${CXXFLAGS} icon.o ${OBJS} ${LIBS}

icon.o: icon.rc icones_interface.ico
	windres -o $@ $<

%.o: %.cc ${HEADERS}
	${CXX} -c -o $@ ${CXXFLAGS} ${INCLUDES} $<

%.o: %.cpp ${HEADERS}
	${CXX} -c -o $@ ${CXXFLAGS} ${INCLUDES} $<
