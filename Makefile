# Variables
CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
SRC =

# Création de l'excécutable
liquide: src/main.c
	$(CC) $(CFLAGS) src/main.c -o liquide $(LDFLAGS)
