remove : run
	rm run
	rm liste.o
	rm main.o
	rm affichage.o
run: compile
	./run
compile: liste.o affichage.o main.o
	gcc -o run main.o liste.o affichage.o -lm

main.o: main.c liste.c affichage.c
	gcc -o main.o -c main.c  -Wall
liste.o : liste.c structure.h
	gcc -c liste.c -o liste.o -lm   -Wall 
affichage.o: affichage.c structure.h
	gcc -o affichage.o -c affichage.c  -Wall


	