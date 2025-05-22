CC = g++
CFLAGS = -Isrc/Include -IFUNCTIONS
LDFLAGS = -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
SOURCES = GAME.c FUNCTIONS/button.c FUNCTIONS/clock.c FUNCTIONS/matrix.c FUNCTIONS/mouvments.c FUNCTIONS/randomiser.c FUNCTIONS/machine.c FUNCTIONS/save.c FUNCTIONS/score.c FUNCTIONS/vsm.c FUNCTIONS/rounded.c FUNCTIONS/background.c FUNCTIONS/SOG.c
TARGET = main

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)
