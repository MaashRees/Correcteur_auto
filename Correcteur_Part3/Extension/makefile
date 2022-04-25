CC = gcc
CFLAGS = -Wall -ansi -g -Wfatal-errors
LDFLAGS = -lncurses
OBJ = obj/correcteur_2.o obj/Ext.o obj/Listes.o obj/fichier.o obj/Levenshtein.o obj/ArbreBK.o
TARGET = correcteur_2

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


obj/correcteur_2.o: src/correcteur_2.c src/Ext.h src/Levenshtein.h src/ArbreBK.h
	gcc -c $< -o obj/correcteur_2.o $(CFLAGS)

obj/Listes.o: src/Listes.c src/Listes.h
	gcc -c $< -o obj/Listes.o $(CFLAGS)

obj/Ext.o: src/Ext.c src/Ext.h src/ArbreBK.h src/Levenshtein.h
	gcc -c $< -o obj/Ext.o $(CFLAGS)

obj/ArbreBK.o: src/ArbreBK.c src/ArbreBK.h src/Listes.h src/fichier.h src/Levenshtein.h
	gcc -c $< -o obj/ArbreBK.o $(CFLAGS)

obj/fichier.o: src/fichier.c src/fichier.h
	gcc -c $< -o obj/fichier.o $(CFLAGS)

obj/Levenshtein.o: src/Levenshtein.c src/Levenshtein.h
	gcc -c $< -o obj/Levenshtein.o $(CFLAGS)

clean:
	rm -f $(OBJ)
