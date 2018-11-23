all: dojo.o tools.o tools.h
	gcc dojo.o tools.o

dojo.o: dojo.c tools.h
	gcc -c -g dojo.c

tools.o: tools.c tools.h
	gcc -c -g tools.c

run:
	./a.out

clean:
	rm *.o; rm *.*.gch; rm a.out; rm *#.#*; rm -rf *.dSYM
