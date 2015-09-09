include ../Makefile.conf

languagesetup.exe: languagesetup.o ../gui/icon.o
	$(CC) -o $@ ../gui/icon.o -mwindows $< `pkg-config --libs gtk+-2.0`

languagesetup.o: languagesetup.c 
	$(CC) -c -o $@ `pkg-config --cflags gtk+-2.0` $< 

../gui/icon.o:
	make -C ../gui icon.o


clean:
	rm languagesetup.exe
