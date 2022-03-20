CC = gcc
CFLAGS = -Wall -ansi -g -Wfatal-errors
LDFLAGS = -lncurses
OBJ = obj/correcteur_0.o obj/Visualise.o obj/ATR.o obj/Listes.o obj/fichier.o
TARGET = correcteur_0

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


obj/correcteur_0.o: src/correcteur_0.c src/Visualise.h src/ATR.h
	gcc -c $< -o obj/correcteur_0.o $(CFLAGS)

obj/Listes.o: src/Listes.c src/Listes.h
	gcc -c $< -o obj/Listes.o $(CFLAGS)

obj/ATR.o: src/ATR.c src/ATR.h src/Listes.h src/fichier.h
	gcc -c $< -o obj/ATR.o $(CFLAGS)

obj/Visualise.o: src/Visualise.c src/Visualise.h src/ATR.h
	gcc -c $< -o obj/Visualise.o $(CFLAGS)

obj/fichier.o: src/fichier.c src/fichier.h
	gcc -c $< -o obj/fichier.o $(CFLAGS)

clean:
	rm -f $(OBJ)
