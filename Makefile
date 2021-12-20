all:
	gcc -Wall -c main.c -c calc.c
	gcc -o stringProg main.o calc.o

clean:
	rm -rf *.o *.a *.so
