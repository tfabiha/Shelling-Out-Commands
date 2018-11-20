dojobash: dojo.o tools.o tools.h
	gcc dojo.o tools.o -c dojobash

dojo.o: dojo.c tools.h
	gcc -g dojo.c

tools.o: tools.c tools.h
	gcc -g tools.c

run: 
	./a.out
