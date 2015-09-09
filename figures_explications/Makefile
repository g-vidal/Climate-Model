SVGS=$(wildcard *.svg)
DEST=$(patsubst %.svg,%.png,${SVGS})

all: ${DEST}

%.png: %.svg
	inkscape -y 0 -e $@ $<
