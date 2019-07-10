# See LICENSE file for copyright and license details.

include config.mk

SRC = dwmstatus.c utils.c comps/dwmstatus-bat.c comps/dwmstatus-disk.c \
comps/dwmstatus-ip.c comps/dwmstatus-load.c comps/dwmstatus-time.c \
comps/dwmstatus-wifi.c 
OBJ = ${SRC:.c=.o}

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS) -g

options:
	@echo ${NAME} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"


clean:
	@echo cleaning
	@rm -f ${NAME} ${OBJ} ${NAME}-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p ${NAME}-${VERSION}
	@cp -R Makefile LICENSE config.mk \
		${SRC} ${NAME}-${VERSION}
	@tar -cf ${NAME}-${VERSION}.tar ${NAME}-${VERSION}
	@gzip ${NAME}-${VERSION}.tar
	@rm -rf ${NAME}-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${NAME} ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/${NAME}

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/${NAME}

.PHONY: all options clean dist install uninstall
