scaner:scaner.o
	gcc -o scaner scaner.o

scaner.o:scaner.c variables.h
	gcc -c scaner.c

clear:
	rm scaner.o scaner
