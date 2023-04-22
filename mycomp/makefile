mycomp: mycomp.o utils.o complex.o
	gcc -Wall -pedantic -ansi mycomp.o utils.o complex.o -o mycomp -lm

mycomp.o: mycomp.c utils.h complex.h
	gcc -Wall -pedantic -ansi -c mycomp.c -o mycomp.o

utils.o: utils.c utils.h complex.h
	gcc -Wall -pedantic -ansi -c utils.c -o utils.o

complex.o: complex.c complex.h
	gcc -Wall -pedantic -ansi -c complex.c -o complex.o -lm
