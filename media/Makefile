all: pgmmedia


pgmmedia: pgmmedia.o pgmlib.o commline.o pgmmedia_cuda.o
	nvcc pgmmedia.o pgmlib.o commline.o pgmmedia_cuda.o -o pgmmedia

pgmmedia_cuda.o: pgmmedia_cuda.cu pgmmedia_cuda.h
	nvcc -c pgmmedia_cuda.cu

pgmmedia.o: pgmmedia.cpp pgmlib.h commline.h
	gcc -c pgmmedia.cpp

pgmlib.o: pgmlib.cpp pgmlib.h commline.h
	gcc -c pgmlib.cpp

commline.o: commline.cpp commline.h
	gcc -c commline.cpp



clean:
	rm -f *.o *~


purge: clean
	rm -f pgmnega pgmlimiar pgmmedia pgmmediana saida.pgm