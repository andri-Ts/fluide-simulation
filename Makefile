# Compilateur
CC = gcc

# Options de compilation (warnings + include)
CFLAGS = -Wall -I include -I dependencies

# Options de linkage (bibliothèques SDL)
LDFLAGS = -L dependencies/lib -lmingw32 -lSDL2main -lSDL2 -mwindows

# Sources et cible
SRC = $(wildcard src/*.c)
# Nom et emplacement de l'exécutable final
TARGET = build/liquide

# Règle principale : créer l'exécutable
$(TARGET):
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)
# copie la DLL SDL2 à côté de l'exe
	copy dependencies\SDL2.dll build\

# Lance l'exécutable depuis la racine(mingw32-make run)
run: $(TARGET)
	build\liquide.exe

# Nettoyer
clean:
	del /Q $(TARGET)
