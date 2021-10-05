
SRC=src
MAINSRC=$(SRC)/main.cpp
BIN=bin/game.o
LINUXFLAGS = -I/usr/include/SDL2 
OSXFLAGS = -I/usr/local/Cellar/
WINDOWSFLAGS = TODO
SDL2CFLAGS=-D_REENTRANT
SDL2LIBS=-lSDL2 -lSDL2_mixer
INCLUDES=include/useful.h

# BIN: $(MAINSRC)
# autodetect:
# 	ifeq ($(OS),Windows_NT)
# 		SDL2CFLAGS += $(WINDOWSFLAGS)
# 	else
# 		UNAME_S := $(shell uname -s)
# 		ifeq ($(UNAME_S),Linux)
# 			SDL2CFLAGS += $(LINUXFLAGS)
# 		endif
# 		ifeq ($(UNAME_S),Darwin)
# 			SDL2CFLAGS += $(OSXFLAGS)
# 		endif
# 		# UNAME_P := $(shell uname -p)
# 		# ifeq ($(UNAME_P),x86_64)
# 		#     CCFLAGS += -D AMD64
# 		# endif
# 		# ifneq ($(filter %86,$(UNAME_P)),)
# 		#     CCFLAGS += -D IA32
# 		# endif
# 		# ifneq ($(filter arm%,$(UNAME_P)),)
# 		#     CCFLAGS += -D ARM
# 		# endif
# 	endif

linux:
	g++ $(MAINSRC) -o $(BIN) $(LINUXFLAGS) $(SDL2CFLAGS) $(SDL2LIBS)
osx: 
	g++ $(MAINSRC) -o $(BIN) $(OSXFLAGS) $(SDL2CFLAGS) $(SDL2LIBS)
#g++ src/main.cpp -o bin/game.o -I include -L /usr/local/Cellar/ -l SDL2 -D_REENTRANT

#$(BIN): $(MAINSRC)
#	g++ $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS)
#commented out until I know what the hell its doin
run:
	$(BIN)

clean:
	rm bin/*