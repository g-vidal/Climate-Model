all:
	make -C src
	make -C gui

clean:
	touch Makefile.conf
	make -C gui clean
	make -C src clean
	rm -f Makefile.conf

climat.pot:
	xgettext --from-code utf-8 -o po/climat.pot src/*.h src/*.cpp gui/*.h? gui/*.cc gui/*.cpp 
	sed -i "s/ c-format/ no-c-format/" po/climat.pot



