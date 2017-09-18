all: pgmnega

pgmnega: pgmnega.o pgmlib.o commline.o pgmnega_cuda.o
	nvcc pgmnega.o pgmlib.o commline.o pgmnega_cuda.o -o pgmnega

pgmnega_cuda.o: pgmnega_cuda.cu pgmnega_cuda.h
	nvcc -c pgmnega_cuda.cu

pgmnega.o: pgmnega.cpp pgmlib.h commline.h
	gcc -c pgmnega.cpp

pgmlib.o: pgmlib.cpp pgmlib.h commline.h
	gcc -c pgmlib.cpp

commline.o: commline.cpp commline.h
	gcc -c commline.cpp



clean:
	rm -f *.o *~

purge: clean
	rm -f pgmnega pgmlimiar pgmmedia pgmmediana saida.pgm