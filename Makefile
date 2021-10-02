
SRC=src
MAINSRC=$(SRC)/main.cpp
BIN=bin/first.o
SDL2CFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDL2LIBS=-lSDL2
;INCLUDES=include/useful.h

LINUX: $(BIN)

$(BIN): $(MAINSRC)
		g++ $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS)

run: $(BIN)