SRC=src
HEADERS=$(SRC)/Exception.hpp $(SRC)/MediaManager.hpp $(SRC)/Game.hpp $(SRC)/Particle.hpp $(SRC)/Animation.hpp
MAINSRC=$(SRC)/main.cpp 
BIN=bin/Simple
SDL2CFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDL2LIBS=-lSDL2 -lSDL2_mixer

all: $(BIN)

$(BIN): $(MAINSRC) $(HEADERS) 
		g++ -g $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS) -DRELEASE
		
debug: $(BIN)
	gdb $(BIN)
		
run:  $(BIN)
	$(BIN)
