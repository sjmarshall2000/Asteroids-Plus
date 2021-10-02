
SRC=src
MAINSRC=$(SRC)/main.cpp
BIN=bin/game.o
LINUXFLAGS = -I/usr/include/SDL2 
OSXFLAGS=-F/Library/Frameworks -framework SDL2
SDL2CFLAGS=-D_REENTRANT
SDL2LIBS=-lSDL2
INCLUDES=include/useful.h


linux: $(BIN)
	g++ $(MAINSRC) -o $(BIN) $(LINUXFLAGS) $(SDL2CFLAGS) $(SDL2LIBS)
osx: 
	g++ $(MAINSRC) -o $(BIN) $(OSXFLAGS) $(SDL2CFLAGS) 

#$(BIN): $(MAINSRC)
#	g++ $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS)
#commented out until I know what the hell its doin
run:
	$(BIN)