CC = gcc
CFLAGS = -Wall -ansi -g -Wfatal-errors
LDFLAGS = -lncurses
OBJ = obj/main.o obj/correcteur_2.o obj/correcteur_1.o obj/correcteur_0.o obj/gestion_erreur.o obj/Visualise.o obj/ATR.o obj/Listes.o obj/fichier.o obj/Levenshtein.o obj/ArbreBK.o
TARGET = correcteur

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


obj/main.o: src/main.c src/correcteur_2.h src/correcteur_1.h src/correcteur_0.h src/gestion_erreur.h 
	gcc -c $< -o obj/main.o $(CFLAGS)

obj/correcteur_2.o: src/correcteur_2.c src/correcteur_2.h src/Visualise.h src/ATR.h src/Levenshtein.h src/ArbreBK.h
	gcc -c $< -o obj/correcteur_2.o $(CFLAGS)


obj/correcteur_1.o: src/correcteur_1.c src/correcteur_1.h src/Visualise.h src/ATR.h src/Levenshtein.h
	gcc -c $< -o obj/correcteur_1.o $(CFLAGS)


obj/correcteur_0.o: src/correcteur_0.c src/correcteur_0.h src/Visualise.h src/ATR.h
	gcc -c $< -o obj/correcteur_0.o $(CFLAGS)

obj/gestion_erreur.o: src/gestion_erreur.c src/gestion_erreur.h
	gcc -c $< -o obj/gestion_erreur.o $(CFLAGS)

obj/Listes.o: src/Listes.c src/Listes.h
	gcc -c $< -o obj/Listes.o $(CFLAGS)

obj/ATR.o: src/ATR.c src/ATR.h src/Listes.h src/fichier.h
	gcc -c $< -o obj/ATR.o $(CFLAGS)

obj/ArbreBK.o: src/ArbreBK.c src/ArbreBK.h src/Listes.h src/fichier.h src/Levenshtein.h
	gcc -c $< -o obj/ArbreBK.o $(CFLAGS)

obj/Visualise.o: src/Visualise.c src/Visualise.h src/ATR.h
	gcc -c $< -o obj/Visualise.o $(CFLAGS)

obj/fichier.o: src/fichier.c src/fichier.h
	gcc -c $< -o obj/fichier.o $(CFLAGS)

obj/Levenshtein.o: src/Levenshtein.c src/Levenshtein.h src/ATR.h
	gcc -c $< -o obj/Levenshtein.o $(CFLAGS)

clean:
	rm -f $(OBJ)
