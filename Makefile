# Compilateur
CC = gcc

# Options de compilation (warnings + include)
CFLAGS = -Wall -I include

# Options de linkage (bibliothèques SDL)
LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows

# Sources et cible
SRC = $(wildcard src/*.c)
TARGET = liquide

# Règle principale : créer l'exécutable
$(TARGET):
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

# Nettoyer
clean:
	del /Q $(TARGET)
