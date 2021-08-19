# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

# Configuration variables and paths can be found here
include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

# Build and Link dwm binary
all: options dwm

# Print compilation options
options:
	@echo \e[94mInfo: DWM build options:\e[0m
	@echo -e "\e[92mCFLAGS\e[0m   = ${CFLAGS}"
	@echo -e "\e[92mDFLAGS\e[0m  = ${LDFLAGS}"
	@echo -e "\e[92mC\e[0m       = ${CC}"

# Compile everything
.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

# Link everything and produce the final binary
dwm: ${OBJ}
	@echo -e "\e[94mINFO: Linking dwm...\e[0m"
	${CC} -o $@ ${OBJ} ${LDFLAGS}

# Clean compilation artifacts
clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

# Make tar dist
dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

# Install the initialization file and the desktop file
initfiles:
	@echo -e "\e[94mINFO: Installing desktop file...\e[0m"
	mkdir -p /usr/share/xsessions/
	cp -f dwm.desktop /usr/share/xsessions/dwm.desktop
	@echo -e "\e[94mINFO: Installing initialization script...\e[0m"
	cp -f startdwm ${DESTDIR}${PREFIX}/bin/startdwm
	chmod 755 ${DESTDIR}${PREFIX}/bin/startdwm

# Install all scripts to $SCRIPTPATH
scripts:
	@echo -e "\e[94mINFO: Installing scripts...\e[0m"
	mkdir -p ${SCRIPTPATH}
	cp -f scripts/* ${SCRIPTPATH}

# Install all user-local files
deps: scripts

# Remove all user-local files
remove-deps:
	rm -f ${HOME}/.cache/dwm.log
	rm -f ${HOME}/.local/bin/volume.sh
	rm -f ${HOME}/.local/bin/brightness.sh

# Install everything that needs root access
install: all initfiles
	@echo -e "\e[94mINFO: Installing dwm...\e[0m"
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	@echo -e "\e[94mINFO: Installing manpage...\e[0m"
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1

# Uninstall everything that needs root access
uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1
	rm -f /usr/share/xsessions/dwm.desktop
	rm -f ${DESTDIR}${PREFIX}/bin/startdwm


.PHONY: all options clean dist install uninstall scripts
