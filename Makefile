#  Makefile 
#  Auteur : Farès BELHADJ (Lire COPYING)
#  Email  : amsi@ai.univ-paris8.fr
#  Date   : 26/09/2013

UNAME := $(shell uname)
#définition des commandes utilisees
CC = g++
RM = rm -rf
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
#déclaration des options du compilateur
PG_FLAGS =
SDL_CFLAGS = $(shell sdl-config --cflags)
CPPFLAGS = -g -I. -I/usr/X11R6/include $(SDL_CFLAGS)
CFLAGS = -Wall -O2 $(PG_FLAGS)
ifeq ($(UNAME),Darwin)
   LDFLAGS  = -lm -framework OpenGL -framework SDL -framework cocoa
else
   SDL_LDFLAGS = $(shell sdl-config --libs)
   LDFLAGS = -lm $(SDL_LDFLAGS) -L/usr/X11R6/lib -lGL -lGLU
endif
#définition des fichiers et dossiers
PROGNAME =visugraphe
PACKAGE=$(PROGNAME)
VERSION = 1.0
distdir = $(PACKAGE)-$(VERSION)
HEADERS = myheader.h
SOURCES = visu.cpp 
ifeq ($(UNAME),Darwin)
   SOURCES += SDLmain.m
   HEADERS += SDLmain.h
endif
DOXYFILE = documentation/Doxyfile
EXTRAFILES = COPYING Makefile
OBJS_A = $(SOURCES:.c=.o)
OBJS = $(OBJS_A:.m=.o)
DISTFILES = $(SOURCES) $(EXTRAFILES) $(HEADERS) $(DOXYFILE)

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

%.o: %.m
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

doc: $(DOXYFILE)
	cd documentation && doxygen && cd ..

dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)
distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)
clean:
	@$(RM) $(PROGNAME) $(OBJS) *~ $(distdir).tgz gmon.out core.*  documentation/*~ documentation/html
