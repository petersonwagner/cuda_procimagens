all: pgmlimiar

pgmlimiar: pgmlimiar.o pgmlib.o commline.o pgmlimiar_cuda.o
	nvcc pgmlimiar.o pgmlib.o commline.o pgmlimiar_cuda.o -o pgmlimiar

pgmlimiar_cuda.o: pgmlimiar_cuda.cu pgmlimiar_cuda.h
	nvcc -c pgmlimiar_cuda.cu

pgmlimiar.o: pgmlimiar.cpp pgmlib.h commline.h
	gcc -c pgmlimiar.cpp

pgmlib.o: pgmlib.cpp pgmlib.h commline.h
	gcc -c pgmlib.cpp

commline.o: commline.cpp commline.h
	gcc -c commline.cpp

clean:
	rm -f *.o *~

purge: clean
	rm -f pgmnega pgmlimiar pgmmedia pgmmediana saida.pgm