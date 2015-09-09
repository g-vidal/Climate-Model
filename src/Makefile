include ../Makefile.conf

PACKAGES=glibmm-2.4
INCLUDES=`pkg-config --cflags ${PACKAGES}`
LIBS=-L. -lclimat `pkg-config --libs ${PACKAGES}`

#mettre ici tous les fichiers qui ne contiennent  
#PAS de fonction main() et qui doivent faire partie de
#libclimat.a
LIBOBJS= \
experience_values.o \
globals.o \
graph_designer.o \
modele_constants.o \
modele_execute.o \
simulation_values.o \
modele_create_etat_1750.o \
modele_create_etat_2007.o \
tableau.o

#mettre ici les .o contenant une fonction main()
EXEOBJS= \
modele_test.o 

#mettre ici les .exe correspondants
EXE= \
modele_test.exe 

HEADERS= \
exceptions.h \
experience_values.h \
globals.h \
graph_designer.h \
graphe_shown.h \
modele_constants.h \
modele_consts_physique.h \
simulation_values.h \
tableau.h

all: libclimat.a ${EXEOBJS} ${EXE}

test: modele_test.exe 
	./modele_test.exe>sortie_test.out

libclimat.a: ${LIBOBJS}
	rm -f libclimat.a
	${AR} -r libclimat.a ${LIBOBJS} 

clean:
	rm -f ${LIBOBJS} ${EXEOBJS} libclimat.a
	rm -f modele_test.exe sortie_test.out modele_create_etat_1750.exe modele_create_etat_2007.exe


create1750: modele_create_etat_1750.exe
	./modele_create_etat_1750.exe

create2007: modele_create_etat_2007.exe 
	./modele_create_etat_2007.exe


%.o: %.cpp ${HEADERS}
	${CXX} -c -o $@ ${CXXFLAGS} ${INCLUDES}  $<

%.exe: %.o libclimat.a
	${CXX} -o $@ ${CXXFLAGS} $< ${LIBS}

../Makefile.conf: ../Makefile.unix.conf
	cp -f $< $@

